//
// Created by sungaoran on 2022/3/20.
//

#include "behaviortree_cpp_v3/controls/Dispatcher.h"

#ifdef Ivy

#include "Engine/Behavior/EventDispatcher.h"
#include "behaviortree_cpp_v3/config_implt.h"

namespace BT {

    Dispatcher::Dispatcher(const std::string &name)
            : ControlNode(name, {}),
              m_current_child_index(invalid) {
        setRegistrationID("Dispatcher");
        EventDispatcher::instance().set_bt_dispatcher(this);
    }

    Dispatcher::~Dispatcher() {
        /* todo verify if this is called after the new dispatcher's constructor */
        EventDispatcher::instance().unset_bt_dispatcher();
    }

    NodeStatus Dispatcher::tick() {
        if (!m_initialized) {
            m_initialized = true;
            on_init();
//            return new_status;
        }

        setStatus(NodeStatus::RUNNING);

        NodeStatus _status;
        if (m_current_child_index != invalid) {
            auto ret = m_map.find(m_current_child_index);
            if (ret != m_map.end()) {
                TreeNode *current_child = ret->second;
                _status = current_child->executeTick();
            } else {
                log_w("debug-bt event %d not found", m_current_child_index);
                _status = NodeStatus::FAILURE;
            }
        } else {
            /* no active events */
            _status = NodeStatus::FAILURE;
        }
        if (_status != NodeStatus::RUNNING) {
            /* unset current child if not running */
            m_current_child_index = invalid;
            haltChildren();
        }
        return _status;
    }

    NodeStatus Dispatcher::on_init() {
        for (auto child: children_nodes_) {
            Optional<int> ret = child->getInput<int>(DECORATOR_INDEX_NAME);
            if (ret) {
                m_map[(event_t) ret.value()] = child;
            }
        }
        return NodeStatus::SUCCESS;
    }

    TreeNode *Dispatcher::get_evt_by_index(event_t index) {
        if (index == invalid) {
            return nullptr;
        }
        auto ret = m_map.find(index);
        if (ret != m_map.end()) {
            return ret->second;
        } else {
            return nullptr;
        }
    }

#else
    namespace BT {
        Dispatcher::Dispatcher(const std::string &name) : ControlNode(name, {}) {
            setRegistrationID("Dispatcher");
        }

        Dispatcher::~Dispatcher() {
        }

        NodeStatus Dispatcher::tick() {
            return NodeStatus::SUCCESS;
        }

        NodeStatus Dispatcher::on_init() {
            return NodeStatus::SUCCESS;
        }

#endif
}