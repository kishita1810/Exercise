#!/usr/bin/env python
import rospy
from efficiency_test.msg import SuperMessage

def callback(data):
    rospy.loginfo("Hello From [%s] publisher" % data.publisher)
    
def listener():
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("internship_exe1", SuperMessage, callback)

    rospy.spin()

if __name__ == '__main__':
    listener()
