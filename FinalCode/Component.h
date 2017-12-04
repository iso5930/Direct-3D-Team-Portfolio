#pragma once

class CObject;

class CComponent
{
protected:
	// Owner
	CObject* m_pOwner;

	// Type
	COM_TYPE m_eComType;

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

public:
	// SetOwner
	void SetOwner(CObject* _pOwner) { m_pOwner = _pOwner; }

	// GetComType
	COM_TYPE GetComType() { return m_eComType; }

public:
	explicit CComponent();
	virtual ~CComponent();
};