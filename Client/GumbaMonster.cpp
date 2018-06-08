#include "stdafx.h"
#include "GumbaMonster.h"
#include "Player.h"
#include "Effect.h"

CGumbaMonster::CGumbaMonster()
{
}


CGumbaMonster::~CGumbaMonster()
{
	Release();
}

void CGumbaMonster::Initialize()
{
	m_pRightFrameKey = L"NormalMushroom";
	m_pLeftFrameKey = L"NormalMushroom";

	FrameChange(0, 1, 0, 200);
	SetRangeValue(50, 50, 28, 20);
	SetAdjustValue(0, -6, 5, 0);
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

void CGumbaMonster::LateInit()
{
}

int CGumbaMonster::Update()
{
	CObj::LateInit();
	if (m_bIsFallDead) return DEAD_OBJ;

	if (m_bIsDead)
	{
		CObj* pObj = CAbstractFactory<CEffect>::CreateObj(m_tInfo.fX - 20.f, m_tInfo.fY - 30.f);
		CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::EFFECT);

		CSoundMgr::GetInstance()->PlaySound(L"Shell SFX.wav", CSoundMgr::TURTLE);
		return DEAD_OBJ;
	}

	m_tInfo.fX += m_fDir*m_fSpeed;
	IsJumping();

	return NO_EVENT;
}

void CGumbaMonster::LateUpdate()
{
	if (m_tInfo.fX < 0 || m_tInfo.fX > MAINSTAGE_REAL_X)
		m_fDir *= -1.f;

	CObj::Animation();
}

void CGumbaMonster::Render(HDC hDC)
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

void CGumbaMonster::Release()
{
}

void CGumbaMonster::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (_objectID == ObjectID::PLAYER) {
		if (_dir == DirID::UP) {
			m_bIsDead = true;
		}
	}
	else if (_objectID == ObjectID::TURTLE_MONSTER) {
		if (2 == _iState || 3 == _iState) {
			m_bIsDead = true;
		}
		else if (0 == m_iState || 1 == m_iState) {
			m_fDir *= -1.f;
		}
	}
	else if (_objectID == ObjectID::OBSTACLE || _objectID == ObjectID::QUESTION_BOX) {
		if (_dir == DirID::LEFT) {
			m_fDir = 1.f;
		}
		else if (_dir == DirID::RIGHT) {
			m_fDir = -1.f;
		}
	}
	else if (_objectID == ObjectID::NOTE_BOX) {
		if (_dir == DirID::LEFT) {
			m_fDir = 1.f;
		}
		else if (_dir == DirID::RIGHT) {
			m_fDir = -1.f;
		}
	}
	else if (_objectID == ObjectID::BULLET) {
		m_bIsDead = true;
	}
	else if (_objectID == ObjectID::ATTACK) {
		m_bIsDead = true;
	}
}

void CGumbaMonster::IsJumping()
{
	if (m_tInfo.fY > 1350) m_bIsFallDead = true;

	float fMoveY = m_tInfo.fY;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.fX, &fMoveY, this);

	if (m_fPrevMoveY + 10.f < fMoveY) m_bIsArrived = true;

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

