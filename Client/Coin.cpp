#include "stdafx.h"
#include "Coin.h"


CCoin::CCoin()
{
	m_eLayer = LayerID::ITEM;
}


CCoin::~CCoin()
{
}

void CCoin::Initialize()
{
	m_bIsJump = false;
	m_bIsFall = false;
	m_fJumpPow = 12.f;
	m_iState = 1;
}

void CCoin::LateInit()
{
	SetRangeValue(48, 48, 16, 16);
	FrameChange(0, 3, 0, 100);
	m_hBrush = CreateSolidBrush(RGB(0, 200, 200));
	if (0 == m_iState)
		m_bIsJump = true;

}

int CCoin::Update()
{
	CObj::LateInit();

	if (m_bIsDead)
		return DEAD_OBJ;

	if (0 == m_iState) {
		isJumping();
	}

	return NO_EVENT;
}

void CCoin::LateUpdate()
{
	CObj::Animation();
}

void CCoin::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"Item"));


	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		16* m_tFrame.iFrameStart,
		64,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CCoin::isJumping()
{
	float fMoveY = m_tInfo.fY;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.fX, &fMoveY, this);

	if (m_fPrevMoveY + 10.f < fMoveY) m_bIsFall = true;

	if (m_bIsJump)
	{
		m_tInfo.fY -= m_fJumpPow * m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;

		if (m_fJumpAcc < PLAYER_ACCEL_LIMIT) m_fJumpAcc += PLAYER_ACCEL_INC;

		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f) // 점프 도중 지면에 닿았을 때
		{
			if (m_fJumpPow * m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f < 0) {
				m_bIsDead = true;
			}
		}
	}
	else if (m_bIsFall)
	{
		m_tInfo.fY += GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		if (m_fJumpAcc < PLAYER_ACCEL_LIMIT) m_fJumpAcc += PLAYER_ACCEL_INC;

		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f)
		{
			m_bIsFall = false;
			m_fJumpAcc = PLAYER_JUMP_INIT;
			m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;
		}
	}
	else if (bColl)
		m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;

	m_fPrevMoveY = fMoveY;
}

void CCoin::Release()
{
}

void CCoin::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (m_iState == 1) {
		CSoundMgr::GetInstance()->PlaySoundW(L"Coin Obtained SFX.wav", CSoundMgr::EFFECT);
	}
	m_bIsDead = true;
}
