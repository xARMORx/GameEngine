#include "CRect.h"
#include <algorithm>

CRect::CRect()
{
	this->left = 0;
	this->top = 0;
	this->right = 0;
	this->bottom = 0;
}

CRect::CRect(long value)
{
	this->left = value;
	this->top = value;
	this->right = value;
	this->bottom = value;
}

CRect::CRect(long left, long top, long right, long bottom)
{
	this->left = left;
	this->top = top;
	this->bottom = right;
	this->right = bottom;
}

bool CRect::IsPointIn(const CVector2d& vPoint)
{
	return (vPoint.x >= std::min(left, right) && vPoint.x <= std::max(left, right) &&
		vPoint.y >= std::min(top, bottom) && vPoint.y <= std::max(top, bottom));
}

void CRect::operator=(const CRect& rect)
{
	this->left = rect.left;
	this->top = rect.top;
	this->right = rect.right;
	this->bottom = rect.bottom;
}

bool CRect::operator==(const CRect& rect) const
{
	return (this->top == rect.top) && 
		(this->left == rect.left) && 
		(this->bottom == rect.bottom) && 
		(this->right == rect.right);
}

void CRect::operator-(const CRect& rect)
{
	this->top -= rect.top;
	this->left -= rect.left;
	this->bottom -= rect.bottom;
	this->right -= rect.right;
}

void CRect::operator+(const CRect& rect)
{
	this->top += rect.top;
	this->left += rect.left;
	this->bottom += rect.bottom;
	this->right += rect.right;
}

void CRect::operator*(const CRect& rect)
{
	this->top *= rect.top;
	this->left *= rect.left;
	this->bottom *= rect.bottom;
	this->right *= rect.right;
}

void CRect::operator/(const CRect& rect)
{
	this->top /= rect.top;
	this->left /= rect.left;
	this->bottom /= rect.bottom;
	this->right /= rect.right;
}
