//
// Created by Gordon on 2022/3/18.
//

#include "behaviortree_cpp_v3/controls/ControlAnim.h"

#ifdef Ivy

//#include "Anim/drivers/EmoDriver.h"
#include "Engine/Behavior/EventDispatcher.h"

//BT::NodeStatus BT::ControlAnim::onStart() {
//    auto a = Anim::create({}, [this](Anim::anim_complete_ret ret) { this->set_status(ret); });
//    for (auto child: children()) {
//        Optional<int> ret = child->getInput<int>(ANIMATION_NODE_N);
//        if (!ret) {
//            return NodeStatus::FAILURE;
//        }
//        a->add_unit(AnimUnit(child->name(), ret.value()));
//        log_v("debug-bt add %s | %d", child->name().c_str(), n.value());
//    }
//    anim = a;
//    bool ret = EmoDriver::instance().set_current_anim(a);
//    if (ret) {
//        return NodeStatus::RUNNING;
//    } else {
//        return NodeStatus::FAILURE;
//    }
//}


//void BT::ControlAnim::onHalted() {
//    std::shared_ptr<Anim> a = anim.lock();
//    if (a) {
//        a->set_complete(Anim::interrupted);
//    }
//}

//void BT::ControlAnim::set_status(Anim::anim_complete_ret t_status) {
//            if (t_status == Anim::success) {
//                setStatus(NodeStatus::SUCCESS);
//            } else if (t_status == Anim::failure || t_status == Anim::interrupted) {
//                setStatus(NodeStatus::FAILURE);
//            }
//            EventDispatcher::instance().dispatch(blank_tick);
//}

#else

BT::NodeStatus BT::ControlAnim::onStart() {
    return NodeStatus::RUNNING;
}

void BT::ControlAnim::onHalted() {}

//void BT::ControlAnim::set_status(Anim::anim_complete_ret t_status){}

#endif


BT::NodeStatus BT::ControlAnim::tick() {
    const NodeStatus initial_status = status();

    if (initial_status == NodeStatus::IDLE) {
        NodeStatus new_status = onStart();
        return new_status;
    }
    return initial_status;
}


void BT::ControlAnim::halt() {
    if (status() == NodeStatus::RUNNING) {
        onHalted();
    }
    ControlNode::halt();
}
