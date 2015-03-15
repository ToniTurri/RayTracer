#ifndef _SOURCE_H
#define _SOURCE_H

#include "vector.h"
#include "color.h"

class Source {
public:

	Source() {}
	~Source() {}

	virtual Vector lightPosition() { return Vector(0, 0, 0); }
	virtual Color lightColor() { return Color(1, 1, 1, 0); }

};

#endif