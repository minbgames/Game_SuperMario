#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	void IsJumping();
	void SetVector(float _vectorX, float _vectorY) { m_fVectorX = _vectorX; m_fVectorY = _vectorY;}

public:
	virtual void Initialize();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;

private:
	bool m_bBulletInit;
	float m_fSlowSpeed;
	float m_fVectorX;
	float m_fVectorY;
};

