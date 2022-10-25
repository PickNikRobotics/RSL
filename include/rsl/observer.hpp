#pragma once

#include <rclcpp/node.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/subscription.hpp>

#include <atomic>
#include <cassert>

namespace rsl {

/** @file */

/**
 * @brief TODO
 */
template <typename MessageType>
class Observer {
    std::atomic<MessageType> msg_;
    const std::shared_ptr<const rclcpp::Subscription<MessageType>> subscription_;

   public:
    Observer(rclcpp::Node& node, std::string const& topic, MessageType initial_value,
             rclcpp::QoS qos = rclcpp::SystemDefaultsQoS())
        : msg_(initial_value),
          subscription_(node.create_subscription<MessageType>(
              topic, qos, [this](const typename MessageType::SharedPtr msg) { msg_ = *msg; })) {
        assert(subscription_);
    }

    auto get() const { return msg_.load(); }
    operator MessageType() const { return get(); }
};

}  // namespace rsl
