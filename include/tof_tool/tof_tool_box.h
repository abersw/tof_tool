#ifndef TOF_TOOL_BOX_H
#define TOF_TOOL_BOX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ros/ros.h> //main ROS library
#include <ros/package.h> //find ROS packages, needs roslib dependency
#include <std_srvs/Empty.h>
#include "wheelchair_msgs/mobilenet.h" //depth sensing
#include "wheelchair_msgs/foundObjects.h"
#include "wheelchair_msgs/objectLocations.h"

#include "sensor_msgs/Image.h" //depth sensing
#include "sensor_msgs/PointCloud2.h" //depth sensing

//experimental
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/TransformStamped.h"

#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"
#include "tf/transform_datatypes.h" //depth sensing

#include <message_filters/subscriber.h> //depth sensing
#include <message_filters/time_synchronizer.h> //depth sensing
#include <message_filters/synchronizer.h> //depth sensing
#include <message_filters/sync_policies/approximate_time.h> //depth sensing

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

    private:
        //debug variables
        const int DEBUG_doesPkgExist = 0;
        const int DEBUG_createFile = 0;
        const int DEBUG_calculateLines = 0;
};

#endif
