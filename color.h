#ifndef _COLOR_H
#define _COLOR_H

class Color {
public: 
	unsigned char r, g, b, s;

	~Color() {}
	Color() : r(255), g(255), b(255) {}
	Color(unsigned char _r, unsigned char _g, unsigned char _b, double _s) 
		: r(_r), g(_g), b(_b), s(_s) {}

	Color& operator=(Color rhs);

	Color operator+(const Color& rhs); 
	Color& operator+=(const Color& rhs); 
	Color operator*(const Color& rhs);
	Color& operator*=(const Color& rhs);
	Color operator+(unsigned char rhs) const;
	Color operator*(unsigned char rhs) const; 
	Color operator*(double rhs) const;

	void swap(Color& rhs);
	void print_color_values();

	Color clip();

	double brightness() { return ( r + b + g ) / 3; }
	Color averageColor(Color color) { return Color((r + color.r) / 2, (g + color.g) / 2, (b + color.b) / 2, s); }
};

Color& Color::operator=(Color rhs) {
	swap(rhs);
	return *this;
}

Color Color::operator+(const Color& rhs) {
	Color result(*this);
	result += rhs;
	return result;
}

Color& Color::operator+=(const Color& rhs) {
	this->r += rhs.r;
	this->g += rhs.g;
	this->b += rhs.b;
	return *this;
}

Color Color::operator*(const Color& rhs) {
	Color result(*this);
	result *= rhs;
	return result;
}

Color& Color::operator*=(const Color& rhs){
	this->r *= rhs.r;
	this->g *= rhs.g;
	this->b *= rhs.b;
	return *this;
}

Color Color::operator+(unsigned char rhs) const {
	Color result(*this);
	result.r += rhs;
	result.g += rhs;
	result.b += rhs;
	return result;
}

Color Color::operator*(unsigned char rhs) const {
	Color result(*this);
	(result.r *= rhs);
	(result.g *= rhs);
	(result.b *= rhs);
	return result;
}

Color Color::operator*(double rhs) const {
	Color result(*this);
	result.r = (unsigned char)(result.r * rhs);
	result.g = (unsigned char)(result.g * rhs);
	result.b = (unsigned char)(result.b * rhs);
	return result;
}

void Color::swap(Color& rhs) {
	using std::swap;

	swap(this->r, rhs.r);
	swap(this->g, rhs.g);
	swap(this->b, rhs.b);
	swap(this->s, rhs.s);
}

Color Color::clip() {
	double light = r + g + b;
	double excesslight = light - 3;

	if (excesslight > 0) {
		r = r + excesslight * (r / light);
		g = g + excesslight * (g / light);
		b = b + excesslight * (b / light);
	}

	if (r > 1) { r = 1; }
	if (g > 1) { g = 1; }
	if (b > 1) { b = 1; }
	if (r < 0) { r = 0; }
	if (g < 0) { g = 0; }
	if (b < 0) { b = 0; }

	return Color(r, g, b, s);
}


void Color::print_color_values() {
	std::cout 
		<< (int) r 
		<< " " 
		<< (int) g 
		<< " " 
		<< (int) b 
		<< " "
		<< (int) s
		<< std::endl;
}

#endif