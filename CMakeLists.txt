project(sample_app)
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

add_executable(sample_app)

option(SYCL_BACKEND "Enable selected SYCL backend" "")

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

if(SYCL_BACKEND STREQUAL hipSYCL)
	find_package(hipSYCL REQUIRED)
	set(CXX_COMPILER syclcc)
	add_sycl_to_target(TARGET sample_app)
elseif(SYCL_BACKEND STREQUAL DPCPP)
	# Print
	# Set clang++ as CXX compiler
	set(CXX_COMPILER clang++)
	#Append -O3 TO CXX_FLAGS
	set(CMAKE_CXX_FLAGS "-fsycl ${CMAKE_CXX_FLAGS}")
endif()