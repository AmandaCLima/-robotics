// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from arm_interfaces:srv/FollowTrajectory.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "arm_interfaces/srv/follow_trajectory.hpp"


#ifndef ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__TRAITS_HPP_
#define ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "arm_interfaces/srv/detail/follow_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'data'
#include "trajectory_msgs/msg/detail/joint_trajectory__traits.hpp"

namespace arm_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const FollowTrajectory_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: data
  {
    out << "data: ";
    to_flow_style_yaml(msg.data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FollowTrajectory_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data:\n";
    to_block_style_yaml(msg.data, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FollowTrajectory_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace arm_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use arm_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const arm_interfaces::srv::FollowTrajectory_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  arm_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use arm_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const arm_interfaces::srv::FollowTrajectory_Request & msg)
{
  return arm_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<arm_interfaces::srv::FollowTrajectory_Request>()
{
  return "arm_interfaces::srv::FollowTrajectory_Request";
}

template<>
inline const char * name<arm_interfaces::srv::FollowTrajectory_Request>()
{
  return "arm_interfaces/srv/FollowTrajectory_Request";
}

template<>
struct has_fixed_size<arm_interfaces::srv::FollowTrajectory_Request>
  : std::integral_constant<bool, has_fixed_size<trajectory_msgs::msg::JointTrajectory>::value> {};

template<>
struct has_bounded_size<arm_interfaces::srv::FollowTrajectory_Request>
  : std::integral_constant<bool, has_bounded_size<trajectory_msgs::msg::JointTrajectory>::value> {};

template<>
struct is_message<arm_interfaces::srv::FollowTrajectory_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace arm_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const FollowTrajectory_Response & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FollowTrajectory_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FollowTrajectory_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace arm_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use arm_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const arm_interfaces::srv::FollowTrajectory_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  arm_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use arm_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const arm_interfaces::srv::FollowTrajectory_Response & msg)
{
  return arm_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<arm_interfaces::srv::FollowTrajectory_Response>()
{
  return "arm_interfaces::srv::FollowTrajectory_Response";
}

template<>
inline const char * name<arm_interfaces::srv::FollowTrajectory_Response>()
{
  return "arm_interfaces/srv/FollowTrajectory_Response";
}

template<>
struct has_fixed_size<arm_interfaces::srv::FollowTrajectory_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<arm_interfaces::srv::FollowTrajectory_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<arm_interfaces::srv::FollowTrajectory_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace arm_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const FollowTrajectory_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FollowTrajectory_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FollowTrajectory_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace arm_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use arm_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const arm_interfaces::srv::FollowTrajectory_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  arm_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use arm_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const arm_interfaces::srv::FollowTrajectory_Event & msg)
{
  return arm_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<arm_interfaces::srv::FollowTrajectory_Event>()
{
  return "arm_interfaces::srv::FollowTrajectory_Event";
}

template<>
inline const char * name<arm_interfaces::srv::FollowTrajectory_Event>()
{
  return "arm_interfaces/srv/FollowTrajectory_Event";
}

template<>
struct has_fixed_size<arm_interfaces::srv::FollowTrajectory_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<arm_interfaces::srv::FollowTrajectory_Event>
  : std::integral_constant<bool, has_bounded_size<arm_interfaces::srv::FollowTrajectory_Request>::value && has_bounded_size<arm_interfaces::srv::FollowTrajectory_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<arm_interfaces::srv::FollowTrajectory_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<arm_interfaces::srv::FollowTrajectory>()
{
  return "arm_interfaces::srv::FollowTrajectory";
}

template<>
inline const char * name<arm_interfaces::srv::FollowTrajectory>()
{
  return "arm_interfaces/srv/FollowTrajectory";
}

template<>
struct has_fixed_size<arm_interfaces::srv::FollowTrajectory>
  : std::integral_constant<
    bool,
    has_fixed_size<arm_interfaces::srv::FollowTrajectory_Request>::value &&
    has_fixed_size<arm_interfaces::srv::FollowTrajectory_Response>::value
  >
{
};

template<>
struct has_bounded_size<arm_interfaces::srv::FollowTrajectory>
  : std::integral_constant<
    bool,
    has_bounded_size<arm_interfaces::srv::FollowTrajectory_Request>::value &&
    has_bounded_size<arm_interfaces::srv::FollowTrajectory_Response>::value
  >
{
};

template<>
struct is_service<arm_interfaces::srv::FollowTrajectory>
  : std::true_type
{
};

template<>
struct is_service_request<arm_interfaces::srv::FollowTrajectory_Request>
  : std::true_type
{
};

template<>
struct is_service_response<arm_interfaces::srv::FollowTrajectory_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__TRAITS_HPP_
