#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "iostream"
#include "fstream"

#define RAD2DEG(x) ((x)*180./M_PI)

using namespace std;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int count = scan->scan_time / scan->time_increment;
    ROS_INFO("I heard a laser scan %s[%d]:", scan->header.frame_id.c_str(), count);
    ROS_INFO("angle_range, %f, %f", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
  
    for(int i = 0; i < count; i++) 
    {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
        ROS_INFO(": [%f, %f]", degree, scan->ranges[i]);

	int Frontfile, Backfile, Leftfile, Rightfile, FrontRightfile, FrontLeftfile;
	int z = 1;
	double F, B, L, R, FR, FL;
	
	if (degree > 178 && degree < 180)
	{
		F = scan->ranges[i];
		if (F >= 0 && F <= 6)
		{
		ofstream Frontfile;
		Frontfile.open ("Front.txt");
			Frontfile << F;
		  	Frontfile.close();
		}

	}

	if (degree > 0 && degree < 2)
	{
	B = scan->ranges[i];
 		if (B >= 0 && B <= 6)
		{
	ofstream Backfile;
	Backfile.open ("Back.txt");
			Backfile << B;
		  	Backfile.close();
		}

	}

	if (degree > -95  && degree < -93)
	{
	L = scan->ranges[i];
		if (L >= 0 && L <= 6)
		{
	ofstream Leftfile;
	Leftfile.open ("Left.txt");
			Leftfile << L;
		  	Leftfile.close();
		}

	}

	if (degree > 93  && degree < 95)
	{
	R = scan->ranges[i];
		if (R >= 0 && R <= 6)
		{
	ofstream Rightfile;
	Rightfile.open ("Right.txt");
			Rightfile << R;
		  	Rightfile.close();
		}

	}

	if (degree > 166  && degree < 168)
	{
	FR = scan->ranges[i];
		if (FR >= 0 && FR <= 6)
		{
	ofstream FrontRightfile;
	FrontRightfile.open ("FrontRight.txt");	
			FrontRightfile << FR;
			FrontRightfile.close ();

		}

	}

	if (degree > -168  && degree < -166)
	{
	FL = scan->ranges[i];
		if (FL >= 0 && FL <= 6)
		{
	ofstream FrontLeftfile;
	FrontLeftfile.open ("FrontLeft.txt");
			FrontLeftfile << FL;
			FrontLeftfile.close ();
		}

	}


    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "rplidar_node_client");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();
}
