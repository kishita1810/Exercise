#include "opencv2/opencv.hpp"
#include "iostream"
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv) {

    ros::init(argc, argv, "cv-camera");

    ros::NodeHandle n;

    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("internship_exe2", 1000);

    ros::Rate loop_rate(10);

    // open the first webcam plugged in the computer
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    // create a window to display the images from the webcam
    cv::namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

    // this will contain the image from the webcam
    cv::Mat frame;
        
    // capture the next frame from the webcam
    camera >> frame;

    int count = 0;
    
    // display the frame until you press a key
    while (ros::ok()) {

        std_msgs::String msg;
        
        std::stringstream ss;
        
        ss << "Image from Webcam " << count;
        
        msg.data = ss.str();

        // show the image on the window
        cv::imshow("Webcam", frame);
        // wait (10ms) for a key to be pressed
        if (cv::waitKey(10) >= 0)
            break;

        cv::imwrite(ss.str(), frame);    

        ROS_INFO("%s", msg.data.c_str());

        chatter_pub.publish(msg);
        sleep(5);

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }
    return 0;
}
