#pragma once
#include "Obj.h"

class CTurtleMonster :
	public CObj
{

public:
	enum SCENE { IDLE, WALK, RUN, END };

public:
	CTurtleMonster();
	virtual ~CTurtleMonster();

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
	void ChangeState(int _iState);
	void IsJumping();
	void SceneChange();

private:
	CObj*			m_pPlayer;
	bool			m_bIsArrived;
	SCENE		m_eCurScene;	// 현재 애니메이션 상태
	SCENE		m_ePreScene;	// 이전 애니메이션 상태
	bool			m_bIsFallDead;
};

