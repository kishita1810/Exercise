#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;

int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("[%s]", msg->data.c_str());

  std::string image_path = samples::findFile("%s", msg->data.c_str());

  src = imread(image_path, IMREAD_COLOR ); // Load an image
  if( src.empty() )
  {
    std::cout << "Could not open or find the image!\n" << std::endl;
    std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
    return -1;
  }
  dst.create( src.size(), src.type() );

  cvtColor( src, src_gray, COLOR_BGR2GRAY );

  namedWindow( window_name, WINDOW_AUTOSIZE );

  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  CannyThreshold(0, 0);

}

static void CannyThreshold(int, void*)
{
    blur( src_gray, detected_edges, Size(3,3) );
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    dst = Scalar::all(0);
    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
    waitKey(3000);
    cv::destroyAllWindows();
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "canny_detection"); 

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("internship_exe2", 1000, chatterCallback);

  ros::spin();

  return 0;
}
