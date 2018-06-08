#pragma once
#include "Obj.h"
class CAttack :public CObj
{
public:
	CAttack();
	~CAttack();

public:
	void SetPlayer(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	void SetMargin(float _fMarginX, float _fMarginY) { m_fMarginX = _fMarginX; m_fMarginY = _fMarginY; }

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CObj* m_pPlayer;
	float m_fMarginX;
	float m_fMarginY;
};

