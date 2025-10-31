# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_projeto_braco_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED projeto_braco_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(projeto_braco_FOUND FALSE)
  elseif(NOT projeto_braco_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(projeto_braco_FOUND FALSE)
  endif()
  return()
endif()
set(_projeto_braco_CONFIG_INCLUDED TRUE)

# output package information
if(NOT projeto_braco_FIND_QUIETLY)
  message(STATUS "Found projeto_braco: 0.0.0 (${projeto_braco_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'projeto_braco' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT projeto_braco_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(projeto_braco_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${projeto_braco_DIR}/${_extra}")
endforeach()
