//
// Created by sungaoran on 2022/3/23.
//

#ifndef PLANTSIO_IVY_CONTROLROTATION_H
#define PLANTSIO_IVY_CONTROLROTATION_H

#include "behaviortree_cpp_v3/control_node.h"

namespace BT {
    class ControlRotation : public ControlNode {
    public:
        explicit ControlRotation(const std::string &name) : ControlNode(name, {}) {
        }

        NodeStatus tick() override {
            setStatus(NodeStatus::RUNNING);
            TreeNode *current_child_node = children_nodes_[current_child_idx_];
            const NodeStatus child_status = current_child_node->executeTick();
            if (child_status != NodeStatus::RUNNING) {
                advance();
                haltChildren();
            }
            return child_status;
        }

        void halt() override {
            if (status() == NodeStatus::RUNNING) {
                advance();
            }
            ControlNode::halt();
        }


    private:
        size_t current_child_idx_ = 0;

        void advance() {
            current_child_idx_++;
            if (current_child_idx_ == children_nodes_.size()) {
                current_child_idx_ = 0;
            }
        }
    };
}

#endif //PLANTSIO_IVY_CONTROLROTATION_H
