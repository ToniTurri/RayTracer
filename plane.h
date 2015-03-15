#ifndef _PLANE_H
#define _PLANE_H

#include "vector.h"
#include "color.h"
#include "object.h"
#include <cmath>

class Plane : public Object {
	Vector normal;
	double distance;
	Color color;

public:

	Plane();
	~Plane() {}
	Plane(Vector _n, double _d, Color _c) :
		normal(_n), distance(_d), color(_c) {}

	virtual Color getColor() { return color; }
	virtual Vector normalAt(Vector point) { return normal; }
	virtual double findIntersection(Ray ray) {
		Vector rayDirection = ray.direction;
		double a = rayDirection.dot(normal);
		if (a == 0) return -1; // ray is parallel to plane
		else {
			double b = normal.dot(ray.origin + ((normal * distance).negative()));
			return -1 * b / a;
		}
	}
};

Plane::Plane() {
	normal = Vector(1, 0, 0);
	distance = 0;
	color = Color(1, 1, 1, 0);
}

#endif