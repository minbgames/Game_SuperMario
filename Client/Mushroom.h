#pragma once
#include "Obj.h"
class CMushroom :public CObj
{
public:
	CMushroom();
	virtual ~CMushroom();

public:
	virtual void Initialize();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	void isJumping();

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;
};

