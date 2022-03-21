//
// Created by sungaoran on 2022/3/20.
//

#include "Dispatcher.h"

#ifdef Ivy

#include "Engine/Behavior/EventDispatcher.h"

namespace BT {
    Dispatcher::Dispatcher(const std::string &name) : ControlNode(name, {}) {
        setRegistrationID("Dispatcher");
        EventDispatcher::instance().set_bt_dispatcher(this);
    }

    Dispatcher::~Dispatcher() {
        /* todo verify if this is called after the new dispatcher's constructor */
        EventDispatcher::instance().unset_bt_dispatcher();
    }

    NodeStatus Dispatcher::tick() {
        const NodeStatus initial_status = status();

        if (initial_status == NodeStatus::IDLE) {
            NodeStatus new_status = onStart();
            return new_status;
        }

        NodeStatus _status;
        if (m_current_child_index != invalid) {
            auto ret = m_map.find(m_current_child_index);
            if (ret != m_map.end()) {
                TreeNode *current_child = ret->second;
                _status = current_child->executeTick();
//                if (status == NodeStatus::SUCCESS || status == NodeStatus::RUNNING) {
//                    /* current running task is completed */
//                    m_current_child_index = invalid;
//                } else if (status == NodeStatus::IDLE) {
//                    log_e("debug-bt child returned idle status");
//                }
            } else {
                log_w("debug-bt node not found");
                _status = NodeStatus::FAILURE;
            }
        } else {
            /* no active events */
            _status = NodeStatus::FAILURE;
        }
        if (_status != NodeStatus::RUNNING){
            /* unset current child if not runnning */
            m_current_child_index = invalid;
        }

    }

    NodeStatus Dispatcher::onStart() {
        for (auto child: children_nodes_) {
            try {
                auto index = (event_t) std::stoi(child->name());
                m_map[index] = child;
            } catch (std::exception &e) {
                log_w("invalid event index %s during creation", child->name().c_str());
            }
        }

        return NodeStatus::SUCCESS;
    }

#else
    Dispatcher::Dispatcher(const std::string &name) : ControlNode(name, {}) {
        setRegistrationID("Dispatcher");
    }

    Dispatcher::~Dispatcher() {
    }

    NodeStatus Dispatcher::tick() {
        return NodeStatus::SUCCESS;
    }

    NodeStatus Dispatcher::onStart() {
        return NodeStatus::SUCCESS;
    }

#endif
}