#ifndef _VECTOR_H
#define _VECTOR_H

#include <cmath>

class Vector {
public:
	double x, y, z;
	int size = 3;

	~Vector() {};
	Vector() {}
	Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	Vector& operator=(Vector rhs);

	// Vector mathematical operations                                                                                                                                                                                               
	Vector operator+(const Vector& rhs);
	Vector& operator+=(const Vector& rhs);
	Vector operator-(const Vector& rhs);
	Vector& operator-=(const Vector& rhs);

	// Vector scalar operations
	Vector operator+(const double& rhs) const;
	Vector operator*(const double& rhs) const;

	Vector cross(const Vector& rhs); // Cross-Product
	double dot(const Vector& rhs); // Dot-Product
	Vector normalize(); // Normalize
	Vector negative(); // Negative 
	double mag(); // mag

	static Vector zero() { return Vector(0, 0, 0); }
	static Vector X()	 { return Vector(1, 0, 0); }
	static Vector Y()	 { return Vector(0, 1, 0); }
	static Vector Z()	 { return Vector(0, 0, 1); }

	void swap(Vector& rhs);
	void print_vector();
};

Vector& Vector::operator=(Vector rhs) {
	swap(rhs);
	return *this;
}

Vector Vector::operator+(const Vector& rhs) {
	Vector result(*this);
	result += rhs;
	return result;
}

Vector& Vector::operator+=(const Vector& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

Vector Vector::operator-(const Vector& rhs) {
	Vector result(*this);
	result -= rhs;
	return result;
}

Vector& Vector::operator-=(const Vector& rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

Vector Vector::operator+(const double& rhs) const {
	Vector result(*this);
	result.x += rhs;
	result.y += rhs;
	result.z += rhs;
	return result;
}

Vector Vector::operator*(const double& rhs) const {
	Vector result(*this);
	result.x *= rhs;
	result.y *= rhs;
	result.z *= rhs;
	return result;
}

Vector Vector::cross(const Vector& rhs) {
	double a = (y * rhs.z) - (z * rhs.y);
	double b = (z * rhs.x) - (x * rhs.z);
	double c = (x * rhs.y) - (y * rhs.x);
	Vector product(a, b, c);
	return product;
}

double Vector::dot(const Vector& rhs) {
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

double Vector::mag() {
	return sqrt((x * x) + (y *y) + (z * z));
}

Vector Vector::normalize() {
	double mag = sqrt((x * x) + (y *y) + (z * z));
	return Vector(x / mag, y / mag, z / mag);
}

Vector Vector::negative() {
	return Vector(-x, -y, -z);
}

void Vector::swap(Vector& rhs) {
	using std::swap;

	swap(this->x, rhs.x);
	swap(this->y, rhs.y);
	swap(this->z, rhs.z);
}

void Vector::print_vector() {
	std::cout 
		<< x 
		<< " " 
		<< y 
		<< " "
		<< z 
		<< std::endl;
}

#endif