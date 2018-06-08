#pragma once
#include "Obj.h"

class CCircleMonster :
	public CObj
{
public:
	CCircleMonster();
	virtual ~CCircleMonster();

public:
	virtual void Initialize();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;
	void SetCenterPos(float _x, float _y) { m_fCenterX = _x; m_fCenterY = _y; }

private:
	float			m_fCenterX;
	float			m_fCenterY;
	float			m_fAngle;
	float			m_fLength;
};

