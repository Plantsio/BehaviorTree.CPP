//
// Created by Gordon on 2022/3/23.
//


#include "config_implt.h"

#ifdef Ivy

#include "Engine/Public.h"
#include "Body/Skin.h"
#include "Anim/IvyAnim.h"
#include "Engine/Behavior/EventDispatcher.h"
#include "Body/Plant.h"
#include "Engine/Behavior/IvyBehavior.h"
#include "Engine/IvyEngine.h"
#include "Anim/drivers/EmoDriver.h"

#endif

namespace BT {


    bool get_condition(condition_t condition) {
#ifdef Ivy
        bool ret = false;
        bool reverse = false;
        if (condition < 0) {
            reverse = true;
            condition = (condition_t) (-(int) condition);   /* reverse condition */
        }
        switch (condition) {
            case has_plant:
                ret = Prop::get<bool>(Prop::has_pot);
                break;
            case has_water:
                ret = (Prop::get<int>(Prop::water_level) > 0);
                break;
            case charging:
                ret = Prop::get<bool>(Prop::charging);
                break;
            case touching_left:
                ret = Skin::instance().touching_left();
                break;
            case touching_right:
                ret = Skin::instance().touching_right();
                break;
            case touching_plant:
                ret = Skin::instance().touching_plant();
                break;
            case hugging:
                ret = Skin::instance().hugging();
                break;
            case is_daytime:
                ret = Public::is_daytime();
                break;
        }
        if (reverse) {
            return !ret;
        } else {
            return ret;
        }
#else
        return true;
#endif
    }

    bool get_value(value_t index, double &value) {
#ifdef Ivy
        switch (index) {
            case temp:
                value = Prop::get<double>(Prop::temperature);
                break;
            case humidity:
                value = Prop::get<double>(Prop::humidity);
                break;
            case light:
                value = Prop::get<double>(Prop::ambient_light);
                break;
            case water_level:
                value = Prop::get<double>(Prop::water_level);
                break;
            case battery:
                value = Prop::get<double>(Prop::battery_percent);
                break;
            case soil_moisture:
                value = Prop::get<double>(Prop::soil_moisture);
                break;
            case current_hour:
                value = Public::get_hour();
                break;
            case water_status:
                value = Plant::instance().get_status().water_status;
                break;
            case sun_status:
                value = Plant::instance().get_status().sun_status;
                break;
            case temp_status:
                value = Plant::instance().get_status().temp_status;
                break;
            case batt_status:
                value = Plant::instance().get_status().batt_status;
                break;
            case mood:
                value = IvyBehavior::instance().get_emotion_value(IvyBehavior::mood);
                break;
            case loneliness:
                value = IvyBehavior::instance().get_emotion_value(IvyBehavior::loneliness);
                break;
            case inactive_minute:
                value = IvyEngine::instance().get_inactive_t() / 60000;
                break;
            case emotion_status:
                value = IvyBehavior::instance().get_current_emo_status();
                break;
            default:
                return false;
        }
#endif
        return true;
    }

    std::string get_interrupted_anim_name() {
#ifdef Ivy
        return EmoDriver::instance().get_interrupted_anim_name();
//        return EmoDriver::instance().get_current_anim_unit_name();
//        return EventDispatcher::instance().get_interrupted_anim_name();
#else
        return "";
#endif
    }

    std::string get_current_anim_name() {
#ifdef Ivy
        return EmoDriver::instance().get_current_anim_unit_name();
#else
        return "";
#endif
    }
}