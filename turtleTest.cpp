#include <stdio.h>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "turtlebotLib.h"
#include "PosControlLib.h"
#include "rosGeometry.h"

int main(int argc,char ** argv){

	ros::init(argc,argv,"nodoTurtle");
	turtlebotRos::turtlebot iRobot;
	turtleControl::positionController pc(0,5,0,2);
	rosGeometry::coordinate Xd(1,5);
	turtleControl::feedbackError fe;
	turtleControl::polarCoordinates _pol;
	ros::Rate loop(150);
	
	while(ros::ok()){

		if(iRobot.odomAvialable()){
			iRobot.setOdom(false);
			/*calculate error*/
			fe.calculateError(Xd,iRobot.getPos().getPos());
			/*polar transformation*/
			_pol.coorTransf(fe,iRobot.getPos().getTheta());
			/*controller calculation*/
			iRobot.setVelCmd(pc.posController(_pol.e,_pol.alpha,_pol.theta));	
		}
		iRobot.Go();	
		loop.sleep();
	}
	return 0;
}