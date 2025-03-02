#include "CVector2d.h"

CVector2d::CVector2d()
{
	this->x = 0.f;
	this->y = 0.f;
}

CVector2d::CVector2d(float fValue)
{
	this->x = fValue;
	this->y = fValue;
}

CVector2d::CVector2d(float x, float y)
{
	this->x = x;
	this->y = y;
}

CVector2d::CVector2d(ImVec2 ImVec)
{
	this->x = ImVec.x;
	this->y = ImVec.y;
}

ImVec2 CVector2d::ToImVec2()
{
	return { this->x, this->y };
}

bool CVector2d::operator==(const CVector2d& vector2d) const
{
	return (this->x == vector2d.x) && (this->y == vector2d.y);
}

void CVector2d::operator=(const CVector2d& vector2d)
{
	this->x = vector2d.x;
	this->y = vector2d.y;
}

void CVector2d::operator-(const CVector2d& vector2d)
{
	this->x -= vector2d.x;
	this->y -= vector2d.y;
}

void CVector2d::operator+(const CVector2d& vector2d)
{
	this->x += vector2d.x;
	this->y += vector2d.y;
}

void CVector2d::operator*(const CVector2d& vector2d)
{
	this->x *= vector2d.x;
	this->y *= vector2d.y;
}

void CVector2d::operator/(const CVector2d& vector2d)
{
	this->x *= vector2d.x;
	this->y *= vector2d.y;
}
