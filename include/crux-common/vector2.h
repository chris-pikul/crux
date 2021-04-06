#pragma once

#include <iostream>

namespace crux {
	template<typename T>
	struct vector2 {
		T x, y;

		vector2() : x(T{}), y(T{}) {}
		vector2(const vector2<T>& copy) : x(copy.x), y(copy.y) {}

		vector2(const T& init) : x(init), y(init) {}
		vector2(const T& initX, const T& initY) : x(initX), y(initY) {}
		
		const vector2<T>& operator=(const vector2<T>& obj) { x = obj.x; y = obj.y; return *this; }
		const vector2<T>& operator+=(const vector2<T>& obj) { x += obj.x; y += obj.y; return *this; }
		const vector2<T>& operator-=(const vector2<T>& obj) { x -= obj.x; y -= obj.y; return *this; }
		const vector2<T>& operator*=(const vector2<T>& obj) { x *= obj.x; y *= obj.y; return *this; }
		const vector2<T>& operator/=(const vector2<T>& obj) { x /= obj.x; y /= obj.y; return *this; }

		T& operator[](std::size_t idx) { return ( idx == 0 ? x : y); }
		const T& operator[](std::size_t idx) const { return (idx == 0 ? x : y); }
	};

	template<typename T>
	bool operator==(const vector2<T>& lhs, const vector2<T>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }

	template<typename T>
	bool operator!=(const vector2<T>& lhs, const vector2<T>& rhs) { return !(lhs == rhs); }

	template<typename T>
	bool operator<(const vector2<T>& lhs, const vector2<T>& rhs) { return lhs.x < rhs.x || lhs.y < rhs.y; }

	template<typename T>
	bool operator>(const vector2<T>& lhs, const vector2<T>& rhs) { return lhs.x > rhs.x || lhs.y > rhs.y; }

	template<typename T>
	bool operator<=(const vector2<T>& lhs, const vector2<T>& rhs) { return lhs == rhs || lhs < rhs; }

	template<typename T>
	bool operator>=(const vector2<T>& lhs, const vector2<T>& rhs) { return lhs == rhs || lhs > rhs; }

	template<typename T>
	vector2<T> operator+(const vector2<T>& lhs, const vector2<T>& rhs) { return vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y); }

	template<typename T>
	vector2<T> operator-(const vector2<T>& lhs, const vector2<T>& rhs) { return vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y); }

	template<typename T>
	vector2<T> operator*(const vector2<T>& lhs, const vector2<T>& rhs) { return vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y); }

	template<typename T>
	vector2<T> operator/(const vector2<T>& lhs, const vector2<T>& rhs) { return vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y); }

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const vector2<T>& obj) {
		out << "vector2{" << obj.x << ", " << obj.y << "}";
		return out;
	}
}
