//
// Created by Gordon on 2022/3/18.
//

#include "behaviortree_cpp_v3/controls/ControlAnim.h"
#ifdef Ivy
#include "Anim/drivers/EmoDriver.h"

BT::NodeStatus BT::ControlAnim::onStart() {
    auto priority = getInput<int>(ANIMATION_CONTROL_PRIORITY);
    Anim anim = Anim({},priority.value(),[this](Anim::anim_complete_ret ret){this->set_status(ret);});
    for (auto child:children()){
        auto n = child->getInput<int>(ANIMATION_NODE_N);
        anim.add_unit(AnimUnit(child->name(),n.value()));
        log_d("debug-bt add %s | %d",child->name().c_str(),n.value());
    }
    bool ret = EmoDriver::instance().set_current_anim(anim);
    if (ret) {
        return NodeStatus::RUNNING;
    }else{
        return NodeStatus::FAILURE;
    }
}

#else
BT::NodeStatus BT::ControlAnim::onStart(){
    return NodeStatus::RUNNING;
}
#endif

void BT::ControlAnim::onHalted() {
}

BT::NodeStatus BT::ControlAnim::tick() {
    const NodeStatus initial_status = status();

    if( initial_status == NodeStatus::IDLE )
    {
        NodeStatus new_status = onStart();
        return new_status;
    }
    //------------------------------------------
//    if( initial_status == NodeStatus::RUNNING )
//    {
//        NodeStatus new_status = onRunning();
//        if( new_status == NodeStatus::IDLE)
//        {
//            throw std::logic_error("AsyncActionNode2::onRunning() must not return IDLE");
//        }
//        return new_status;
//    }
    //------------------------------------------
    return initial_status;


    return BT::NodeStatus::SUCCESS;
}


void BT::ControlAnim::halt() {
    if( status() == NodeStatus::RUNNING)
    {
        onHalted();
    }
    setStatus(NodeStatus::IDLE);
}