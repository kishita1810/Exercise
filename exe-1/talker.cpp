#include <ros/ros.h>
#include <efficiency_test/SuperMessage.h>

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<efficiency_test::SuperMessage>("internship_exe1", 1000);

  ros::Rate loop_rate(125);
  int count = 0;

  while (ros::ok())
  {
    efficiency_test::SuperMessage msg;
    std::stringstream ss;
    ss << "C++" << count;
    msg.publisher = ss.str();
    
    ROS_INFO("%s", msg.publisher.c_str());
    pub.publish(msg);
    ros::spinOnce();
    
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
