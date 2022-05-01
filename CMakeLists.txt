project(sample_app)
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

add_executable(sample_app)

option(SYCL_BACKEND "Enable selected SYCL backend" "")
option(SYCL_DEVICE "Select target SYCL device" GPU)

target_include_directories(sample_app
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(sample_app PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src/vector_add.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/sample_app.cpp
)

set_target_properties(sample_app PROPERTIES
	PUBLIC_HEADER
	${CMAKE_CURRENT_SOURCE_DIR}/include/vector_add.hpp
)

# Handle multiple devices
set(CPU_DEVICE 0)
set(GPU_DEVICE 1)
set(HOST_DEVICE 2)

set(device_value -1)
if(SYCL_DEVICE STREQUAL CPU)
	set(device_value ${CPU_DEVICE})
elseif(SYCL_DEVICE STREQUAL GPU)
	set(device_value ${GPU_DEVICE})
elseif(SYCL_DEVICE STREQUAL HOST)
	set(device_value ${HOST_DEVICE})
endif()

add_compile_definitions(sample_app
	CPU_DEVICE=${CPU_DEVICE}
	GPU_DEVICE=${GPU_DEVICE}
	HOST_DEVICE=${HOST_DEVICE}
	DEVICE_VALUE=${device_value}
)

if(SYCL_BACKEND STREQUAL hipSYCL)
	find_package(hipSYCL REQUIRED)
	add_sycl_to_target(TARGET sample_app)
endif()

message(STATUS "SYCL_BACKEND: ${SYCL_BACKEND}")
message(STATUS "SYCL_DEVICE: ${SYCL_DEVICE}")