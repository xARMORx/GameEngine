#pragma once
class CVector2d
{
public:
	float x;
	float y;

	CVector2d();
	CVector2d(float fValue);
	CVector2d(float x, float y);

	bool operator==(const CVector2d& vector2d) const;
	void operator=(const CVector2d& vector2d);
	void operator-(const CVector2d& vector2d);
	void operator+(const CVector2d& vector2d);
	void operator*(const CVector2d& vector2d);
	void operator/(const CVector2d& vector2d);
};

