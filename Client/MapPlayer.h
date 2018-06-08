#pragma once
#include "Obj.h"
class CMapPlayer :
	public CObj
{
public:
	CMapPlayer();
	virtual ~CMapPlayer();

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool m_bIsMove;
	INFO m_tDstInfo;
	DirID::DIRECTION m_eDir;

};

