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
        explicit Dispatcher(const std::string &name) : ControlNode(name, {}) {
            setRegistrationID("Dispatcher");
        }

        void set_current_index(event_t index) {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);
            m_current_child_index = index;
        }


    private:
        mutable std::recursive_mutex m_mutex;

        NodeStatus tick() override;

        NodeStatus onStart();

        std::map<event_t, TreeNode *> m_map;

        event_t m_current_child_index = invalid;
    };
}

#endif //PLANTSIO_IVY_DISPATCHER_H
