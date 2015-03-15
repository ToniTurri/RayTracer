#ifndef _LIGHT_H
#define _LIGHT_H

class Light : public Source {
public:
	Vector position;
	Color color;

	Light();
	~Light() {}
	Light(Vector _pos, Color _color) : position(_pos), color(_color) {}

	virtual Vector lightPosition() { return position; }
	virtual Color lightColor() { return color; }
};

Light::Light() {
	position = Vector();
	color = Color();
}
#endif