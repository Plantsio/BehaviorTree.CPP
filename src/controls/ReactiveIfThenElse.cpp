//
// Created by sungaoran on 2021/11/9.
//

#include "behaviortree_cpp_v3/controls/ReactiveIfThenElse.h"
ReactiveIfThenElse::ReactiveIfThenElse(const std::string &name)
        : ControlNode::ControlNode(name, {} )
        , child_idx_(0)
{
    setRegistrationID("IfThenElse");
}

void ReactiveIfThenElse::halt()
{
    child_idx_ = 0;
    ControlNode::halt();
}

BT::NodeStatus ReactiveIfThenElse::tick()
{
    const size_t children_count = children_nodes_.size();

    if(children_count != 2 && children_count != 3)
    {
        throw std::logic_error("IfThenElseNode must have either 2 or 3 children");
    }

    setStatus(BT::NodeStatus::RUNNING);

    if (child_idx_ == 0)
    {
        BT::NodeStatus condition_status = children_nodes_[0]->executeTick();

        if (condition_status == BT::NodeStatus::RUNNING)
        {
            return condition_status;
        }
        else if (condition_status == BT::NodeStatus::SUCCESS)
        {
            child_idx_ = 1;
        }
        else if (condition_status == BT::NodeStatus::FAILURE)
        {
            if( children_count == 3){
                child_idx_ = 2;
            }
            else{
                return condition_status;
            }
        }
    }else{
        /* for children that return running, the following tick will be reactive */
        /* check condition */
        BT::NodeStatus condition_status = children_nodes_[0]->executeTick();
        if (condition_status == BT::NodeStatus::RUNNING){
            /* return running if if-condition is still checking */
            return condition_status;
        }
        /* reactive part */
        if ((child_idx_ == 1 && condition_status == BT::NodeStatus::FAILURE) || (child_idx_ ==2 && condition_status == BT::NodeStatus::SUCCESS)){
            haltChildren();
            child_idx_ = 0;
            return BT::NodeStatus::FAILURE;
        }
        /* child is allowed to tick now, so not return */
    }
    // not an else
    /* first time just like a normal if-then-else node */
    if (child_idx_ > 0)
    {
        BT::NodeStatus status = children_nodes_[child_idx_]->executeTick();
        if (status == BT::NodeStatus::RUNNING)
        {
            return BT::NodeStatus::RUNNING;
        }
        else{
            haltChildren();
            child_idx_ = 0;
            return status;
        }
    }

    throw std::logic_error("Something unexpected happened in IfThenElseNode");
}