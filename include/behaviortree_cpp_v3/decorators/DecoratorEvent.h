//
// Created by sungaoran on 2022/3/20.
//

#ifndef PLANTSIO_IVY_DECORATOREVENT_H
#define PLANTSIO_IVY_DECORATOREVENT_H

#include "behaviortree_cpp_v3/decorator_node.h"
#include "behaviortree_cpp_v3/config.h"

#define DECORATOR_PRIORITY_NAME     "priority"
#define DECORATOR_INDEX_NAME     "index"

namespace BT {
    class DecoratorEvent : public DecoratorNode {
    public:
        DecoratorEvent(const std::string &name, const NodeConfiguration &config)
                : DecoratorNode(name, config){}

        static PortsList providedPorts() {
            return {InputPort<int>(DECORATOR_PRIORITY_NAME), InputPort<int>(DECORATOR_INDEX_NAME)};
        }

        NodeStatus tick() override;

        int get_priority();

        int get_index();

        bool get_reenter() const{
            return m_reenter;
        }

        NodeStatus on_init();

    private:
        bool m_reenter = false;
        bool m_initialized = false;
    };
}


#endif //PLANTSIO_IVY_DECORATOREVENT_H
