#!/usr/bin/env python

import rospy
from efficiency_test.msg import SuperMessage

def talker():
    pub = rospy.Publisher('internship_exe1', SuperMessage)
    rospy.init_node('internship_exe1', anonymous=True)
    rate = rospy.Rate(10) 
    msg = SuperMessage()
    count = 0

    while not rospy.is_shutdown():
        count = count + 1
        msg.publisher = ("Python %d" %count)
        rospy.loginfo(msg)
        pub.publish(msg) 
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
