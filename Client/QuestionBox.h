#pragma once
#include "Obj.h"
class CQuestionBox :
	public CObj
{
public:
	CQuestionBox();
	virtual ~CQuestionBox();

public:
	virtual void Initialize();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	void ChangeState(int _state);
	void SetItemID(ItemID::ID _itemID) { m_eItemID = _itemID; }

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;

private:
	ItemID::ID m_eItemID;
};

