//
// Created by Gordon on 2021/11/9.
//

#include "RandomFallback.h"
#include "behaviortree_cpp_v3/action_node.h"
#include "esp_random.h"

RandomFallback::RandomFallback(const std::string &name)
        : ControlNode::ControlNode(name, {}) {
    setRegistrationID("RandomFallback");
    current_child_idx_ = generate_random_index();
}

BT::NodeStatus RandomFallback::tick() {
    setStatus(BT::NodeStatus::RUNNING);
    TreeNode *current_child_node = children_nodes_[current_child_idx_];
    const BT::NodeStatus child_status = current_child_node->executeTick();

    switch (child_status) {
        case BT::NodeStatus::RUNNING: {
            return child_status;
        }
        case BT::NodeStatus::SUCCESS: {
            haltChildren();
            current_child_idx_ = generate_random_index();
            return child_status;
        }
        case BT::NodeStatus::FAILURE: {
            current_child_idx_ = generate_random_index();
        }
            break;

        case BT::NodeStatus::IDLE: {
            throw BT::LogicError("A child node must never return IDLE");
        }
    }   // end switch

    return BT::NodeStatus::FAILURE;
}

uint32_t RandomFallback::generate_random_index() {
    const size_t children_count = children_nodes_.size();
    uint32_t rng = esp_random();
    uint32_t index = (uint32_t) ((double) rng / UINT32_MAX * (double) children_count);
    index = std::min(children_count, index);
    return index;
}

void RandomFallback::halt()
{
    current_child_idx_ = generate_random_index();
    ControlNode::halt();
}
