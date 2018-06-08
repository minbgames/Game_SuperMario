#pragma once
#include "Obj.h"

class CGumbaMonster :
	public CObj
{
public:
	CGumbaMonster();
	virtual ~CGumbaMonster();

public:
	virtual void Initialize();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;

public:
	void IsJumping();

private:
	bool			m_bIsArrived;
	bool			m_bIsFallDead;
};

