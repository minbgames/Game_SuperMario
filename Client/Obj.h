#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const ObjectID::OBJID& GetObjectID() const { return m_eObjectID; }
	const int& GetObjectState() const { return m_iState; }
	const LayerID::ID& GetLayer() const { return m_eLayer; }
	const STAT& GetStat() const { return m_tStat; }
	const INFO& GetInfo() const { return m_tInfo; }
	const RECT& GetRect() const { return m_tRect; }
	const bool& GetDead() const { return m_bIsDead; }
	const bool& GetHold() const { return m_bIsHolding; }
	const float& GetDir() const { return m_fDir; }
	const float& GetSpeed() const { return fabsf(m_fSpeed); }
	const bool& GetColOption() const{ return m_bColOpt; }

public:
	void SetObjectID(const ObjectID::OBJID& _objectID) { m_eObjectID = _objectID; }
	void SetObjectState(const int _iState) { m_iState = _iState; }
	void SetInfo(const INFO& rInfo) { m_tInfo = rInfo; }
	void SetDamage(float fAtt) { m_tStat.fHp -= fAtt; }
	void SetDead() { m_bIsDead = true; }
	void SetHold(bool _hold) { m_bIsHolding = _hold; }
	void SetPos(float x, float y) { m_tInfo.fX = x, m_tInfo.fY = y; }
	void SetSize(float x, float y) { m_tInfo.fCX = x, m_tInfo.fCY = y; }
	void SetDir(float _dir) { m_fDir = _dir; }
	void SetColOption(bool _colOpt) { m_bColOpt = _colOpt; }
	void SetSpeed(float _speed) { m_fSpeed = _speed; }

public:
	virtual void OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState) = 0;

public:
	virtual void Initialize() = 0;
	virtual void LateInit();
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

protected:
	void UpdateRect();
	void Animation();
	void FrameChange(int _startX, int _endX, int _lineY, int _time);
	void SetAdjustValue(int _axisX, int _axisY, int _marginX, int _marginY);
	void SetRangeValue(int _cx, int _cy, int _rencx, int _rency);

protected:
	INFO	m_tInfo;
	INFO	m_tRenInfo;

	RECT	m_tRect;

	STAT	m_tStat;
	FRAME	m_tFrame;

	ADJUST m_tAdjust;

	bool	m_bIsInit;
	bool	m_bIsDead;

	float	m_fSpeed;
	float	m_fDir;

	int m_iState;
	int m_iAnimInit;
	int m_iAnimState;
	bool m_bAnimOnce;
	float m_fMultiple;

	LayerID::ID		m_eLayer;
	bool		m_bIsJump;	// 점프 상태
	bool		m_bIsFall;
	bool		m_bIsHolding;
	bool		m_bColOpt;

	float		m_fJumpPow;	// 점프 힘
	float		m_fJumpAcc;	// 점프 가속도

	float		m_fPrevMoveY;

	ObjectID::OBJID m_eObjectID;
	HBRUSH	m_hBrush;
	HBRUSH	m_hPrev;

	TCHAR*		m_pLeftFrameKey;
	TCHAR*		m_pRightFrameKey;
	
	DWORD m_dwTime;

};

