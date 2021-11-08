////
//// Created by Gordon on 2021/10/25.
////
//
//#ifndef PLANTSIO_IVY_BT_UDP_PUBLISHER_H
//#define PLANTSIO_IVY_BT_UDP_PUBLISHER_H
//
//#include "abstract_logger.h"
//#include <AsyncUDP.h>
//
//namespace BT {
//    struct subscriber{
//        IPAddress ip;
//        unsigned port;
//    };
//
//
//    class PublisherUDP : public StatusChangeLogger {
//        static std::atomic<bool> ref_count;
//    public:
//        PublisherUDP(const BT::Tree &t_tree);
//
//        virtual ~PublisherUDP();
//
//        /**
//         * add a subscriber by ip and port
//         * @param ip
//         * @param port
//         */
//        void add_sub(IPAddress ip,unsigned port);
//
//        /**
//         * delete a subscriber by ip
//         * @param ip
//         */
//        void remove_sub(IPAddress ip);
//
//    private:
//        virtual void callback(Duration timestamp, const TreeNode &node, NodeStatus prev_status,
//                              NodeStatus status) override;
//
//        virtual void flush() override;
//
//        const BT::Tree &m_tree;
//        std::vector<uint8_t> status_buffer_;
//        std::vector<SerializedTransition> transition_buffer_;
//
//        void createStatusBuffer();
//
//        std::mutex mutex_;
//
//        AsyncUDP m_udp;
//        struct Subscriber;
//        std::vector<Subscriber> m_subs;
//    };
//}
//
//
//#endif //PLANTSIO_IVY_BT_UDP_PUBLISHER_H
