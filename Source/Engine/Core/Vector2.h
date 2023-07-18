#pragma once
#include <cmath>
#include <sstream>
namespace Twili
{
	class Vector2
	{
	public:
		float x, y;

	public:
		Vector2() :x{ 0 }, y{ 0 } {};
		Vector2(float v) :x { v }, y{ v } {};
		Vector2(float x, float y) : x{ x }, y{ y } {};
		Vector2(int x, int y) : x{ (float)x }, y{ (float)y } {};

		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); };
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); };
		Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); };
		Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); };


		Vector2 operator + (float s) const { return Vector2(x + s, y + s); };
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); };
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); };
		Vector2 operator * (float s) const { return Vector2(x * s, y * s); };
		
		Vector2 operator += (const Vector2& v) {
			x += v.x; y += v.y;
			return *this;
		};
		Vector2 operator -= (const Vector2& v) {
			x -= v.x; y -= v.y;
			return *this;
		};
		Vector2 operator /= (const Vector2& v) {
			x /= v.x; y /= v.y;
			return *this;
		};
		Vector2 operator *= (const Vector2& v) {
			x *= v.x; y *= v.y;
			return *this;
		};


		float lengthSQR() const { return (x * x) + (y * y); };
		inline float length() const {return std::sqrt(lengthSQR()); };

		Vector2 normalized() const { return *this / length(); }
		void normalize() { *this /= length(); }

		float distanceSQR(const Vector2& v) const
		{
			return (v - *this).lengthSQR();
		};
		float distance(const Vector2& v) const
		{
			return (v - *this).length();
		};

		float angle() const { return std::atan2f(y, x); };

		Vector2 Rotate(float radians) const;





	};
	inline std::istream& operator >> (std::istream& stream, Vector2& v)
	{
		std::string line;
		std::getline(stream, line);
		// { ##, ## }
		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);
		return stream;
	}

	inline Vector2 Vector2::Rotate(float radians) const
	{
		float _x = x * std::cos(radians) - y * std::sin(radians);
		float _y = x * std::sin(radians) + y * std::cos(radians);

		return { _x,_y };
	}

	using vec2 = Vector2;
}