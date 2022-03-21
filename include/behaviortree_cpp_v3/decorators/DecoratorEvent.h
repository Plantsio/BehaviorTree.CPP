//
// Created by sungaoran on 2022/3/20.
//

#ifndef PLANTSIO_IVY_DECORATOREVENT_H
#define PLANTSIO_IVY_DECORATOREVENT_H

#include "behaviortree_cpp_v3/decorator_node.h"
#include "behaviortree_cpp_v3/config.h"

#define DECORATOR_PRIORITY_NAME     "priority"

namespace BT {
    class DecoratorEvent : public DecoratorNode {
    public:
        DecoratorEvent(const std::string &name, const NodeConfiguration &config) : DecoratorNode(name, config) {}

        static PortsList providedPorts() {
            return {InputPort<int>(DECORATOR_PRIORITY_NAME)};
        }

        NodeStatus tick() override;

        int get_priority();
    };
}


#endif //PLANTSIO_IVY_DECORATOREVENT_H
