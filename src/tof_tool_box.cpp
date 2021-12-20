#include "tof_tool/tof_tool_box.h"


using namespace std;

void TofToolBox::sayHello() {
    ROS_INFO("Hello!");
}

/**
 * function for printing space sizes
 * 0  little space
 * 1  big space
 * @param 'spaceSize' size of the space required when printing
 */
void TofToolBox::printSeparator(int spaceSize) {
	if (spaceSize == 0) {
		printf("--------------------------------------------\n");
	}
	else {
		printf("\n");
		printf("--------------------------------------------\n");
		printf("\n");
	}
}

/**
 * Does the wheelchair_dump package exist in the workspace?
 * If it's missing, close down the node safely
 * @param 'pkg_name' name of package to find within workspace
 * @return 'getPkgPath' full path of package 'pkg_name'
 */
std::string TofToolBox::doesPkgExist(std::string pkg_name) {
    std::string getPkgPath;
	if (ros::package::getPath(pkg_name) == "") {
		cout << "FATAL:  Couldn't find package " << pkg_name << "\n";
		cout << "FATAL:  Closing node. \n";
        if (DEBUG_doesPkgExist) {
            cout << getPkgPath << endl;
        }
		ros::shutdown();
		exit(0);
	}
    else {
        getPkgPath = ros::package::getPath(pkg_name);
        if (DEBUG_doesPkgExist) {
            cout << "ROS package is: " << getPkgPath << endl;
        }
    }
    return getPkgPath;
}

/**
 * Function to check if file exists in the 'fileName' path, if it doesn't exist create a new one
 *
 * @param the path and file name to be created called 'fileName'
 * @return return '1' if file already exists, return '0' if file was missing and has been created
 */
int TofToolBox::createFile(std::string fileName) { //if this doesn't get called, no file is created
    if (DEBUG_createFile) {
        printf("DEBUG: createFile()\n");
    }
	std::ifstream fileExists(fileName);

	if (fileExists.good() == 1) {
		//File exists
        if (DEBUG_createFile) {
            printf("Weighting file exists\n");
        }
		//cout << fileName;
		return 1;
	}
	else {
		//File doesn't exist
        if (DEBUG_createFile) {
            printf("Weighting file doesn't exist\n");
            printf("creating new file\n");
        }
		ofstream NEW_FILE (fileName);
		NEW_FILE.close();
		//cout << fileName;
		return 0;
	}
}

/**
 * calculate number of lines present in fileName
 * while we haven't reached the end of the file
 * iterate returncounter on each line, return the value
 * @param the path and file name to be calculated called 'fileName'
 * @return 'returnCounter' return the number of lines in the file
 */
int TofToolBox::calculateLines(std::string fileName) {
	if (DEBUG_calculateLines) {
		cout << "DEBUG: calculateLines()\n";
	}
	ifstream FILE_COUNTER(fileName);
	std::string getlines;
	int returnCounter = 0;
	while (getline (FILE_COUNTER, getlines)) {
        returnCounter++;
        // Output the text from the file
        //cout << getlines;
        //cout << "\n";
	}
	FILE_COUNTER.close();
    if (DEBUG_calculateLines) {
        cout << returnCounter << endl;
    }
	return returnCounter;
}

/**
 * print out status of NaN detection for vectors and quaternions
 * inside a tf::Transform
 * @param option 0 is transform.getOrigin, 1 is transform.getRotation
 * @param myTransform from tf::transform vector
 * @return 'detectedNaN' return 1 if NaN detected, 0 if no NaN
 */
void TofToolBox::validateTransformPrint(int option, tf::Transform myTransform) {
	if (option == 0) {
		//get origin
		cout << myTransform.getOrigin().x() << ", " <<
					myTransform.getOrigin().y() << ", " <<
					myTransform.getOrigin().z() << endl;
	}
	else if (option == 1) {
		//get rotation
		cout << myTransform.getOrigin().x() << ", " <<
					myTransform.getOrigin().y() << ", " <<
					myTransform.getOrigin().y() << ", " <<
					myTransform.getOrigin().z() << endl;
	}
}

/**
 * search for NaN in vector and quaternions
 * inside a tf::Transform
 * @param myTransform from tf::transform vector
 * @return 'detectedNaN' return 1 if NaN detected, 0 if no NaN
 */
int TofToolBox::validateTransform(tf::Transform myTransform) {
	int detectedNaN = 0;
    if ((isnan(myTransform.getOrigin().x())) ||
        (isnan(myTransform.getOrigin().y())) ||
        (isnan(myTransform.getOrigin().z()))) {
        if (DEBUG_nan_detector) {
            cout << "NaN detected in local DET transform, using getOrigin" << endl;
			validateTransformPrint(0, myTransform);
        }
        detectedNaN = 1;
    }
	if ((isnan(myTransform.getRotation().x())) &&
		(isnan(myTransform.getRotation().y())) &&
		(isnan(myTransform.getRotation().z())) &&
		(isnan(myTransform.getRotation().w()))) {
		if (DEBUG_nan_detector) {
            cout << "NaN detected in local DET transform, using getRotation" << endl;
			validateTransformPrint(1, myTransform);
        }
        detectedNaN = 1;
	}
    if ((!rviz::validateFloats(myTransform.getOrigin().x())) ||
        (!rviz::validateFloats(myTransform.getOrigin().y())) ||
        (!rviz::validateFloats(myTransform.getOrigin().z())) ) {
        if (DEBUG_nan_detector) {
            cout << "NaN detected whilst validating myTransform.getOrigin in RVIZ" << endl;
			validateTransformPrint(0, myTransform);
        }
        detectedNaN = 1;
    }
	if ((!rviz::validateFloats(myTransform.getRotation().x())) ||
        (!rviz::validateFloats(myTransform.getRotation().y())) ||
		(!rviz::validateFloats(myTransform.getRotation().z())) ||
        (!rviz::validateFloats(myTransform.getRotation().w())) ) {
        if (DEBUG_nan_detector) {
            cout << "NaN detected whilst validating myTransform.getRotation in RVIZ" << endl;
			validateTransformPrint(1, myTransform);
        }
        detectedNaN = 1;
    }
	return detectedNaN;
}