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
        touch_left_or_right = 2,         /* 触摸左侧 */

        touch_hug = 4,          /* 触摸两侧 */
        touch_plant = 5,        /* 触摸植物 */
        pot_change = 6,         /* 盆状态改变 */
        knock = 7,              /* 轻敲 */
        thump = 8,              /* 重击 */
        batt_change = 9,        /* 充电状态变更 */
        sun_change = 10,        /* 阳光状态变更 */
        wake_up_suddenly = 11,  /* 突然醒来 */
        wake_up_slowly = 12,    /* 缓慢醒来 */
        sleep = 13,             /* 进入睡眠 */
        water_change = 14,      /* 水位状态变更 */
        temp_change = 15,       /* 温度状态变更 */

        trans_manager = 101,
    };

    enum condition_t : int {
        has_plant = 1,          /* 植物存在 */
        has_water = 2,          /* 水存在 */
        charging = 3,           /* 充电中 */
        touching_left = 4,      /* 触摸左侧中 */
        touching_right = 5,     /* 触摸右侧中 */
        touching_plant = 6,     /* 触摸植物中 */
        hugging = 7,            /* 抱住中 */
        is_daytime = 8,         /* 处于白天 */
    };

    enum value_t : int {
        temp = 1,               /* 温度 */
        humidity = 2,           /* 湿度 */
        light = 3,              /* 光照 */
        water_level = 4,        /* 水位 */
        battery = 5,            /* 电量 */
        soil_moisture = 6,      /* 土壤湿度 */
        current_hour = 7,       /* 当前小时 */
        inactive_minute = 8,    /* 非活跃分钟数 */
        mood = 9,
        water_status = 10,      /* 当前浇水状态 */
        sun_status = 11,        /* 当前阳光状态 */
        temp_status = 12,       /* 当前温度状态 */
        batt_status = 13,       /* 当前电池状态 */
        loneliness = 14,        /* 孤独值 */
        emotion_status =15,     /* 情感状态 */
    };

    /* todo
     * 1. xx触摸左和右合并为一个事件
     * 2. xx光照状态恢复事件
     * 3. xx植物状态产生的突变事件，获取上次状态和当前状态
     * 4. 加入睡眠条件
     * 5. xx非活跃不包括前触
     * 6. xx打断时间队列，以判断短期内打断次数
     * 7. xx加入心情管理
     * 8. 随机节点（验证） */
}
#endif //PLANTSIO_IVY_CONFIG_IMPLT_H
