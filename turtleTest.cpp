#include <stdio.h>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "turtlebotLib.h"
#include "PosControlLib.h"

int main(int argc,char ** argv){

	ros::init(argc,argv,"nodoTurtle");
	turtlebotRos::turtlebot iRobot;
	turtleControl::positionController pc(0,5,0,2);
	ros::Rate loop(150);
	while(ros::ok()){

		if(iRobot.odomAvialable()){
			iRobot.setOdom(false);
			/*calculate error*/
			/*polar transformation*/
			
			/*controller calculation*/
			iRobot.setVelCmd(pc.posController(e,alpha,theta));
			
		}	
		loop.sleep();
	}
	return 0;
}