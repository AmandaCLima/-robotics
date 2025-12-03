// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from arm_interfaces:srv/FollowTrajectory.idl
// generated code does not contain a copyright notice
#include "arm_interfaces/srv/detail/follow_trajectory__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `data`
#include "trajectory_msgs/msg/detail/joint_trajectory__functions.h"

bool
arm_interfaces__srv__FollowTrajectory_Request__init(arm_interfaces__srv__FollowTrajectory_Request * msg)
{
  if (!msg) {
    return false;
  }
  // data
  if (!trajectory_msgs__msg__JointTrajectory__init(&msg->data)) {
    arm_interfaces__srv__FollowTrajectory_Request__fini(msg);
    return false;
  }
  return true;
}

void
arm_interfaces__srv__FollowTrajectory_Request__fini(arm_interfaces__srv__FollowTrajectory_Request * msg)
{
  if (!msg) {
    return;
  }
  // data
  trajectory_msgs__msg__JointTrajectory__fini(&msg->data);
}

bool
arm_interfaces__srv__FollowTrajectory_Request__are_equal(const arm_interfaces__srv__FollowTrajectory_Request * lhs, const arm_interfaces__srv__FollowTrajectory_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // data
  if (!trajectory_msgs__msg__JointTrajectory__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  return true;
}

bool
arm_interfaces__srv__FollowTrajectory_Request__copy(
  const arm_interfaces__srv__FollowTrajectory_Request * input,
  arm_interfaces__srv__FollowTrajectory_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // data
  if (!trajectory_msgs__msg__JointTrajectory__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  return true;
}

arm_interfaces__srv__FollowTrajectory_Request *
arm_interfaces__srv__FollowTrajectory_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Request * msg = (arm_interfaces__srv__FollowTrajectory_Request *)allocator.allocate(sizeof(arm_interfaces__srv__FollowTrajectory_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(arm_interfaces__srv__FollowTrajectory_Request));
  bool success = arm_interfaces__srv__FollowTrajectory_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
arm_interfaces__srv__FollowTrajectory_Request__destroy(arm_interfaces__srv__FollowTrajectory_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    arm_interfaces__srv__FollowTrajectory_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
arm_interfaces__srv__FollowTrajectory_Request__Sequence__init(arm_interfaces__srv__FollowTrajectory_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Request * data = NULL;

  if (size) {
    data = (arm_interfaces__srv__FollowTrajectory_Request *)allocator.zero_allocate(size, sizeof(arm_interfaces__srv__FollowTrajectory_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = arm_interfaces__srv__FollowTrajectory_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        arm_interfaces__srv__FollowTrajectory_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
arm_interfaces__srv__FollowTrajectory_Request__Sequence__fini(arm_interfaces__srv__FollowTrajectory_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      arm_interfaces__srv__FollowTrajectory_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

arm_interfaces__srv__FollowTrajectory_Request__Sequence *
arm_interfaces__srv__FollowTrajectory_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Request__Sequence * array = (arm_interfaces__srv__FollowTrajectory_Request__Sequence *)allocator.allocate(sizeof(arm_interfaces__srv__FollowTrajectory_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = arm_interfaces__srv__FollowTrajectory_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
arm_interfaces__srv__FollowTrajectory_Request__Sequence__destroy(arm_interfaces__srv__FollowTrajectory_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    arm_interfaces__srv__FollowTrajectory_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
arm_interfaces__srv__FollowTrajectory_Request__Sequence__are_equal(const arm_interfaces__srv__FollowTrajectory_Request__Sequence * lhs, const arm_interfaces__srv__FollowTrajectory_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!arm_interfaces__srv__FollowTrajectory_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
arm_interfaces__srv__FollowTrajectory_Request__Sequence__copy(
  const arm_interfaces__srv__FollowTrajectory_Request__Sequence * input,
  arm_interfaces__srv__FollowTrajectory_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(arm_interfaces__srv__FollowTrajectory_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    arm_interfaces__srv__FollowTrajectory_Request * data =
      (arm_interfaces__srv__FollowTrajectory_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!arm_interfaces__srv__FollowTrajectory_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          arm_interfaces__srv__FollowTrajectory_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!arm_interfaces__srv__FollowTrajectory_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
arm_interfaces__srv__FollowTrajectory_Response__init(arm_interfaces__srv__FollowTrajectory_Response * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
arm_interfaces__srv__FollowTrajectory_Response__fini(arm_interfaces__srv__FollowTrajectory_Response * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
arm_interfaces__srv__FollowTrajectory_Response__are_equal(const arm_interfaces__srv__FollowTrajectory_Response * lhs, const arm_interfaces__srv__FollowTrajectory_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
arm_interfaces__srv__FollowTrajectory_Response__copy(
  const arm_interfaces__srv__FollowTrajectory_Response * input,
  arm_interfaces__srv__FollowTrajectory_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

arm_interfaces__srv__FollowTrajectory_Response *
arm_interfaces__srv__FollowTrajectory_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Response * msg = (arm_interfaces__srv__FollowTrajectory_Response *)allocator.allocate(sizeof(arm_interfaces__srv__FollowTrajectory_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(arm_interfaces__srv__FollowTrajectory_Response));
  bool success = arm_interfaces__srv__FollowTrajectory_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
arm_interfaces__srv__FollowTrajectory_Response__destroy(arm_interfaces__srv__FollowTrajectory_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    arm_interfaces__srv__FollowTrajectory_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
arm_interfaces__srv__FollowTrajectory_Response__Sequence__init(arm_interfaces__srv__FollowTrajectory_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Response * data = NULL;

  if (size) {
    data = (arm_interfaces__srv__FollowTrajectory_Response *)allocator.zero_allocate(size, sizeof(arm_interfaces__srv__FollowTrajectory_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = arm_interfaces__srv__FollowTrajectory_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        arm_interfaces__srv__FollowTrajectory_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
arm_interfaces__srv__FollowTrajectory_Response__Sequence__fini(arm_interfaces__srv__FollowTrajectory_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      arm_interfaces__srv__FollowTrajectory_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

arm_interfaces__srv__FollowTrajectory_Response__Sequence *
arm_interfaces__srv__FollowTrajectory_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Response__Sequence * array = (arm_interfaces__srv__FollowTrajectory_Response__Sequence *)allocator.allocate(sizeof(arm_interfaces__srv__FollowTrajectory_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = arm_interfaces__srv__FollowTrajectory_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
arm_interfaces__srv__FollowTrajectory_Response__Sequence__destroy(arm_interfaces__srv__FollowTrajectory_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    arm_interfaces__srv__FollowTrajectory_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
arm_interfaces__srv__FollowTrajectory_Response__Sequence__are_equal(const arm_interfaces__srv__FollowTrajectory_Response__Sequence * lhs, const arm_interfaces__srv__FollowTrajectory_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!arm_interfaces__srv__FollowTrajectory_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
arm_interfaces__srv__FollowTrajectory_Response__Sequence__copy(
  const arm_interfaces__srv__FollowTrajectory_Response__Sequence * input,
  arm_interfaces__srv__FollowTrajectory_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(arm_interfaces__srv__FollowTrajectory_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    arm_interfaces__srv__FollowTrajectory_Response * data =
      (arm_interfaces__srv__FollowTrajectory_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!arm_interfaces__srv__FollowTrajectory_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          arm_interfaces__srv__FollowTrajectory_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!arm_interfaces__srv__FollowTrajectory_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "arm_interfaces/srv/detail/follow_trajectory__functions.h"

bool
arm_interfaces__srv__FollowTrajectory_Event__init(arm_interfaces__srv__FollowTrajectory_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    arm_interfaces__srv__FollowTrajectory_Event__fini(msg);
    return false;
  }
  // request
  if (!arm_interfaces__srv__FollowTrajectory_Request__Sequence__init(&msg->request, 0)) {
    arm_interfaces__srv__FollowTrajectory_Event__fini(msg);
    return false;
  }
  // response
  if (!arm_interfaces__srv__FollowTrajectory_Response__Sequence__init(&msg->response, 0)) {
    arm_interfaces__srv__FollowTrajectory_Event__fini(msg);
    return false;
  }
  return true;
}

void
arm_interfaces__srv__FollowTrajectory_Event__fini(arm_interfaces__srv__FollowTrajectory_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  arm_interfaces__srv__FollowTrajectory_Request__Sequence__fini(&msg->request);
  // response
  arm_interfaces__srv__FollowTrajectory_Response__Sequence__fini(&msg->response);
}

bool
arm_interfaces__srv__FollowTrajectory_Event__are_equal(const arm_interfaces__srv__FollowTrajectory_Event * lhs, const arm_interfaces__srv__FollowTrajectory_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!arm_interfaces__srv__FollowTrajectory_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!arm_interfaces__srv__FollowTrajectory_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
arm_interfaces__srv__FollowTrajectory_Event__copy(
  const arm_interfaces__srv__FollowTrajectory_Event * input,
  arm_interfaces__srv__FollowTrajectory_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!arm_interfaces__srv__FollowTrajectory_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!arm_interfaces__srv__FollowTrajectory_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

arm_interfaces__srv__FollowTrajectory_Event *
arm_interfaces__srv__FollowTrajectory_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Event * msg = (arm_interfaces__srv__FollowTrajectory_Event *)allocator.allocate(sizeof(arm_interfaces__srv__FollowTrajectory_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(arm_interfaces__srv__FollowTrajectory_Event));
  bool success = arm_interfaces__srv__FollowTrajectory_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
arm_interfaces__srv__FollowTrajectory_Event__destroy(arm_interfaces__srv__FollowTrajectory_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    arm_interfaces__srv__FollowTrajectory_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
arm_interfaces__srv__FollowTrajectory_Event__Sequence__init(arm_interfaces__srv__FollowTrajectory_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Event * data = NULL;

  if (size) {
    data = (arm_interfaces__srv__FollowTrajectory_Event *)allocator.zero_allocate(size, sizeof(arm_interfaces__srv__FollowTrajectory_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = arm_interfaces__srv__FollowTrajectory_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        arm_interfaces__srv__FollowTrajectory_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
arm_interfaces__srv__FollowTrajectory_Event__Sequence__fini(arm_interfaces__srv__FollowTrajectory_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      arm_interfaces__srv__FollowTrajectory_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

arm_interfaces__srv__FollowTrajectory_Event__Sequence *
arm_interfaces__srv__FollowTrajectory_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_interfaces__srv__FollowTrajectory_Event__Sequence * array = (arm_interfaces__srv__FollowTrajectory_Event__Sequence *)allocator.allocate(sizeof(arm_interfaces__srv__FollowTrajectory_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = arm_interfaces__srv__FollowTrajectory_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
arm_interfaces__srv__FollowTrajectory_Event__Sequence__destroy(arm_interfaces__srv__FollowTrajectory_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    arm_interfaces__srv__FollowTrajectory_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
arm_interfaces__srv__FollowTrajectory_Event__Sequence__are_equal(const arm_interfaces__srv__FollowTrajectory_Event__Sequence * lhs, const arm_interfaces__srv__FollowTrajectory_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!arm_interfaces__srv__FollowTrajectory_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
arm_interfaces__srv__FollowTrajectory_Event__Sequence__copy(
  const arm_interfaces__srv__FollowTrajectory_Event__Sequence * input,
  arm_interfaces__srv__FollowTrajectory_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(arm_interfaces__srv__FollowTrajectory_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    arm_interfaces__srv__FollowTrajectory_Event * data =
      (arm_interfaces__srv__FollowTrajectory_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!arm_interfaces__srv__FollowTrajectory_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          arm_interfaces__srv__FollowTrajectory_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!arm_interfaces__srv__FollowTrajectory_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
