#include "stdafx.h"
#include "TurtleMonster.h"
#include "Player.h"
#include "Effect.h"

CTurtleMonster::CTurtleMonster()
{
}


CTurtleMonster::~CTurtleMonster()
{
	Release();
}

void CTurtleMonster::Initialize()
{
	m_pRightFrameKey = L"NormalTurtleRight";
	m_pLeftFrameKey = L"NormalTurtleLeft";
	m_eCurScene = WALK;
	m_ePreScene = m_eCurScene;

	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = 500.f;
	// 초기 위치 설정

	FrameChange(0, 1, 0, 200);
	SetRangeValue(50, 55, 28, 42);
	SetAdjustValue(15, -15, 10, 5);
	// ROI 설정

	m_bIsFall = true;
	m_bIsJump = false;
	m_bIsArrived = false;
	m_bIsHolding = false;
	m_bIsFallDead = false;
	m_fSpeed = 1.f;
	m_fDir = -1.0f;
	m_fJumpPow = TURTLE_JUMP_POW;
	m_fJumpAcc = 0.f;
	m_iState = 0;
	// 멤버변수

	m_dwTime = GetTickCount();
}

void CTurtleMonster::LateInit()
{
	m_pPlayer = CObjectMgr::GetInstance()->GetPlayer();
}

int CTurtleMonster::Update()
{
	CObj::LateInit();
	if(m_bIsFallDead) return DEAD_OBJ;

	if (m_bIsDead)
	{
		CObj* pObj = CAbstractFactory<CEffect>::CreateObj(m_tInfo.fX - 20.f, m_tInfo.fY - 30.f);
		CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::EFFECT);

		CSoundMgr::GetInstance()->PlaySound(L"Shell SFX.wav", CSoundMgr::TURTLE);
		m_pPlayer->SetHold(false);
		return DEAD_OBJ;
	}

	if (m_bIsHolding) { // When player hold
		if (!m_pPlayer->GetHold()) { // if player is not hold when player hold
			m_bIsHolding = false;
			if (dynamic_cast<CPlayer*>(m_pPlayer)->GetUpThrow()) {
				m_pPlayer->SetColOption(false);
				m_fJumpAcc = TURTLE_JUMP_INIT;
				m_bIsJump = true;
				ChangeState(3);
			}
			else {
				m_bIsFall = true;
				m_fJumpAcc = TURTLE_JUMP_ZERO;
				m_fDir = m_pPlayer->GetDir();
				m_tInfo.fX += 40.f*m_fDir;
				ChangeState(2);
			}
			return NO_EVENT;
		}

		m_tInfo.fY = m_pPlayer->GetInfo().fY - 5.0f;
		m_tInfo.fX = m_pPlayer->GetInfo().fX + 30.0f * m_pPlayer->GetDir();
		return NO_EVENT;
	}

	if (0 == m_iState) {
		m_tInfo.fX += m_fDir*m_fSpeed;
		IsJumping();
	}
	else if (1 == m_iState) {
		IsJumping();
	}
	else if (2 == m_iState) {
		m_tInfo.fX += m_fDir*m_fSpeed;
		IsJumping();
	}
	else if (3 == m_iState) {
		IsJumping();
	}
	return NO_EVENT;
}

void CTurtleMonster::LateUpdate()
{
	if (false)
	{
		m_bIsDead = true;
		return;
	}


	if (m_tInfo.fX < 0 || m_tInfo.fX > MAINSTAGE_REAL_X)
		m_fDir *= -1.f;

	SceneChange();
	CObj::Animation();
}

void CTurtleMonster::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	if (m_fDir > 0) {
		CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(m_pRightFrameKey));
	}
	else {
		CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(m_pLeftFrameKey));
	}

	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX + m_tAdjust.iAxisMoveX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY + m_tAdjust.iAxisMoveY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tRenInfo.fCX + m_tAdjust.iMarginX,
		m_tFrame.iScene * (int)m_tRenInfo.fCY + m_tAdjust.iMarginY,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CTurtleMonster::Release()
{
}

void CTurtleMonster::ChangeState(int _iState)
{
	bool bTemp = true;
	if (m_iState == 3) bTemp = false;
	m_iState = _iState;

	CObj* pObj = CAbstractFactory<CEffect>::CreateObj(m_tInfo.fX-20.f, m_tInfo.fY-30.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::EFFECT);

	switch (m_iState)
	{
	case 0: // 정상 상태
		m_fSpeed = TURTLE_SPEED_NORMAL;
		m_hBrush = CreateSolidBrush(RGB(255, 255, 255));
		m_eCurScene = WALK;
		break;
	case 1: // 껍질 정지 상태
		m_eCurScene = IDLE;
		m_fSpeed = TURTLE_SPEED_ZERO;
		m_hBrush = CreateSolidBrush(RGB(0, 255, 0));
		m_pPlayer->SetColOption(true);
		m_bColOpt = true;
		if (bTemp) CSoundMgr::GetInstance()->PlaySound(L"Shell SFX.wav", CSoundMgr::TURTLE);
		break;
	case 2: // 껍질 이동 상태
		m_eCurScene = RUN;
		m_fSpeed = TURTLE_SPEED_ATTACK;
		m_hBrush = CreateSolidBrush(RGB(255, 0, 0));
		CSoundMgr::GetInstance()->PlaySound(L"Shell SFX.wav", CSoundMgr::TURTLE);
		break;
	case 3: // 껍질 점프 상태
		m_eCurScene = IDLE;
		m_fSpeed = TURTLE_SPEED_ZERO;
		m_hBrush = CreateSolidBrush(RGB(0, 255, 0));
		m_pPlayer->SetColOption(false);
		m_bColOpt = false;
		break;
	default:
		break;
	}
}

void CTurtleMonster::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (_objectID == ObjectID::PLAYER) {
		if (0 == _iState) { // 플레이어 상태: 0
			if (_dir == DirID::UP) {
				switch (m_iState)
				{
				case 0:
					ChangeState(1);
					break;
				case 1:
					ChangeState(2);
					break;
				case 2:
					ChangeState(1);
					break;
				case 3:
					m_bColOpt = true;
					m_bIsJump = false;
					m_bIsFall = true;
					m_bIsArrived = false;
					m_fJumpAcc = 0.f;
					break;
				default:
					break;
				}
			}
			else if (_dir == DirID::LEFT) {
				switch (m_iState)
				{
				case 1:
					m_fDir = 1.0f;
					ChangeState(2);
					break;
				default:
					break;
				}
			}
			else if (_dir == DirID::RIGHT) {
				switch (m_iState)
				{
				case 1:
					m_fDir = -1.0f;
					ChangeState(2);
					break;
				default:
					break;
				}
			}
		}
		else { // 플레이어 상태: 1
			if (_dir == DirID::UP) {
				switch (m_iState)
				{
				case 0:
					ChangeState(1);
					break;
				case 1:
					ChangeState(2);
					break;
				case 2:
					ChangeState(1);
					break;
				case 3:
					m_bColOpt = true;
					m_bIsJump = false;
					m_bIsFall = true;
					m_bIsArrived = false;
					m_fJumpAcc = TURTLE_JUMP_ZERO;
					CSoundMgr::GetInstance()->PlaySound(L"Shell SFX.wav", CSoundMgr::TURTLE);
					break;
				default:
					break;
				}
			}
			else { // 잡기
				if (1 == m_iState) { //등껍질일때만 
					m_bIsHolding = true;
					m_pPlayer->SetHold(true);
					m_fDir = m_pPlayer->GetDir();
				}
			}
		}
	}
	else if (_objectID == ObjectID::TURTLE_MONSTER) {
		if (m_pPlayer->GetHold()) {
			m_bIsDead = true;
		}
		else {
			if (2 == _iState || 3 == _iState) {
				m_bIsDead = true;
			}
			else {
				if (0 == m_iState || 1 == m_iState) {
					m_fDir *= -1.f;
				}
			}
		}
	}
	else if (_objectID == ObjectID::FLOWER_MONSTER) {
		if (m_pPlayer->GetHold()) {
			m_bIsDead = true;
		}
	}
	else if (_objectID == ObjectID::OBSTACLE || _objectID == ObjectID::QUESTION_BOX) {
		if (_dir == DirID::LEFT) {
			m_fDir = 1.f;
			if(2 == m_iState) CSoundMgr::GetInstance()->PlaySound(L"Bump V1 SFX.wav", CSoundMgr::TURTLE);
		}
		else if (_dir == DirID::RIGHT) {
			m_fDir = -1.f;
			if (2 == m_iState) CSoundMgr::GetInstance()->PlaySound(L"Bump V1 SFX.wav", CSoundMgr::TURTLE);
		}
		else if (_dir == DirID::UP) {
			m_bIsJump = false;
			m_bIsFall = true;
			m_bIsArrived = false;
			m_fJumpAcc = TURTLE_JUMP_INIT/2;
			if (2 == m_iState) CSoundMgr::GetInstance()->PlaySound(L"Bump V1 SFX.wav", CSoundMgr::TURTLE);
		}
	}
	else if (_objectID == ObjectID::NOTE_BOX) {
		if (_dir == DirID::LEFT) {
			m_fDir = 1.f;
			if (2 == m_iState) CSoundMgr::GetInstance()->PlaySound(L"Bump V1 SFX.wav", CSoundMgr::TURTLE);
		}
		else if (_dir == DirID::RIGHT) {
			m_fDir = -1.f;
			if (2 == m_iState) CSoundMgr::GetInstance()->PlaySound(L"Bump V1 SFX.wav", CSoundMgr::TURTLE);
		}
		else if (_dir == DirID::UP) {
			m_bIsJump = false;
			m_bIsFall = true;
			m_bIsArrived = false;
			m_fJumpAcc = TURTLE_JUMP_INIT;
			if (2 == m_iState) CSoundMgr::GetInstance()->PlaySound(L"Bump V1 SFX.wav", CSoundMgr::TURTLE);
		}
	}
	else if (_objectID == ObjectID::BULLET) {
		m_bIsDead = true;
	}
	else if (_objectID == ObjectID::BOSS) {
		m_bIsDead = true;
	}
	else if (_objectID == ObjectID::ATTACK) {
		if (m_dwTime + 200 < GetTickCount()) {

			switch (m_iState)
			{
			case 0:
				ChangeState(1);
				break;
			case 1:
			case 2:
			case 3:
				m_bIsDead = true;
				break;
			}

			m_dwTime = GetTickCount();
		}
	}
}

void CTurtleMonster::IsJumping()
{
	if (m_tInfo.fY > 1350) m_bIsFallDead = true;

	float fMoveY = m_tInfo.fY;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.fX, &fMoveY, this);
	switch (m_iState)
	{
	case 0:
		if (m_fPrevMoveY + 10.f < fMoveY) m_bIsArrived = true;
		break;
	case 2:
		if (m_fPrevMoveY + 10.f < fMoveY) m_bIsFall = true;
		break;
	default:
		break;
	}

	if (m_bIsJump)
	{
		m_tInfo.fY -= m_fJumpPow*m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		if (TURTLE_JUMP_ZERO == m_fJumpAcc) {
			m_fJumpAcc = TURTLE_JUMP_INIT;
		}
		else {
			m_fJumpAcc += TURTLE_ACCEL_THROW_INC;
		}
		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f)
		{
			if (m_fJumpPow * m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f < 0) {
				m_bIsJump = false;
				m_bIsArrived = false;
				m_fJumpAcc = TURTLE_JUMP_ZERO;
				m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;
				if (3 == m_iState) {
					ChangeState(1);
				}
			}
		}
	}
	else if (m_bIsFall)
	{
		m_tInfo.fY += GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		m_fJumpAcc += TURTLE_ACCEL_FALL_INC;
		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f)
		{
			m_bIsFall = false;
			m_bIsArrived = false;
			m_fJumpAcc = TURTLE_JUMP_ZERO;
			m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;
			if (3 == m_iState) {
				ChangeState(1);
			}
		}
	}
	else if (m_bIsArrived) {
		m_fDir *= -1.f;
		m_bIsArrived = false;
	}
	else if (bColl)
		m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;

	m_fPrevMoveY = fMoveY;
}

void CTurtleMonster::SceneChange()
{
	if (m_ePreScene != m_eCurScene)
	{
		switch (m_eCurScene)
		{
		case IDLE:
			FrameChange(0, 0, 1, 200);
			break;
		case WALK:
			FrameChange(0, 1, 0, 100);
			break;
		case RUN:
			FrameChange(0, 3, 3, 50);
			break;
		default:
			break;
		}
		m_ePreScene = m_eCurScene;
	}
}
