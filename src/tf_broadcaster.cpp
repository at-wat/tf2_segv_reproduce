#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "broadcaster");

  tf::TransformBroadcaster tfb;
  ros::Duration(1.0).sleep();

  ros::Rate rate(10);

  int cnt = 0;
  while (ros::ok())
  {
    ++cnt;
    tfb.sendTransform(
        tf::StampedTransform(
            tf::Transform(tf::Quaternion(0, 0, 0, 1)),
            ros::Time::now() + ros::Duration(0.1), "laser_link_base", "laser_link"));
    tfb.sendTransform(
        tf::StampedTransform(
            tf::Transform(tf::Quaternion(0, 0, 0, 1)),
            ros::Time::now() + ros::Duration(0.1), "map", "odom"));
    if (cnt > 10)
    {
      tfb.sendTransform(
          tf::StampedTransform(
              tf::Transform(tf::Quaternion(0, 0, 0, 1)),
              ros::Time::now() + ros::Duration(0.1), "base_link", "laser_link_base"));
    }
    if (cnt > 20)
    {
      tfb.sendTransform(
          tf::StampedTransform(
              tf::Transform(tf::Quaternion(0, 0, 0, 1)),
              ros::Time::now() + ros::Duration(0.1), "odom", "base_link"));
    }
    if (cnt > 30)
      break;

    ros::spinOnce();
    rate.sleep();
  }

  ros::spin();
}
