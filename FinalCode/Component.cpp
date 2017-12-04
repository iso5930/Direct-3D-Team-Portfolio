#include "Stdafx.h"
#include "Component.h"

CComponent::CComponent()
{
	// Owner
	m_pOwner = NULL;

	// ComType
	m_eComType = COM_TYPE_END;
}

CComponent::~CComponent()
{
}