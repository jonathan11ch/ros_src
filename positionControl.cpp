#include <math.h>
#include <stdio.h>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_datatypes.h"
#include "PosControlLib.h"
/*constants definition*/
const double Gamma = 0.5; //linear vel max
const double k = 0.2;
/**/
bool ODOM_DATA= false;
/*Turtlebot class*/
/*Current Point*/
double Xc=0;
double Yc=0;
double XITAc=0;
/*Desired point*/
double Xd=10;
double Yd=10;
/* position error */
double _X;
double _Y;
/*Polar coordinates*/
double e;
double alpha;
double theta;
/*commands*/
//double w=0;
//double v=0;
/*error calculation*/
void Error(){
	_X=Xd-Xc;
	_Y=Yd-Yc;	
}
/*Coordinates transformation*/
void coorTransf(){
	e=sqrt((_X*_X)+(_Y*_Y)); 
	theta=atan2(_Y,_X);
	alpha=theta-XITAc;
}
/*Controller function*/
//void posController(){
//	v=Gamma*tanh(e)*cos(alpha);
//	w=k*alpha+Gamma*(tanh(e)/e)*sin(alpha)*cos(alpha);
//}

/*time of Callback: 20 ms*/
void odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg){
	/*update postion*/
	ODOM_DATA=true;
	Xc=odom_msg->pose.pose.position.x;
	Yc=odom_msg->pose.pose.position.y;
	XITAc=tf::getYaw(odom_msg->pose.pose.orientation);	
}

int main(int argc, char **argv){
	
	ros::init(argc,argv,"pos_controler");
	ros::NodeHandle nh;
	/*Odometry subscription*/
	ros::Subscriber odomSub=nh.subscribe("odom",100,odomCallback);
	/*Velocity publisher*/
	ros::Publisher velPub=nh.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi",10);
	/*Loop rate*/
	ros::Rate loop_rate(150); //150Hz	
	/*COntroller object*/
	turtleControl::positionController pc(0.5,0.2);
	turtleControl::polarCoordinates p();
	/*velocity msgs type */
	geometry_msgs::Twist velMsg;
	
	while(ros::ok()){
		
		/*Control loop*/
		if(ODOM_DATA){
			ODOM_DATA=false;
		/*calculate error*/
			Error();
		/*polar transformation*/	
			coorTransf();
		/*Controller calculation*/
			velMsg=pc.posController(e,alpha,theta);				
		}		
		//velMsg.linear.x=v;
		//velMsg.angular.z=w;
		velPub.publish(velMsg);
		ros::spinOnce();
		loop_rate.sleep();
	}
	
return 0;
}
