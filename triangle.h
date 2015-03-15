#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "object.h"
#include "vector.h"
#include "color.h"

class Triangle : public Object {

public:
	Color color;
	Vector normal;
	Vector v0, v1, v2;

	Triangle() {}
	~Triangle() {}
	Triangle(Vector _n, Color _c, Vector _v0, Vector _v1, Vector _v2)
	: normal(_n), color(_c), v0(_v0), v1(_v1), v2(_v2) {}

	virtual Color getColor() { return color; }
	virtual Vector normalAt(Vector point) { return normal; }
	virtual double findIntersection(Ray ray) {

		//edge 0 
		Vector v0v1 = v1 - v0;
		Vector v0v2 = v2 - v0;
		Vector N = v0v1.cross(v0v2);
		double nDotRay = N.dot(ray.direction);
		if (nDotRay < 0) { return -1; } // right of the triangle

		double d = N.dot(v0);
		double t = -(N.dot(ray.origin) + d) / nDotRay;

		Vector p = ray.origin + (ray.direction * t);

		//edge 0
		Vector v0p = p - v0;
		double v = N.dot(v0v1.cross(v0p));
		if (v < 0) { return -1; } // outside

		//edge 1
		Vector v1p = p - v1;
		Vector v1v2 = v2 - v1;
		double w = N.dot(v1v2.cross(v1p));
		if (w < 0) { return -1; } // outside

		//edge 2
		Vector v2p = p - v2;
		Vector v2v0 = v0 - v2;
		double u = N.dot(v2v0.cross(v2p));
		if (u < 0) { return false; } // outside

		return t;
	}
};

#endif