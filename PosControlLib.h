#include <math.h>
#include <stdio.h>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_datatypes.h"
#include "rosGeometry.h"

namespace turtleControl{
/**/
class feedbackError
{
double _x;
double _y;
public:
	 feedbackError();
	~ feedbackError();
	void calculateError(rosGeometry::coordinate Xd, rosGeometry::coordinate Xc){
		_x=Xd.getPointX()-Xc.getPointX();
		_y=Xd.getPointY()-Xc.getPointY();
	}

};

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
/**/
class polarCoordinates{
		

	public:	
double e; 
double alpha;
double theta;
	polarCoordinates();
	
	void setCoordinates(double _e,double _alpha, double _theta){
		e=_e;
		alpha=_alpha;
		theta=_theta;
	}
	void coorTransf(double _X,double _Y, double XITAc);
	void coorTransf(feedbackError fe,double XITAc);				
};
/* input data ~X calculated as the difference  */
void polarCoordinates::coorTransf(double _X, double _Y,double XITAc ){
	e=sqrt((_X*_X)+(_Y*_Y)); 
	theta=atan2(_Y,_X);
	alpha=theta - XITAc;
}
void polarCoordinates::coorTransf(feedbackError fe,double XITAc){
	e=sqrt((fe._x*fe._x)+(fe._y*fe._y)); 
	theta=atan2(fe._y,fe_x);
	alpha=theta - XITAc;	

}





}





