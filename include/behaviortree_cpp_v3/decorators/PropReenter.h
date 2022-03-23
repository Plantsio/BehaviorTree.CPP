//
// Created by Gordon on 2022/3/23.
//

#ifndef PLANTSIO_IVY_PROPREENTER_H
#define PLANTSIO_IVY_PROPREENTER_H

#include "behaviortree_cpp_v3/decorator_node.h"

namespace BT {
    class PropReenter : public DecoratorNode {
    public:
        explicit PropReenter(const std::string &name) : DecoratorNode(name, {}) {}

        NodeStatus tick() override {
            return child()->executeTick();
        }
    };
}


#endif //PLANTSIO_IVY_PROPREENTER_H
