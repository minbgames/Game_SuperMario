#pragma once
#include "Obj.h"
class CLeaf :
	public CObj
{
public:
	CLeaf();
	virtual ~CLeaf();

private:
	enum MODE{ JUMP, FALL, GROUND, END };

public:
	virtual void Initialize();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	void isJumping();
	void SetJumpInit(MODE _mode);

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;

private:
	float m_fParabolaX;
	float m_fParabolaAxisX;
};

