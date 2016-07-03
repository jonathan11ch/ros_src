#include <math.h>
#include <stdio.h>
#include <string>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_datatypes.h" 

/*Robot model main Objects*/
/*Input values (w,v) angular velocity and linear velocity */
/*Output values current position*/
/*Output velocities*/
namespace turtlebotRos{
/*Coordinates object class*/
class rectCoord
{
double	x;
double	y;
double theta;	
public:
	rectCoord();
	~rectCoord();

};
/*Turtlebot object class*/
class turtlebot
{
std::string velTopic("cmd_vel_mux/input/navi");	
ros::NodeHandle nh;
ros::Publisher velPub;
ros::Subscriber OdomSub;
nav_msgs::Odometry pos_state;
turtlebotRos::rectCoord _pos;
int queue_size=10;
public:
	turtlebot(){
		velPub=nh.advertise<geometry_msgs::Twist>(velTopic,queue_size);
		OdomSub=nh.subscribe("odom",queue_size,odomCallback);
	}
	~ turtlebot();
	void setVelCmd(double v,double w);
	void setVelQueue(int q);
	void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
};

/*FUNCTION DEFINITIONS*/
/*publish the desired velocity on twist topic*/
void turtlebot::setVelCmd(double v,double w){


}
/*set buffer size for velocity topic*/
void turtlebot::setVelQueue(int q){
	queue_size=q;
}
/*callback function for Odometry updates the odometry state*/
void turtlebot::odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
	pos_state.pos=msg->pose;  //pose.position.x - pose.orientation.x
	pos_state.twist=msg->twist; //twist.linear.x - twist.angular.x

}


}