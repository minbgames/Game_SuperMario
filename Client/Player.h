#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	enum SCENE { IDLE, WALK, RUN, AIR, FLY, SITDOWN, ATTACK, DEAD, END };
	enum MODE { JUMP, FALL, GROUND };
	enum PLAYERMODE { MINI, NORMAL, FIRE, RACCOON, PLAYER_DEAD, DEFAULT };
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void ChangeSpeed(float _fSpeed);
	const bool& GetUpThrow() const { return m_bUpThrow; }
	void SetJumpInit(MODE _mode, float _initAccel);

public:
	virtual void Initialize();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) override;

private:
	template <typename T>
	CObj* CreateBullet()
	{
		return CAbstractFactory<T>::CreateObj(m_fGunX, m_fGunY, m_fAngle);
	}

	void IsJumping();
	void OffSet();
	void SceneChange();
	void ChangeMode(PLAYERMODE _ePlayerMode);
	void ReturnAdjust();
	void SetFrameKey();

private:	
	bool			m_bUpThrow;
	bool			m_bIsCtrl;
	PLAYERMODE m_ePlayerMode;
	bool			m_bIsChange;
	bool			m_bIsSitDown;
	bool			m_bIsStart;
	bool			m_bSceneTimer;
	bool			m_bUpKeyDown;
	bool			m_bDownKeyDown;

	SCENE		m_eCurScene;	// 현재 애니메이션 상태
	SCENE		m_ePreScene;	// 이전 애니메이션 상태
	DWORD		m_dwTime;
};

