#include <math.h>
#include <stdio.h>
#include <string>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_datatypes.h" 
#include "rosGeometry.h"
/*Robot model main Objects*/
/*Input values (w,v) angular velocity and linear velocity */
/*Output values current position*/
/*Output velocities*/
namespace turtlebotRos{
/*Coordinates object class*/
class orientation
{
rosGeometry::coordinate _pos;
double theta;	
public:
	orientation();
	~orientation();
	/*setup functions*/
	void setTheta(double _theta){theta=_theta;}
	/*return functions*/	
	rosGeometry::coordinate getPos(){return _pos;}
	double getTheta(){return theta;}
};
/*Turtlebot object class*/
class turtlebot
{
std::string velTopic("cmd_vel_mux/input/navi");	
ros::NodeHandle nh;
ros::Publisher velPub;
ros::Subscriber OdomSub;
geometry_msgs::Twist velMsg;
nav_msgs::Odometry pos_state;
turtlebotRos::orientation _pos;
int queue_size=10;
bool odomData=false

public:
	turtlebot(){
		velPub=nh.advertise<geometry_msgs::Twist>(velTopic,queue_size);
		OdomSub=nh.subscribe("odom",queue_size,odomCallback);
	}
	~ turtlebot();
	void setVelCmd(double v,double w);
	void setVelCmd(geometry_msgs::Twist velMsg);
	void setVelQueue(int q);
	void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
	bool odomAvialable();
	void setOdom(bool b);
	void Go();
	turtlebotRos::orientation getPos(){return _pos;}
};

/**************************FUNCTION DEFINITIONS***************************/
bool turtlebot::odomAvialable(){
	return odomData;
}
void turtlebot::setOdom(bool b){
	odomData=b;
}
/*publish the desired velocity on twist topic*/
	/*input function v, w*/
void turtlebot::setVelCmd(double v,double w){
	velMsg;
	velMsg.linear.x=v;
	velMsg.angular.z=w;
}
	/*input function Twist compact message*/
void turtlebot::setVelCmd(geometry_msgs::Twist vel){
	velMsg=vel;
}

void turtlebot::Go(){
	velPub.publish(velMsg);
}
/*set buffer size for velocity topic*/
void turtlebot::setVelQueue(int q){
	queue_size=q;
}
/*callback function for Odometry updates the odometry state*/
void turtlebot::odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
	odomData=true;
	_pos.getPos().setValues(msg->pose.pose.position.x,msg->pose.pose.position.y);  //x position  //y position
	_pos.setTheta(tf::getYaw(msg->pose.pose.orientation)); //orientation angle YAW
}


}