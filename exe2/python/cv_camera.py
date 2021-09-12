#!/usr/bin/env python

import cv2
import time
import rospy
from std_msgs.msg import String

def talker():
    pub = rospy.Publisher('internship_exe2', String, queue_size=10)
    rospy.init_node('cv_camera', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    capture = cv2.VideoCapture(0)
    capture.set(3, 640)
    capture.set(4, 480)
    img_counter = 0
    frame_set = []
    start_time = time.time()

    while not rospy.is_shutdown():
        ret, frame = capture.read()
        # gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.imshow('frame', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        if time.time() - start_time >= 5: #<---- Check if 5 sec passed
            img_name = "opencv_frame_{}.png".format(img_counter)
            cv2.imwrite(img_name, frame)
            print("{} written!".format(img_counter))
            rospy.loginfo(img_name)
            pub.publish(img_name)
            rate.sleep()
            start_time = time.time()
        img_counter += 1

        

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
