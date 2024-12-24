#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_lcd.h"
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>

#define LCD_INSTANCE                (0)
#define LVGL_BUFFER_ADDR_AT_SDRAM   (0xD007F810)
#define LVGL_BUFFER_2_ADDR_AT_SDRAM (0xD00FF020)

static void disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p);

static void disp_clean_dcache(lv_disp_drv_t *drv);

static uint8_t CopyImageToLcdFrameBuffer(void *pSrc, void *pDst, uint32_t xSize, uint32_t ySize);

static lv_disp_t *display = NULL;
static lv_disp_drv_t disp_drv;
static lv_disp_draw_buf_t disp_buf;

void lcd_init() {
    printf("lcd_init: Starting initialization\r\n");

    /* There is only one display on STM32 */
    if (display != NULL) {
        printf("lcd_init: Error - Display already initialized\r\n");
        abort();
    }

    printf("lcd_init: Initializing LCD\r\n");
    /* Initialize the LCD */
    if (BSP_LCD_Init(LCD_INSTANCE, LCD_ORIENTATION_LANDSCAPE) != BSP_ERROR_NONE) {
        printf("lcd_init: Error - Failed to initialize LCD\r\n");
        abort();
    }
    printf("lcd_init: LCD initialized\r\n");

    BSP_LCD_SetBrightness(LCD_INSTANCE, 90);
    BSP_LCD_DisplayOn(LCD_INSTANCE);
    printf("lcd_init: LCD brightness set and display turned on\r\n");

    if (*(volatile uint32_t *)LVGL_BUFFER_ADDR_AT_SDRAM != 0xFFFFFFFF) {
        printf("lcd_init: Error - SDRAM buffer memory not initialized properly\r\n");
        abort();
    }
    printf("lcd_init: SDRAM buffer memory initialized properly\r\n");

    /* Initialize LVGL display buffer */
    printf("lcd_init: Initializing LVGL display buffer\r\n");
    lv_disp_draw_buf_init(&disp_buf, (void *)LVGL_BUFFER_ADDR_AT_SDRAM,
                          (void *)LVGL_BUFFER_2_ADDR_AT_SDRAM,
                          Lcd_Ctx[LCD_INSTANCE].XSize * Lcd_Ctx[LCD_INSTANCE].YSize);
    printf("lcd_init: Display buffer initialized\r\n");

    /* Check display size */
    printf("lcd_init: LCD XSize: %lu, YSize: %lu\r\n", Lcd_Ctx[LCD_INSTANCE].XSize, Lcd_Ctx[LCD_INSTANCE].YSize);

    /* Initialize LVGL display driver */
    printf("lcd_init: Initializing LVGL display driver\r\n");
    lv_disp_drv_init(&disp_drv);
    disp_drv.sw_rotate = 1;

    /* Set up the functions to access your display */
    disp_drv.hor_res = Lcd_Ctx[LCD_INSTANCE].XSize;
    disp_drv.ver_res = Lcd_Ctx[LCD_INSTANCE].YSize;
    disp_drv.flush_cb = disp_flush;
    disp_drv.clean_dcache_cb = disp_clean_dcache;
    disp_drv.draw_buf = &disp_buf;
    printf("lcd_init: LVGL display driver configured\r\n");

    /* Register the driver */
    printf("lcd_init: Registering LVGL display driver\r\n");
    display = lv_disp_drv_register(&disp_drv);
    if (display == NULL) {
        printf("lcd_init: Error - Display driver registration failed\r\n");
        abort();
    } else {
        printf("lcd_init: Display driver registered successfully\r\n");
    }
}

static void disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
    printf("disp_flush: Flushing area: x1=%d, y1=%d, x2=%d, y2=%d\r\n",
           area->x1, area->y1, area->x2, area->y2);

    if (area->x2 < 0 || area->y2 < 0 ||
        area->x1 > Lcd_Ctx[LCD_INSTANCE].XSize - 1 ||
        area->y1 > Lcd_Ctx[LCD_INSTANCE].YSize - 1) {
        printf("disp_flush: Area is out of bounds\r\n");
        return;
    }

    SCB_CleanInvalidateDCache();
    SCB_InvalidateICache();

    uint32_t address =
            hlcd_ltdc.LayerCfg[Lcd_Ctx[LCD_INSTANCE].ActiveLayer].FBStartAdress +
            (((Lcd_Ctx[LCD_INSTANCE].XSize * area->y1) + area->x1) * Lcd_Ctx[LCD_INSTANCE].BppFactor);

    printf("disp_flush: Copying image to LCD frame buffer\r\n");
    uint8_t status = CopyImageToLcdFrameBuffer((void *) color_p, (void *) address,
                                               lv_area_get_width(area), lv_area_get_height(area));

    if (status != BSP_ERROR_NONE) {
        printf("disp_flush: Error copying image to LCD frame buffer\r\n");
    }

    lv_disp_flush_ready(&disp_drv);
    printf("disp_flush: Flush complete\r\n");
}

static void disp_clean_dcache(lv_disp_drv_t *drv) {
    printf("disp_clean_dcache: Cleaning and invalidating DCache\r\n");
    SCB_CleanInvalidateDCache();
}

static uint8_t CopyImageToLcdFrameBuffer(void *pSrc, void *pDst, uint32_t xSize, uint32_t ySize) {
    printf("CopyImageToLcdFrameBuffer: Starting DMA2D transfer\r\n");

    hlcd_dma2d.Init.Mode = DMA2D_M2M_PFC;
    hlcd_dma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
    hlcd_dma2d.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;
    hlcd_dma2d.Init.RedBlueSwap = DMA2D_RB_REGULAR;
    hlcd_dma2d.Init.OutputOffset = LCD_DEFAULT_WIDTH - xSize;
    hlcd_dma2d.Instance = DMA2D;

    if (HAL_DMA2D_Init(&hlcd_dma2d) != HAL_OK) {
        printf("CopyImageToLcdFrameBuffer: DMA2D initialization failed\r\n");
        return BSP_ERROR_BUS_DMA_FAILURE;
    }

    if (HAL_DMA2D_Start(&hlcd_dma2d, (uint32_t) pSrc, (uint32_t) pDst, xSize, ySize) != HAL_OK) {
        printf("CopyImageToLcdFrameBuffer: DMA2D start failed\r\n");
        return BSP_ERROR_BUS_DMA_FAILURE;
    }

    if (HAL_DMA2D_PollForTransfer(&hlcd_dma2d, 20) != HAL_OK) {
        printf("CopyImageToLcdFrameBuffer: DMA2D transfer polling failed\r\n");
        return BSP_ERROR_BUS_DMA_FAILURE;
    }

    printf("CopyImageToLcdFrameBuffer: DMA2D transfer complete\r\n");
    return BSP_ERROR_NONE;
}