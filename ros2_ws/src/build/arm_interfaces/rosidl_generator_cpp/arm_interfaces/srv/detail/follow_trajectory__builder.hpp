// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_interfaces:srv/FollowTrajectory.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "arm_interfaces/srv/follow_trajectory.hpp"


#ifndef ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__BUILDER_HPP_
#define ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_interfaces/srv/detail/follow_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_interfaces
{

namespace srv
{

namespace builder
{

class Init_FollowTrajectory_Request_data
{
public:
  Init_FollowTrajectory_Request_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::arm_interfaces::srv::FollowTrajectory_Request data(::arm_interfaces::srv::FollowTrajectory_Request::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_interfaces::srv::FollowTrajectory_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_interfaces::srv::FollowTrajectory_Request>()
{
  return arm_interfaces::srv::builder::Init_FollowTrajectory_Request_data();
}

}  // namespace arm_interfaces


namespace arm_interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_interfaces::srv::FollowTrajectory_Response>()
{
  return ::arm_interfaces::srv::FollowTrajectory_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace arm_interfaces


namespace arm_interfaces
{

namespace srv
{

namespace builder
{

class Init_FollowTrajectory_Event_response
{
public:
  explicit Init_FollowTrajectory_Event_response(::arm_interfaces::srv::FollowTrajectory_Event & msg)
  : msg_(msg)
  {}
  ::arm_interfaces::srv::FollowTrajectory_Event response(::arm_interfaces::srv::FollowTrajectory_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_interfaces::srv::FollowTrajectory_Event msg_;
};

class Init_FollowTrajectory_Event_request
{
public:
  explicit Init_FollowTrajectory_Event_request(::arm_interfaces::srv::FollowTrajectory_Event & msg)
  : msg_(msg)
  {}
  Init_FollowTrajectory_Event_response request(::arm_interfaces::srv::FollowTrajectory_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_FollowTrajectory_Event_response(msg_);
  }

private:
  ::arm_interfaces::srv::FollowTrajectory_Event msg_;
};

class Init_FollowTrajectory_Event_info
{
public:
  Init_FollowTrajectory_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowTrajectory_Event_request info(::arm_interfaces::srv::FollowTrajectory_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_FollowTrajectory_Event_request(msg_);
  }

private:
  ::arm_interfaces::srv::FollowTrajectory_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_interfaces::srv::FollowTrajectory_Event>()
{
  return arm_interfaces::srv::builder::Init_FollowTrajectory_Event_info();
}

}  // namespace arm_interfaces

#endif  // ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__BUILDER_HPP_
