// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from arm_interfaces:srv/FollowTrajectory.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "arm_interfaces/srv/detail/follow_trajectory__struct.h"
#include "arm_interfaces/srv/detail/follow_trajectory__type_support.h"
#include "arm_interfaces/srv/detail/follow_trajectory__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace arm_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _FollowTrajectory_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _FollowTrajectory_Request_type_support_ids_t;

static const _FollowTrajectory_Request_type_support_ids_t _FollowTrajectory_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _FollowTrajectory_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _FollowTrajectory_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _FollowTrajectory_Request_type_support_symbol_names_t _FollowTrajectory_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, arm_interfaces, srv, FollowTrajectory_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, arm_interfaces, srv, FollowTrajectory_Request)),
  }
};

typedef struct _FollowTrajectory_Request_type_support_data_t
{
  void * data[2];
} _FollowTrajectory_Request_type_support_data_t;

static _FollowTrajectory_Request_type_support_data_t _FollowTrajectory_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _FollowTrajectory_Request_message_typesupport_map = {
  2,
  "arm_interfaces",
  &_FollowTrajectory_Request_message_typesupport_ids.typesupport_identifier[0],
  &_FollowTrajectory_Request_message_typesupport_symbol_names.symbol_name[0],
  &_FollowTrajectory_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t FollowTrajectory_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_FollowTrajectory_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &arm_interfaces__srv__FollowTrajectory_Request__get_type_hash,
  &arm_interfaces__srv__FollowTrajectory_Request__get_type_description,
  &arm_interfaces__srv__FollowTrajectory_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace arm_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, arm_interfaces, srv, FollowTrajectory_Request)() {
  return &::arm_interfaces::srv::rosidl_typesupport_c::FollowTrajectory_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "arm_interfaces/srv/detail/follow_trajectory__struct.h"
// already included above
// #include "arm_interfaces/srv/detail/follow_trajectory__type_support.h"
// already included above
// #include "arm_interfaces/srv/detail/follow_trajectory__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace arm_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _FollowTrajectory_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _FollowTrajectory_Response_type_support_ids_t;

static const _FollowTrajectory_Response_type_support_ids_t _FollowTrajectory_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _FollowTrajectory_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _FollowTrajectory_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _FollowTrajectory_Response_type_support_symbol_names_t _FollowTrajectory_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, arm_interfaces, srv, FollowTrajectory_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, arm_interfaces, srv, FollowTrajectory_Response)),
  }
};

typedef struct _FollowTrajectory_Response_type_support_data_t
{
  void * data[2];
} _FollowTrajectory_Response_type_support_data_t;

static _FollowTrajectory_Response_type_support_data_t _FollowTrajectory_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _FollowTrajectory_Response_message_typesupport_map = {
  2,
  "arm_interfaces",
  &_FollowTrajectory_Response_message_typesupport_ids.typesupport_identifier[0],
  &_FollowTrajectory_Response_message_typesupport_symbol_names.symbol_name[0],
  &_FollowTrajectory_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t FollowTrajectory_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_FollowTrajectory_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &arm_interfaces__srv__FollowTrajectory_Response__get_type_hash,
  &arm_interfaces__srv__FollowTrajectory_Response__get_type_description,
  &arm_interfaces__srv__FollowTrajectory_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace arm_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, arm_interfaces, srv, FollowTrajectory_Response)() {
  return &::arm_interfaces::srv::rosidl_typesupport_c::FollowTrajectory_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "arm_interfaces/srv/detail/follow_trajectory__struct.h"
// already included above
// #include "arm_interfaces/srv/detail/follow_trajectory__type_support.h"
// already included above
// #include "arm_interfaces/srv/detail/follow_trajectory__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace arm_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _FollowTrajectory_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _FollowTrajectory_Event_type_support_ids_t;

static const _FollowTrajectory_Event_type_support_ids_t _FollowTrajectory_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _FollowTrajectory_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _FollowTrajectory_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _FollowTrajectory_Event_type_support_symbol_names_t _FollowTrajectory_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, arm_interfaces, srv, FollowTrajectory_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, arm_interfaces, srv, FollowTrajectory_Event)),
  }
};

typedef struct _FollowTrajectory_Event_type_support_data_t
{
  void * data[2];
} _FollowTrajectory_Event_type_support_data_t;

static _FollowTrajectory_Event_type_support_data_t _FollowTrajectory_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _FollowTrajectory_Event_message_typesupport_map = {
  2,
  "arm_interfaces",
  &_FollowTrajectory_Event_message_typesupport_ids.typesupport_identifier[0],
  &_FollowTrajectory_Event_message_typesupport_symbol_names.symbol_name[0],
  &_FollowTrajectory_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t FollowTrajectory_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_FollowTrajectory_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &arm_interfaces__srv__FollowTrajectory_Event__get_type_hash,
  &arm_interfaces__srv__FollowTrajectory_Event__get_type_description,
  &arm_interfaces__srv__FollowTrajectory_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace arm_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, arm_interfaces, srv, FollowTrajectory_Event)() {
  return &::arm_interfaces::srv::rosidl_typesupport_c::FollowTrajectory_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "arm_interfaces/srv/detail/follow_trajectory__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace arm_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _FollowTrajectory_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _FollowTrajectory_type_support_ids_t;

static const _FollowTrajectory_type_support_ids_t _FollowTrajectory_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _FollowTrajectory_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _FollowTrajectory_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _FollowTrajectory_type_support_symbol_names_t _FollowTrajectory_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, arm_interfaces, srv, FollowTrajectory)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, arm_interfaces, srv, FollowTrajectory)),
  }
};

typedef struct _FollowTrajectory_type_support_data_t
{
  void * data[2];
} _FollowTrajectory_type_support_data_t;

static _FollowTrajectory_type_support_data_t _FollowTrajectory_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _FollowTrajectory_service_typesupport_map = {
  2,
  "arm_interfaces",
  &_FollowTrajectory_service_typesupport_ids.typesupport_identifier[0],
  &_FollowTrajectory_service_typesupport_symbol_names.symbol_name[0],
  &_FollowTrajectory_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t FollowTrajectory_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_FollowTrajectory_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &FollowTrajectory_Request_message_type_support_handle,
  &FollowTrajectory_Response_message_type_support_handle,
  &FollowTrajectory_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    arm_interfaces,
    srv,
    FollowTrajectory
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    arm_interfaces,
    srv,
    FollowTrajectory
  ),
  &arm_interfaces__srv__FollowTrajectory__get_type_hash,
  &arm_interfaces__srv__FollowTrajectory__get_type_description,
  &arm_interfaces__srv__FollowTrajectory__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace arm_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, arm_interfaces, srv, FollowTrajectory)() {
  return &::arm_interfaces::srv::rosidl_typesupport_c::FollowTrajectory_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
