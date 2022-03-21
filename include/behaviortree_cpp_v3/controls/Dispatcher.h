//
// Created by sungaoran on 2022/3/20.
//

#ifndef PLANTSIO_IVY_DISPATCHER_H
#define PLANTSIO_IVY_DISPATCHER_H

#include "behaviortree_cpp_v3/control_node.h"
#include "behaviortree_cpp_v3/config.h"
#include "map"

namespace BT {
    class Dispatcher : public ControlNode {
    public:
        explicit Dispatcher(const std::string &name);

        ~Dispatcher() override;

        event_t get_current_index() const {
            return m_current_child_index;
        }

        void set_current_index(event_t index) {
            m_current_child_index = index;
        }

        TreeNode *get_current_evt() {
            return get_evt_by_index(m_current_child_index);
        }

        TreeNode *get_evt_by_index(event_t index) {
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

    private:
        NodeStatus tick() override;

        NodeStatus on_init();

        bool m_initialized = false;

        std::map<event_t, TreeNode *> m_map;

        event_t m_current_child_index = invalid;
    };
}

#endif //PLANTSIO_IVY_DISPATCHER_H
