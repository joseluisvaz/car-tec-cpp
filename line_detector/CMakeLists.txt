cmake_minimum_required(VERSION 2.8.3)
project(line_detector)


#set(OpenCV_INCLUDE_DIRS "/opt/ros/kinetic/include/opencv-3.3.1/")



#set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect opencv_contrib opencv_legacy opencv_gpu)
##set(OpenCV_DIR /usr/share/OpenCV)

## Use C++11
add_definitions(-std=c++11)
## By adding -Wall and -Werror, the compiler does not ignore warnings anymore,
## enforcing cleaner code.
#add_definitions(-std=c++11 -Wall -Werror)

## Find catkin macros and libraries
find_package(catkin REQUIRED 
    COMPONENTS
	    cv_bridge
        car_tec_msgs
        roscpp
        rospy
        std_msgs
        image_transport
)

if(NOT ANDROID)
  find_package(PythonLibs)
  if(PYTHONLIBS_VERSION_STRING VERSION_LESS 3)
    find_package(Boost REQUIRED python)
  else()
    find_package(Boost REQUIRED python3)
  endif()
else()
find_package(Boost REQUIRED)
endif()
find_package(OpenCV 3 REQUIRED)


message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


##d, nylok-coated (3)
#find_packaxe(Eigen3 REQUIRED)
#find_package(Boost REQUIRED)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
#    ${EIGEN3_INCLUDE_DIR}
  LIBRARIES ${PROJECT_NAME}_core
  CATKIN_DEPENDS roscpp rospy std_msgs car_tec_msgs image_transport
  DEPENDS Boost OpenCV
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS}
#  ${EIGEN3_INCLUDE_DIR}
#  ${Boost_INCLUDE_DIRS}
)

## Declare a cpp library
#add_library(${PROJECT_NAME}_core
#   src/Algorithm.cpp
#)

add_library(${PROJECT_NAME}_core
        src/HoughDetector.cpp
)

## Declare cpp executables
add_executable(${PROJECT_NAME}
        src/${PROJECT_NAME}_node.cpp
        src/LineDetector.cpp
)

## Add dependencies to exported targets, like ROS msgs or srvs
#add_dependencies(${PROJECT_NAME}_core
#  ${catkin_EXPORTED_TARGETS}
#)


add_dependencies(${PROJECT_NAME}_core
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)


## Specify libraries to link executable targets against
#target_link_libraries(${PROJECT_NAME}_core
#  ${catkin_LIBRARIES}
#)
target_link_libraries(${PROJECT_NAME}_core
	    ${OpenCV_LIBS}
        ${catkin_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
        ${PROJECT_NAME}_core
	    ${OpenCV_LIBS}
        ${catkin_LIBRARIES}
)


#############
## Install ##
#############

# Mark executables and/or libraries for installation
install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Mark cpp header files for installation
install(
  DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.hpp"
)

# Mark other files for installation
#install(
#  DIRECTORY doc
#  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
#)

