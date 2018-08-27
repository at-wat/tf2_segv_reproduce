#!/bin/bash

set -e

. /opt/ros/${ROS_DISTRO}/setup.bash
. /catkin_ws/devel/setup.bash

roscore &

sleep 2

echo tf_broadcaster_segv start
(rosrun tf2_segv_reproduce tf_broadcaster_segv && echo tf_broadcaster_segv: O || echo tf_broadcaster_segv: X ) &

echo tf_listener_segv start
rosrun tf2_segv_reproduce tf_listener_segv && echo tf_broadcaster_segv: O || echo tf_broadcaster_segv: X
