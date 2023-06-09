#ifndef TOF_TOOL_BOX_H
#define TOF_TOOL_BOX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ros/ros.h> //main ROS library
#include <ros/package.h> //find ROS packages, needs roslib dependency

#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"

#include "rviz/validate_floats.h"


#include <fstream>
#include <iostream>
#include <sstream>


class TofToolBox {
    public:
        void sayHello();
        void printSeparator(int spaceSize);
        std::string doesPkgExist(std::string pkg_name);
        int createFile(std::string fileName);
        int calculateLines(std::string fileName);
        void validateTransformPrint(int option, tf::Transform myTransform);
        int validateTransform(tf::Transform myTransform);

    private:
        //debug variables
        const int DEBUG_doesPkgExist = 0;
        const int DEBUG_createFile = 0;
        const int DEBUG_calculateLines = 0;
        const int DEBUG_nan_detector = 1;
};

#endif
