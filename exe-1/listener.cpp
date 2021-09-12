#include <ros/ros.h>
#include <efficiency_test/SuperMessage.h>

void chatterCallback(const efficiency_test::SuperMessage::ConstPtr& msg)
{
  ROS_INFO("Hello From: [%s] publisher", msg->publisher.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("internship_exe1", 1000, chatterCallback);

  ros::spin();

  return 0;
}
