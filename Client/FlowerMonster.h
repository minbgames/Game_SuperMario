#pragma once
#include "Obj.h"

class CFlowerMonster :
	public CObj
{
public:
	CFlowerMonster();
	virtual ~CFlowerMonster();

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
	CObj* m_pPlayer;
	float m_fFlowerLengthY;
	float m_fPlusDir;
	bool m_bDownAnim;
	bool m_bUpAnim;
	DWORD m_dwAnimTime;
	int m_iIndex;
};

