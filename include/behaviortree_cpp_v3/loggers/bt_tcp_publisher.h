//
// Created by Gordon on 2021/10/25.
//

#ifndef PLANTSIO_IVY_BT_UDP_PUBLISHER_H
#define PLANTSIO_IVY_BT_UDP_PUBLISHER_H

#include "abstract_logger.h"
#include "WiFiClient.h"
#include "TcpPublisher.h"

namespace BT {
    class PublisherTCP : public StatusChangeLogger, public TcpPublisher{
        static std::atomic<bool> ref_count;
    public:
        explicit PublisherTCP(const BT::Tree &t_tree);

        void flush_if_subscribed();

    private:
        void callback(Duration timestamp, const TreeNode &node, NodeStatus prev_status,
                              NodeStatus status) override;

        void flush() override;

        const BT::Tree &m_tree;
        std::vector<uint8_t> m_status_buf;
        std::vector<uint8_t> m_tcp_buf;
//        SerializedTransition m_transition;
        std::vector<SerializedTransition> m_transition_buf;
        std::vector<uint8_t> m_tcp_data;
        uint32_t m_last_flush_t = 0;

        void createStatusBuffer();

        std::recursive_mutex m_mutex;
    };
}


#endif //PLANTSIO_IVY_BT_UDP_PUBLISHER_H
