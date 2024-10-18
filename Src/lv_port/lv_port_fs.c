/**
 * @file lv_port_fs_templ.c
 *
 */

/*Copy this file as "lv_port_fs.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_fs.h"
#include "../Drivers/lvgl/lvgl.h"
#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_ts.h"
/*********************
 *      DEFINES
 *********************/
#define TS_INSTANCE (TS_INSTANCES_NBR - 1)
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static TS_State_t TS_State;

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
static void touchpad_read(lv_indev_drv_t *drv, lv_indev_data_t *data);
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void touchpad_init(void) {
    TS_Init_t hTS;

    hTS.Width = TS_MAX_WIDTH;
    hTS.Height = TS_MAX_HEIGHT;
    hTS.Orientation = TS_SWAP_XY;
    hTS.Accuracy = 5;
    BSP_TS_Init(TS_INSTANCE, &hTS);

    static lv_indev_drv_t indev_drv; /*Descriptor of an input device driver*/
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER; /*The touchpad is pointer type device*/
    indev_drv.read_cb = touchpad_read;

    lv_indev_drv_register(&indev_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void touchpad_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {
    /* Read your touchpad */
    static int16_t last_x = 0;
    static int16_t last_y = 0;

    BSP_TS_GetState(TS_INSTANCE, &TS_State);
    if (TS_State.TouchDetected) {
        data->point.x = TS_State.TouchX;
        data->point.y = TS_State.TouchY;
        last_x = data->point.x;
        last_y = data->point.y;
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->point.x = last_x;
        data->point.y = last_y;
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
