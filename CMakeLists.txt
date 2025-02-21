cmake_minimum_required(VERSION 2.8.3)

# set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(rms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TSL Robin Map for voxelization
add_subdirectory(thirdparty/robin-map)

# Point Cloud Library
set(PCL_DIR "D:/PCL 1.13.1/cmake")
find_package(PCL REQUIRED
  NO_DEFAULT_PATH)

# Eigen
# find_package(Eigen3 REQUIRED)
set(Eigen_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIRS})
set(Eigen_LIBRARIES ${Eigen_LIBRARIES})

set(LIBRARIES
  RMS
)

# catkin_package(
# INCLUDE_DIRS include
# LIBRARIES ${LIBRARIES}
# CATKIN_DEPENDS roscpp nodelet sensor_msgs pcl_ros mrs_lib
# DEPENDS Eigen
# )
include_directories(
  include

  # ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_library(RMS
  src/histogram.cpp
  src/rms.cpp
)

# add_dependencies(RMS
# ${${PROJECT_NAME}_EXPORTED_TARGETS}
# ${catkin_EXPORTED_TARGETS}
# )
target_link_libraries(RMS
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${Eigen_INCLUDE_DIRS}
  tsl::robin_map
)

add_executable(test_rms
  src/test_rms.cpp
)
target_link_libraries(test_rms
  RMS
)

#
# add_library(RMSNodelet
# src/histogram.cpp
# src/rms.cpp
# src/rms_nodelet.cpp
# )
# add_dependencies(RMSNodelet
# ${${PROJECT_NAME}_EXPORTED_TARGETS}
# ${catkin_EXPORTED_TARGETS}
# )
# target_link_libraries(RMSNodelet
# ${catkin_LIBRARIES}
# ${PCL_LIBRARIES}
# ${Eigen_INCLUDE_DIRS}
# tsl::robin_map
# )

# # --------------------------------------------------------------
# # |                           Install                          |
# # --------------------------------------------------------------
install(TARGETS ${LIBRARIES}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)
