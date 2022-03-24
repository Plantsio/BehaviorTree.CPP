//
// Created by sungaoran on 2022/3/20.
//

#ifndef PLANTSIO_IVY_CONFIG_H
#define PLANTSIO_IVY_CONFIG_H

#define BT_VALUE_INPUT_NAME     "index"
#define BT_ANIM_NAME            "anim"
#define BT_VALUE_TARGET_NAME    "target"
#define BT_CONDITION_NAME       "condition"
#include "string"

namespace BT {
    /* note for reference and type check only (for now) */
    /* todo generate enum selection on UI */

    enum event_t:int;

    enum condition_t:int;

    enum value_t:int;

    /* get Ivy conditions */
    bool get_condition(condition_t condition);

    /* get Ivy properties or params */
    bool get_value(value_t index, double &value);

    /* get the nam of the currently playing animation */
    std::string get_current_anim_name();
}

#endif //PLANTSIO_IVY_CONFIG_H
