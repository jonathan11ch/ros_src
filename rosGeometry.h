#include "ros/ros.h"
#include <math.h>
#include <stdio.h>

namespace rosGeometry{

class coordinate
{
double x;
double y;
public:
	coordinate(double _x, double _y){
		x=_x;
		y=_y;
	}
	coordinate(){
		x=0;
		y=0;
	}
	~coordinate();
	void setValues(double _x, double _y){
		x=_x;
		y=_y;
	}
	double getPointX(){return x;}
	double getPointY(){return y;}
};


}
