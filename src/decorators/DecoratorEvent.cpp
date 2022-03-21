//
// Created by sungaoran on 2022/3/20.
//

#include "behaviortree_cpp_v3/decorators/DecoratorEvent.h"

namespace BT {
    NodeStatus DecoratorEvent::tick() {
        return child()->executeTick();
    }

    int DecoratorEvent::get_priority() {
        auto ret = getInput<int>(DECORATOR_PRIORITY_NAME);
        return ret.value();
    }
}
