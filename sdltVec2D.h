#pragma once

#include <iostream>

namespace sdlt {

	class Vec2D {
	public:
		Vec2D();
		Vec2D(int x, int y);
		Vec2D(double x, double y);

		double getX() const;
		double getY() const;

		void setX(double x);
		void setY(double y);

		void shiftX(double dx);
		void shiftY(double dy);

		Vec2D& operator+=(const Vec2D& rhs);

		friend Vec2D operator+(Vec2D lhs,
			const Vec2D& rhs);

		Vec2D& operator-=(const Vec2D& rhs);

		friend Vec2D operator-(Vec2D lhs,
			const Vec2D& rhs);

		Vec2D& operator*=(const double rhs);

		friend Vec2D operator*(Vec2D lhs,
			const double& rhs);

		// Returns the dot product of *this and rhs
		double dot(Vec2D rhs) const;

		// Returns the cross product of *this and rhs
		double cross(Vec2D rhs) const;

		// Returns the magnitude of the Vec2D
		double mag() const;

		// Returns the magnitude of the position squared
		double mag2() const;

		bool operator==(const Vec2D& other) const;
	private:
		double x;
		double y;
	};

	using Position2D = Vec2D;
	using Velocity2D = Vec2D;
}

std::ostream& operator<<(std::ostream& os, const sdlt::Vec2D& obj);