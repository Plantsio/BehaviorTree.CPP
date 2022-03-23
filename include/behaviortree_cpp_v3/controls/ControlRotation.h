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
            setRegistrationID("ControlAnim");
        }

        NodeStatus tick() override {
            const size_t children_count = children_nodes_.size();

            setStatus(NodeStatus::RUNNING);

            TreeNode *current_child_node = children_nodes_[current_child_idx_];
            const NodeStatus child_status = current_child_node->executeTick();
            if (child_status != NodeStatus::RUNNING) {
                current_child_idx_++;
            }
            if (current_child_idx_ == children_count) {
                current_child_idx_ = 0;
            }
            return child_status;
        }


    private:
        size_t current_child_idx_;

    };
}

#endif //PLANTSIO_IVY_CONTROLROTATION_H
