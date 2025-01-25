#pragma once

enum eDrawType {
	BACKGROUND,
	WINDOW,
	FOREGROUND
};

class CComponent
{
protected:

	eDrawType m_nDrawType;
public:
	CComponent();
	
	void SetDrawType(eDrawType nType);
	eDrawType GetDrawType();
};