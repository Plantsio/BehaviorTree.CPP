//
// Created by Gordon on 2022/3/18.
//

#ifndef PLANTSIO_IVY_CONTROLANIM_H
#define PLANTSIO_IVY_CONTROLANIM_H

#include "behaviortree_cpp_v3/control_node.h"
#include "behaviortree_cpp_v3/config.h"

#define ANIMATION_CONTROL_PRIORITY "priority"

#ifdef Ivy

#endif
namespace BT {
    class ControlAnim : public ControlNode {
    public:
        explicit ControlAnim(const std::string &name) : ControlNode(name, {}) {
            setRegistrationID("ControlAnim");
        }

        void halt() override;

    private:
#ifdef Ivy

       // void set_status(Anim::anim_complete_ret t_status);

       // std::weak_ptr<Anim> anim;
#endif

        NodeStatus onStart();

        void onHalted();

        NodeStatus tick() override;
    };
}

#endif //PLANTSIO_IVY_CONTROLANIM_H
