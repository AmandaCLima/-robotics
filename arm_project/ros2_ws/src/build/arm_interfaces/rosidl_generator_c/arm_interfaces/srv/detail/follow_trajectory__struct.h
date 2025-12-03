// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_interfaces:srv/FollowTrajectory.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "arm_interfaces/srv/follow_trajectory.h"


#ifndef ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__STRUCT_H_
#define ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "trajectory_msgs/msg/detail/joint_trajectory__struct.h"

/// Struct defined in srv/FollowTrajectory in the package arm_interfaces.
typedef struct arm_interfaces__srv__FollowTrajectory_Request
{
  trajectory_msgs__msg__JointTrajectory data;
} arm_interfaces__srv__FollowTrajectory_Request;

// Struct for a sequence of arm_interfaces__srv__FollowTrajectory_Request.
typedef struct arm_interfaces__srv__FollowTrajectory_Request__Sequence
{
  arm_interfaces__srv__FollowTrajectory_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_interfaces__srv__FollowTrajectory_Request__Sequence;

// Constants defined in the message

/// Struct defined in srv/FollowTrajectory in the package arm_interfaces.
typedef struct arm_interfaces__srv__FollowTrajectory_Response
{
  uint8_t structure_needs_at_least_one_member;
} arm_interfaces__srv__FollowTrajectory_Response;

// Struct for a sequence of arm_interfaces__srv__FollowTrajectory_Response.
typedef struct arm_interfaces__srv__FollowTrajectory_Response__Sequence
{
  arm_interfaces__srv__FollowTrajectory_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_interfaces__srv__FollowTrajectory_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  arm_interfaces__srv__FollowTrajectory_Event__request__MAX_SIZE = 1
};
// response
enum
{
  arm_interfaces__srv__FollowTrajectory_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/FollowTrajectory in the package arm_interfaces.
typedef struct arm_interfaces__srv__FollowTrajectory_Event
{
  service_msgs__msg__ServiceEventInfo info;
  arm_interfaces__srv__FollowTrajectory_Request__Sequence request;
  arm_interfaces__srv__FollowTrajectory_Response__Sequence response;
} arm_interfaces__srv__FollowTrajectory_Event;

// Struct for a sequence of arm_interfaces__srv__FollowTrajectory_Event.
typedef struct arm_interfaces__srv__FollowTrajectory_Event__Sequence
{
  arm_interfaces__srv__FollowTrajectory_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_interfaces__srv__FollowTrajectory_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_INTERFACES__SRV__DETAIL__FOLLOW_TRAJECTORY__STRUCT_H_
