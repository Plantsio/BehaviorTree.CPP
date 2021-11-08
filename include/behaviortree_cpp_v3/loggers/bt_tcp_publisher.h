//
// Created by Gordon on 2021/10/25.
//

#ifndef PLANTSIO_IVY_BT_UDP_PUBLISHER_H
#define PLANTSIO_IVY_BT_UDP_PUBLISHER_H

#include "abstract_logger.h"
#include "WiFiClient.h"
#include "tool/TcpPublisher.h"

namespace BT {
    class PublisherTCP : public StatusChangeLogger, public TcpPublisher{
        static std::atomic<bool> ref_count;
    public:
        PublisherTCP(const BT::Tree &t_tree);

    private:
        virtual void callback(Duration timestamp, const TreeNode &node, NodeStatus prev_status,
                              NodeStatus status) override;

        virtual void flush() override;

        const BT::Tree &m_tree;
        std::vector<uint8_t> m_status_buf;
        std::vector<uint8_t> m_tcp_buf;
//        SerializedTransition m_transition;
        std::vector<SerializedTransition> m_transition_buf;
        std::vector<uint8_t> m_tcp_data;
        uint32_t m_last_flush_t = 0;

        void createStatusBuffer();

        std::mutex mutex_;
    };
}


#endif //PLANTSIO_IVY_BT_UDP_PUBLISHER_H
