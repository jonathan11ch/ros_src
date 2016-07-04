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
	/*setup functions*/
	void setX(double _x){x=_x;}
	void setY(double _y){y=_y;}
	void setTheta(double _theta){theta=_theta;}
	/*return functions*/	
	double getX(){return x;}
	double getY(){return y;}
	double getTheta(){return theta;}
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
	geometry_msgs::Twist velMsg;
	velMsg.linear.x=v;
	velMsg.angular.z=w;
	velPub.publish(velMsg);
}
	/*input function Twist compact message*/
void turtlebot::setVelCmd(geometry_msgs::Twist velMsg){
	velPub.publish(velMsg);
}
/*set buffer size for velocity topic*/
void turtlebot::setVelQueue(int q){
	queue_size=q;
}
/*callback function for Odometry updates the odometry state*/
void turtlebot::odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
	_pos.setX(msg->pose.pose.position.x);  //x position
	_pos.setY(msg->pose.pose.position.y);  //y position
	_pos.setTheta(tf::getYaw(msg->pose.pose.orientation)); //orientation angle YAW
}


}