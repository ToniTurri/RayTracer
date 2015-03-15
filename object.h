#ifndef _OBJECT_H
#define _OBJECT_H

#include "vector.h"
#include "color.h"
#include "ray.h"

class Object {
public:
	Object() {}
	~Object() {}

	virtual double findIntersection(Ray ray) { return 0; }
	virtual Vector normalAt(Vector intersectionPos) { return Vector(); }
	virtual Color getColor() { return Color(); }

};


#endif