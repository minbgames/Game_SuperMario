#pragma once
#include "Obj.h"
class CFinalMsg :public CObj
{
public:
	CFinalMsg();
	~CFinalMsg();

	// Inherited via CObj
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

