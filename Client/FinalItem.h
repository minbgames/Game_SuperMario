#pragma once
#include "Obj.h"
class CFinalItem :
	public CObj
{
public:
	CFinalItem();
	~CFinalItem();

public:
	void SetItemNumber(int _num) { m_iAnimState = 2; m_iSetNumber = _num; m_bIsSetNumber = true; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void LateInit() override;
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;

private:
	bool m_bIsSetNumber;
	int m_iSetNumber;
};

