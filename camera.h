#ifndef _CAMERA_H
#define _CAMERA_H

#include "vector.h"

class Camera {
	Vector camPosition, camDirection, camRight, camDown;

public:
	Camera();
	~Camera() {}
	Camera(Vector _pos, Vector _dir, Vector _right, Vector _down) :
		camPosition(_pos), camDirection(_dir), camRight(_right), camDown(_down) {}

	Vector getDirection() { return camDirection; }
	Vector getPosition()  { return camPosition; }
	Vector getDown()      { return camDown; }
	Vector getRight()     { return camRight; }
};

Camera::Camera() {
	camPosition		= Vector::zero();
	camDirection	= Vector::Z();
	camDown			= Vector::zero();
	camRight		= Vector::zero();
}

#endif