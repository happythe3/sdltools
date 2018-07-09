/*
Copyright 2018 Alexander Shearer

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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