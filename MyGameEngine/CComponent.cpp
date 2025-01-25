#include "CComponent.h"

CComponent::CComponent()
{
	this->m_nDrawType = eDrawType::BACKGROUND;
}

void CComponent::SetDrawType(eDrawType nType)
{
	this->m_nDrawType = nType;
}

eDrawType CComponent::GetDrawType()
{
	return this->m_nDrawType;
}
