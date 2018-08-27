FROM ros:kinetic

COPY package.xml /catkin_ws/src/tf2_segv_reproduce/package.xml
WORKDIR /catkin_ws
RUN . /opt/ros/${ROS_DISTRO}/setup.sh && cd src/ && catkin_init_workspace

SHELL ["/bin/bash", "-c"]
RUN apt-get update -qq \
  && rosdep install -y --from-paths src --ignore-src \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

COPY . /catkin_ws/src/tf2_segv_reproduce
RUN . /opt/ros/${ROS_DISTRO}/setup.sh && catkin_make

COPY test.sh /test.sh

CMD ["/test.sh"]
