# car-tec
Development of an autonomous vehicle prototype in ROS as the capstone project of the mechatronics engineering degree

## Overview
This repository is the ros-package needed for the capstone project for the degree in Mechatronics Engineering in the Tec de Monterrey - Campus Guadalajara.

This project is going to be the platform for several projects about autonomous systems on-campus and will lead to further development in the classes of Robotics and Capstone Project in Mechatronics Engineering.

This packagae has been developed and tested under:

**- ROS Kinetic**
**- Ubuntu Xenial 16.04**

Requirements:
**- Python: 3.5.2**
**- OpenCV: 3.4.0**

**Author(s): Jose Vazquez (Main Developer), Farid Izar (xbox control node), Andres Gonzalez (xbox control node)**

**Mainteiner: TBA**

## MCU Software Repository

The development for the microcontroller software layer of this project is in the repository by [Farid Izar](github.com/faridiz/cartec-mcu)(http://wiki.ros.org)

**Author(s): Farid Izar (Main Developer), Andres Gonzalez (Main Developer/Scheduling), Jose Vazquez (MCU ROS Implementation)**


## Installation
### Dependencies

- [Robot Operating System (ROS)](http://wiki.ros.org) (middleware for robotics)

#### Building

To build from source, clone the latest version from this repository into your catkin workspace and compile the package using

	cd catkin_workspace/src
	git clone https://github.com/joseluisvaz/car-tec-cpp
	git clone https://github.com/ros-drivers/video_stream_opencv
	cd ../
	catkin build

If you have problems with the catkin build command make sure you have ```catkin_tools``` installed by runnning in the console

```
sudo apt-get install python-catkin-tools
```

  
## Usage

After building the packages, just source the workspace like this:
```
source catkin_workspace/devel/setup.sh
```
The software runs using a ZED camera, a webcam or a videofile.

### Video_file
Create a folder named data inside the ```line_detector``` data node and afterwards poblate it with a ```.mp4``` video to be used as the input, then just run: 
``` roslaunch master_node simulation.launch ```

### Webcam
For a webcam just use the following command
``` roslaunch master_node master_video.launch ```

## Xbox controller
To substitute the perception-action pipeline with an xbox controller for its interface with the microcontroller board, just use:
``` roslaunch master_node xbox.launch ```

\\ TODO: Make script to install the dependencies for the python code and add virtual environment instructions if needed.


## NODES

//TODO LIST AND DESCRIBE THE NODES CONTAINED IN THIS PACKAGE
### ros_package_tree
//TODO TREE OF THE PACKAGE
 
### NODE_A_NAME
#### Subscribed Topics
#### Published Topics

### NODE_B_NAME


# NOTES
from zed_ros_wrapper repository, checkout v2.2.x branch for integration with CUDA 9.0, ig you are using another CUDA version please make sure to use the correct up-to-date zed_ros_wrapper branch(version).
