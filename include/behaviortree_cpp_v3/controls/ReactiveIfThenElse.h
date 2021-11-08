//
// Created by sungaoran on 2021/11/9.
//

#ifndef PLANTSIO_IVY_REACTIVEIFTHENELSE_H
#define PLANTSIO_IVY_REACTIVEIFTHENELSE_H

#include "behaviortree_cpp_v3/control_node.h"
class ReactiveIfThenElse  : public BT::ControlNode{
public:
    ReactiveIfThenElse(const std::string& name);

    virtual ~ReactiveIfThenElse() override = default;

    virtual void halt() override;

private:
    size_t child_idx_;

    virtual BT::NodeStatus tick() override;
};


#endif //PLANTSIO_IVY_REACTIVEIFTHENELSE_H
