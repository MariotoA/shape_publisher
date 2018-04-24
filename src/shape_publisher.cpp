#include <ros/ros.h>
#include <geometry_msgs/Polygon.h>

int main(int argc, char **argv)
{
	ros::init(argc,argv,"shape_publisher");
	ros::NodeHandle nh;
	ros::Rate loop_rate(20);
	ros::Publisher pub = nh.advertise<geometry_msgs::Polygon>("/chassis_polygon",1000);
	geometry_msgs::Polygon msg;
	geometry_msgs::Point32 p1,p2,p3,p4;
	p4.x = p4.y = p3.y = p1.x = -0.225;
	p2.x = p2.y = p3.x = p1.y = 0.225;
	msg.points.push_back(p1);
	msg.points.push_back(p2);
	msg.points.push_back(p3);
	msg.points.push_back(p4);
	ROS_INFO("POINTS: %d", msg.points.size());
	while (ros::ok())
	{
		pub.publish(msg);
		loop_rate.sleep();
		ros::spinOnce();
		ROS_INFO("SHAPE PUBLISHED: P1[%f,%f]  P2[%f,%f]  P3[%f,%f]  P4[%f,%f]",
		p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y
		);
	}
	return 0;
}
