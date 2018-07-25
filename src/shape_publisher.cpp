#include <ros/ros.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>

int main(int argc, char **argv)
{
	ros::init(argc,argv,"shape_publisher");
	ros::NodeHandle nh("~");
	ros::Rate loop_rate(.7), loop_rate_rviz(10);

	//Polygon
	ros::Publisher pub = nh.advertise<geometry_msgs::Polygon>("/chassis_polygon",1);
	geometry_msgs::Polygon msg;

	// Auxiliar var to store points temporarily.
	std::vector<double> points;

	// Obtaining parameters from yaml specified in rosparam tag
	nh.getParam("shape", points);
	ROS_INFO("MESSAGE CREATED");
	for (int i=0; i < points.size(); i+=2)
	{
		geometry_msgs::Point32 p;
		p.x = points[i];
		p.y = points[i+1];
		msg.points.push_back(p);
		ROS_INFO("P%d[%f,%f]",i,p.x,p.y);
	}

	// Polygon Stamped (to see it on Rviz)
	ros::Publisher pub_s = nh.advertise<geometry_msgs::PolygonStamped>("/chassis_polygon_stamped",1000);
	geometry_msgs::PolygonStamped msg_s;
	msg_s.polygon = msg;
	msg_s.header.stamp = ros::Time::now();
	msg_s.header.frame_id = "base_link";

	// Timer starts
	ros::Time begin = ros::Time::now();
	while ( begin.toSec() == 0 ) 
	{
		begin = ros::Time::now();
	}
	double ellapsed_time = 0;
	while (ros::ok())
	{
		if (ellapsed_time < 5)
		{
			pub.publish(msg);
			pub_s.publish(msg_s);
			loop_rate.sleep();
		} else 
		{
			pub_s.publish(msg_s);
			loop_rate_rviz.sleep();
		}
		ros::spinOnce();
		ros::Time current = ros::Time::now();
		ellapsed_time = (current-begin).toSec();
		ROS_INFO("SHAPE PUBLISHED.");
	}
	ROS_INFO("SHAPE PUBLISHER EXITING SAFELY.");
	return 0;
}
