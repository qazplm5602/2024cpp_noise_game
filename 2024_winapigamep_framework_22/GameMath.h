#pragma once
class GameMath
{
public:
	template <typename T>
	static T Lerp(T a, T b, float t) { return a + t * (b - a); }
};

