#!/usr/bin/env python

import cv2
import numpy as np
import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "%s", data.data)
    filename = (data.data)
    print(filename)
    img = cv2.imread(filename)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    canny = cv2.Canny(img, 100, 200)
    cv2.imshow("canny image",canny)
    name = "canny" + data.data
    cv2.imwrite(name, canny)
    cv2.waitKey(3000)
    cv2.destroyAllWindows()

    
def listener():
    rospy.init_node('canny_detection', anonymous=True)

    rospy.Subscriber("internship_exe2", String, callback)

    rospy.spin()

if __name__ == '__main__':
    listener()
