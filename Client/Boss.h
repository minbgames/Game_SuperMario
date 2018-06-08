#pragma once
#include "Obj.h"

class CBoss :
	public CObj
{
public:
	CBoss();
	virtual ~CBoss();

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
	void PatternA();
	void PatternB();
	void PatternC();

private:
	int m_iAttackPattern;
	int m_iBulletCount;
	float m_fAngle;
	float m_fOriginX;
	float m_fDashAcc;
	float m_fDashPow;
};

