//
// Created by sungaoran on 2022/3/20.
//

#ifndef PLANTSIO_IVY_CONFIG_H
#define PLANTSIO_IVY_CONFIG_H

namespace BT {
    /* note for reference and type check only (for now) */
    /* todo generate enum selection on UI */
    typedef enum {
        invalid = -1,
        blank_tick = 0,
        idle_routine = 1,
        touch_left = 2,
        touch_right = 3,
        touch_hug = 4,
        touch_plant = 5,
        pot_in = 6,
        pot_out = 7,
        knock = 8,
        thump = 9,

    } event_t;
}

#endif //PLANTSIO_IVY_CONFIG_H
