//
// Created by Gordon on 2021/10/25.
//

#include "include/behaviortree_cpp_v3/loggers/bt_tcp_publisher.h"
#include "behaviortree_cpp_v3/flatbuffers/bt_flatbuffer_helper.h"
#include "WiFi.h"
#include "array"

namespace BT {
    std::atomic<bool> PublisherTCP::ref_count(false);

    BT::PublisherTCP::PublisherTCP(const BT::Tree &t_tree)
            : StatusChangeLogger(t_tree.rootNode()),
              m_tree(t_tree) {

        createStatusBuffer();
    }

    void PublisherTCP::createStatusBuffer() {
        m_status_buf.clear();
        applyRecursiveVisitor(m_tree.rootNode(), [this](TreeNode *node) {
            size_t index = m_status_buf.size();
            m_status_buf.resize(index + 3);
            flatbuffers::WriteScalar<uint16_t>(&m_status_buf[index], node->UID());
            flatbuffers::WriteScalar<int8_t>(&m_status_buf[index + 2],
                                             static_cast<int8_t>(convertToFlatbuffers(node->status())));
        });
    }

    void PublisherTCP::callback(Duration timestamp, const TreeNode &node, NodeStatus prev_status, NodeStatus status) {
        SerializedTransition transition = SerializeTransition(node.UID(), timestamp, prev_status, status);
        if (m_subs.empty()) {
            /* there is no subscribers at the moment */
            return;
        } else {
//            std::unique_lock<std::mutex> lock(mutex_);
//            m_transition = SerializeTransition(node.UID(), timestamp, prev_status, status);
            std::lock_guard<std::recursive_mutex> lock(m_mutex);
            m_transition_buf.push_back(transition);
            /* one or more subscribers present */
//            if (millis() - m_last_flush_t > 1) {
//                /* note flush behavior is control*/
//                flush();
//                m_last_flush_t = millis();
//            }
        }
    }

    void PublisherTCP::flush() {
        if (!WiFi.isConnected()) {
            return;
        }
//        const size_t msg_size = m_status_buf.size() + 8 + m_transition.size();
        const size_t msg_size = m_status_buf.size() + 8 + (m_transition_buf.size() * 12);
        m_tcp_buf.resize(msg_size);
        unsigned index = 0;
        flatbuffers::WriteScalar<uint32_t>(&m_tcp_buf[index], m_status_buf.size());
        index += 4;

        std::copy(m_status_buf.begin(), m_status_buf.end(), m_tcp_buf.begin() + index);
        index += m_status_buf.size();
        flatbuffers::WriteScalar<uint32_t>(&m_tcp_buf[index], m_transition_buf.size());
        index += 4;

        for (auto &transition: m_transition_buf) {
            std::copy(transition.begin(), transition.end(), m_tcp_buf.begin() + index);
            index += transition.size();
        }
        /* fixme grootIvy frequently receive bad header size */
        send(m_tcp_buf.data(), m_tcp_buf.size());
        m_transition_buf.clear();
        createStatusBuffer();
    }

    void PublisherTCP::flush_if_subscribed() {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        if (m_subs.empty()) {
            /* there is no subscribers at the moment */
            return;
        } else {
            flush();
        }
    }
}