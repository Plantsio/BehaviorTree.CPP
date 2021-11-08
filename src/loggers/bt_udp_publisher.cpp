////
//// Created by Gordon on 2021/10/25.
////
//
//#include "include/behaviortree_cpp_v3/loggers/bt_udp_publisher.h"
//#include "behaviortree_cpp_v3/flatbuffers/bt_flatbuffer_helper.h"
//#include "WiFi.h"
//
//namespace BT {
//    std::atomic<bool> PublisherUDP::ref_count(false);
//
//    struct PublisherUDP::Subscriber {
//        Subscriber(IPAddress t_ip, unsigned t_port) : m_ip(t_ip), m_port(t_port) {}
//
//        IPAddress m_ip;
//        unsigned m_port;
//    };
//
//    BT::PublisherUDP::PublisherUDP(const BT::Tree &t_tree)
//            : StatusChangeLogger(t_tree.rootNode()),
//              m_tree(t_tree) {
//        bool expected = false;
//        if (!ref_count.compare_exchange_strong(expected, true)) {
//            throw LogicError("Only one instance of PublisherZMQ shall be created");
//        }
//
////        std::vector<uint8_t> tree_buffer_;
////        tree_buffer_.resize(builder.GetSize());
////        memcpy(tree_buffer_.data(), builder.GetBufferPointer(), builder.GetSize());
//
//        createStatusBuffer();
//    }
//
//    PublisherUDP::~PublisherUDP() {
//        if (WiFi.isConnected()) {
//            m_udp.close();
//        }
//        ref_count = false;
//    }
//
//    void PublisherUDP::createStatusBuffer() {
//        status_buffer_.clear();
//        applyRecursiveVisitor(m_tree.rootNode(), [this](TreeNode *node) {
//            size_t index = status_buffer_.size();
//            status_buffer_.resize(index + 3);
//            flatbuffers::WriteScalar<uint16_t>(&status_buffer_[index], node->UID());
//            flatbuffers::WriteScalar<int8_t>(&status_buffer_[index + 2],
//                                             static_cast<int8_t>(convertToFlatbuffers(node->status())));
//        });
//    }
//
//    void PublisherUDP::callback(Duration timestamp, const TreeNode &node, NodeStatus prev_status, NodeStatus status) {
//        log_v("p-udp cb");
//        if (m_subs.empty()) {
//            /* there is no subscribers at the moment */
//            return;
//        } else {
//            SerializedTransition transition =
//                    SerializeTransition(node.UID(), timestamp, prev_status, status);
//            {
//                std::unique_lock<std::mutex> lock(mutex_);
//                transition_buffer_.push_back(transition);
//            }
//            /* one or more subscribers present */
//            flush();
//        }
//    }
//
//    void PublisherUDP::flush() {
//        std::unique_lock<std::mutex> lock(mutex_);
//        if (!WiFi.isConnected()) {
//            return;
//        }
//
//        const size_t msg_size = status_buffer_.size() + 8 + (transition_buffer_.size() * 12);
//        AsyncUDPMessage message(msg_size);
//        uint8_t *data_ptr = message.data();
//
//        // first 4 bytes are the side of the header
//        flatbuffers::WriteScalar<uint32_t>(data_ptr, static_cast<uint32_t>(status_buffer_.size()));
//        data_ptr += sizeof(uint32_t);
//        // copy the header part
//        memcpy(data_ptr, status_buffer_.data(), status_buffer_.size());
//        data_ptr += status_buffer_.size();
//
//        // first 4 bytes are the side of the transition buffer
//        flatbuffers::WriteScalar<uint32_t>(data_ptr, static_cast<uint32_t>(transition_buffer_.size()));
//        data_ptr += sizeof(uint32_t);
//
//        for (auto &transition: transition_buffer_) {
//            memcpy(data_ptr, transition.data(), transition.size());
//            data_ptr += transition.size();
//        }
//        transition_buffer_.clear();
//        createStatusBuffer();
//
//        for (auto sub: m_subs) {
//            /* send to all subscribers */
//            m_udp.sendTo(message, sub.m_ip, sub.m_port);
//            log_d("p-udp sent %d data to %s:%d", message.length(),sub.m_ip.toString().c_str(), sub.m_port);
//        }
//    }
//
//    void PublisherUDP::add_sub(IPAddress ip, unsigned int port) {
//        for (auto sub:m_subs) {
//            if (sub.m_ip != ip) {
//                m_subs.push_back(Subscriber(ip, port));
//            }
//        }
//    }
//
//    void PublisherUDP::remove_sub(IPAddress ip) {
//        for (unsigned i = 0; i < m_subs.size(); i++) {
//            if (m_subs[i].m_ip == ip) {
//                m_subs.erase(m_subs.begin() + i);
//            }
//        }
//    }
//}