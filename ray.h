#ifndef _RAY_H
#define _RAY_H

class Ray {
public:
	Vector origin, direction;

	Ray();
	~Ray() {}
	Ray(Vector _o, Vector _d) :
		origin(_o), direction(_d) {}
};

Ray::Ray() {
	origin = Vector();
	direction = Vector(1, 0, 0);
}

#endif