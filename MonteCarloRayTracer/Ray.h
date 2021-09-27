
#ifndef RAY_TNCG15_H //So we wont declare things more than once
#define RAY_TNCG15_H

#include "typedefs.h"


//Based on www.youtube.com/watch?v=AHe8PUr7Jqw

class Ray {
public:
	//Ray() : start{ vec3{0.0} }, end{ vec3{0.0} }, direction{ vec3{0.0} }{};
	Ray(const dvec3&, const dvec3&);

	void setColor(const ColorDbl &newColor);
	void setEnd(const double hit);

	ColorDbl getColor();
	dvec3 getStart();
	dvec3 getDirection();
	dvec3 getEnd();

	void localLight(Scene& scene, size_t obj_ind);

private:
	ColorDbl color{ BLACK };
	dvec3 start;
	dvec3 direction;
	dvec3 end;

};

#endif
