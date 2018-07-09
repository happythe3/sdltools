#include "sdltVec2D.h"

using namespace sdlt;

Vec2D::Vec2D()
	:x(0.0), y(0.0)
{
}

Vec2D::Vec2D(int x, int y)
	:x(x), y(y)
{
}

Vec2D::Vec2D(double x, double y)
	:x(x), y(y)
{
}


Vec2D & Vec2D::operator+=(const Vec2D & rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2D sdlt::operator+(Vec2D lhs, const Vec2D & rhs)
{
	lhs += rhs;
	return lhs;
}

Vec2D & Vec2D::operator-=(const Vec2D & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2D sdlt::operator-(Vec2D lhs, const Vec2D & rhs)
{
	lhs -= rhs;
	return lhs;
}

Vec2D & Vec2D::operator*=(const double rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vec2D sdlt::operator*(Vec2D lhs, const double & rhs)
{
	lhs *= rhs;
	return lhs;
}

double Vec2D::dot(Vec2D rhs) const
{
	return x * rhs.x + y * rhs.y;
}

double Vec2D::cross(Vec2D rhs) const
{
	return x * rhs.y - y * rhs.x;
}

double Vec2D::mag() const
{
	return std::sqrt(x*x + y * y);
}

double Vec2D::mag2() const
{
	return x * x + y * y;
}

bool Vec2D::operator==(const Vec2D & rhs) const
{
	return (fabs(x - rhs.x) < 0.001) && (fabs(y - rhs.y) < 0.001);
}

std::ostream & operator<<(std::ostream & os, const Vec2D & P)
{
	return os << "(" << P.getX() << ", " << P.getY() << ")";
}

double sdlt::Vec2D::getX() const
{
	return x;
}

double sdlt::Vec2D::getY() const
{
	return y;
}

void sdlt::Vec2D::setX(double nx)
{
	x = nx;
}

void sdlt::Vec2D::setY(double ny)
{
	y = ny;
}

void sdlt::Vec2D::shiftX(double dx)
{
	x += dx;
}

void sdlt::Vec2D::shiftY(double dy)
{
	y += dy;
}
