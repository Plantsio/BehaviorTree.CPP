//
// Created by sungaoran on 2022/3/20.
//

#include "Dispatcher.h"

#ifdef Ivy

#include "Arduino.h"

#endif
namespace BT {
    NodeStatus Dispatcher::tick() {
        const NodeStatus initial_status = status();

        if (initial_status == NodeStatus::IDLE) {
            NodeStatus new_status = onStart();
            return new_status;
        }
        return NodeStatus::SUCCESS;
    }

    NodeStatus Dispatcher::onStart() {
        for (auto child: children_nodes_) {
            try {
                auto index = (event_t) std::stoi(child->name());
                m_map[index] = child;
            } catch (std::exception &e) {
#ifdef Ivy
                log_w("invalid event index %s during creation", child->name().c_str());
#endif
            }

            if (m_current_child_index != invalid) {
                auto ret = m_map.find(m_current_child_index);
                if (ret != m_map.end()) {
                    TreeNode *current_child = ret->second;
                }
            }


        }

        return NodeStatus::SUCCESS;
    }
}