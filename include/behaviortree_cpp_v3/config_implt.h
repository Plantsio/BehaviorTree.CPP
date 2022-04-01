//
// Created by Gordon on 2022/3/24.
//

#ifndef PLANTSIO_IVY_CONFIG_IMPLT_H
#define PLANTSIO_IVY_CONFIG_IMPLT_H

/* this file is created to prevent massive rebuild should the following enums are changed */
/* note, this file should only be included in cpp files */
#include "config.h"

namespace BT {
    enum event_t : int {
        invalid = -1,
        blank_tick = 0,
        idle_routine = 1,       /* 空闲 */
        touch_left = 2,         /* 触摸左侧 */
        touch_right = 3,        /* 触摸右侧 */
        touch_hug = 4,          /* 触摸两侧 */
        touch_plant = 5,        /* 触摸植物 */
        pot_change = 6,         /* 盆状态改变 */
        knock = 7,              /* 轻敲 */
        thump = 8,              /* 重击 */
        charging_change = 9,     /* 充电状态变更 */
        light_change = 10,      /* 光突变 */
        wake_up_suddenly = 11,  /* 突然醒来 */
        wake_up_slowly = 12,    /* 缓慢醒来 */
        sleep = 13,             /* 进入睡眠 */
    };

    enum condition_t : int {
        has_plant = 1,          /* 植物存在 */
        has_water = 2,          /* 水存在 */
        charging = 3,           /* 充电中 */
        touching_left = 4,      /* 触摸左侧中 */
        touching_right = 5,     /* 触摸右侧中 */
        touching_plant = 6,     /* 触摸植物中 */
        hugging = 7,            /* 抱住中 */
    };

    enum value_t : int {
        temp = 1,               /* 温度 */
        humidity = 2,           /* 湿度 */
        light = 3,              /* 光照 */
        water_level = 4,        /* 水位 */
        battery = 5,            /* 电量 */
        soil_moisture = 6,      /* 土壤湿度 */
    };
}
#endif //PLANTSIO_IVY_CONFIG_IMPLT_H
