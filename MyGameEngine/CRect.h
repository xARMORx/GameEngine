#pragma once
#include "CVector2d.h"

class CRect
{
public:
	long left;
	long top;
	long right;
	long bottom;

	CRect();
	CRect(long value);
	CRect(long left, long top, long right, long bottom);

	bool IsPointIn(const CVector2d& vPoint);

	bool operator==(const CRect& rect) const;
	void operator=(const CRect& rect);
	void operator-(const CRect& rect);
	void operator+(const CRect& rect);
	void operator*(const CRect& rect);
	void operator/(const CRect& rect);
};
