//
// Created by Gordon on 2021/11/9.
//

#ifndef PLANTSIO_IVY_RANDOMFALLBACK_H
#define PLANTSIO_IVY_RANDOMFALLBACK_H


#include "behaviortree_cpp_v3/control_node.h"

class RandomFallback : public BT::ControlNode {
public:
    RandomFallback(const std::string &name);

    virtual ~RandomFallback() override = default;

    virtual void halt() override;

    virtual BT::NodeStatus tick() override;

private:
    size_t current_child_idx_;

    int generate_random_index();

};


#endif //PLANTSIO_IVY_RANDOMFALLBACK_H
