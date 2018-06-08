#pragma once
#include "Obj.h"
class CDoor :
	public CObj
{
public:
	CDoor();
	~CDoor();

	// Inherited via CObj
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

