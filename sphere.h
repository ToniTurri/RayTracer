#ifndef _SPHERE_H
#define _SPHERE_H

#include "vector.h"
#include "object.h"
#include "color.h"

class Sphere : public Object {

public:
	double radius;
	Vector center;
	Color color;

	Sphere();
	~Sphere() {}
	Sphere(Vector _c, double _r, Color _color) :
		center(_c), radius(_r), color(_color) {}

	virtual Color getColor() { return color; }
	virtual Vector normalAt(Vector point) {
		// normal points away from center of sphere
		Vector normal = (point + center.negative()).normalize();
		return normal;
	}

	virtual double findIntersection(Ray ray) {
		double a = ray.direction.dot(ray.direction);
		double b = 2 * ray.direction.dot(ray.origin - center);
		double c = ray.origin.dot(ray.origin - center) - (radius * radius);

		double discriminant = b * b - 4 * a * c;
		if (discriminant < 0) { return -1; }
		double discSqrt = sqrt(discriminant);
		double q = 0;

		if (b < 0)  { q = (-b - discSqrt) / 2.0; }
		else 		{ q = (-b + discSqrt) / 2.0; }

		double t0 = q / a;
		double t1 = c / q;

		if (t0 > t1) {
			double temp = t0;
			t0 = t1;
			t1 = temp;
		}

		if (t1 < 0) { return -1; } // negative direction - misses the sphere
		if (t0 < 0) { return t1; } // point at t1
		else		{ return t0; } // point at t0
	}
};

Sphere::Sphere() {
	center = Vector();
	radius = 1.0;
	color  = Color(1, 1, 1, 0);
}

#endif