//
// Created by sungaoran on 2022/3/20.
//

#include "behaviortree_cpp_v3/decorators/DecoratorEvent.h"
#include "behaviortree_cpp_v3/decorators/PropReenter.h"

namespace BT {
    NodeStatus DecoratorEvent::tick() {
        if (!m_initialized) {
            m_initialized = true;
            NodeStatus new_status = on_init();
//            return new_status;
        }
        return child()->executeTick();
    }

    int DecoratorEvent::get_priority() {
        auto ret = getInput<int>(DECORATOR_PRIORITY_NAME);
        return ret.value();
    }

    int DecoratorEvent::get_index() {
        auto ret = getInput<int>(DECORATOR_INDEX_NAME);
        return ret.value();
    }

    NodeStatus DecoratorEvent::on_init() {
        if (auto prop = dynamic_cast<PropReenter *>(child())) {
            m_reenter = true;
        }
        return NodeStatus::SUCCESS;
    }
}
