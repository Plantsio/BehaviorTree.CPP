//
// Created by Gordon on 2022/3/18.
//

#ifndef PLANTSIO_IVY_ANIMATIONNODE_H
#define PLANTSIO_IVY_ANIMATIONNODE_H

#include "behaviortree_cpp_v3/control_node.h"

namespace BT {
    class AnimationNode : public ControlNode {
    public:
        AnimationNode(int priority, const std::string &name) : ControlNode(name, {}) {}

    };
}

#endif //PLANTSIO_IVY_ANIMATIONNODE_H
