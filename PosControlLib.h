#include <math.h>
#include <stdio.h>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_datatypes.h"

class positionController{
/*controller parameters*/
double Gamma;
double k;
/*Output variables*/
double v;
double w;
geometry_msgs::Twist VelCommand;

	public:
	positionController(double G, double _k){
		Gamma=G;
		k=_k;
	}
		
	geometry_msgs::Twist posController(double e,double alpha,double theta){
		VelCommand.linear.x=Gamma*tanh(e)*cos(alpha);
		VelCommand.angular.z=k*alpha+Gamma*(tanh(e)/e)*sin(alpha)*cos(alpha);
		return VelCommand;
	}		
};

class polarCoordinates{
double e; 
double alpha;
double theta;		
	public:	
	polarCoordinates();
	
	void setCoordinates(double _e,double _alpha, double _theta){
		e=_e;
		alpha=_alpha;
		theta=_theta;
	}				
};





