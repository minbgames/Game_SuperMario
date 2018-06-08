#include "stdafx.h"
#include "FireMonster.h"
#include "Player.h"

CFireMonster::CFireMonster()
{
}


CFireMonster::~CFireMonster()
{
	Release();
}

void CFireMonster::Initialize()
{
	m_fDir = -1.0f;
	m_pRightFrameKey = L"FireMonster";
	m_pLeftFrameKey = L"FireMonster";
	SetRangeValue(42, 48, 14, 16);
	SetAdjustValue(0, 0, 0, 0);
	FrameChange(0, 2, 0, 30);
	m_fJumpPow = 16.f;
	m_bDownAnim = true;
	m_bIsJump = false;

	m_dwAnimTime = GetTickCount();
}

void CFireMonster::LateInit()
{
	m_pPlayer = CObjectMgr::GetInstance()->GetPlayer();
}

int CFireMonster::Update()
{
	CObj::LateInit();

	if (m_bDownAnim) {
		if (m_dwAnimTime + 3000 < GetTickCount()) {
			if (fabsf(m_pPlayer->GetInfo().fX - m_tInfo.fX) < 250.f) {
				m_bDownAnim = false;
				m_bIsJump = true;
				m_fJumpAcc = 1.5f;
			}
		}
		return NO_EVENT;
	}

	IsJumping();

	if (m_tInfo.fY > 1350.f) {
		m_tInfo.fY = 1350.f;
		m_bDownAnim = true;
		m_dwAnimTime = GetTickCount();
	}

	return NO_EVENT;
}

void CFireMonster::LateUpdate()
{
	CObj::Animation();
}

void CFireMonster::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(m_pRightFrameKey));

	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX + m_tAdjust.iAxisMoveX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY + m_tAdjust.iAxisMoveY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tRenInfo.fCX,
		m_tFrame.iScene * (int)m_tRenInfo.fCY,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CFireMonster::Release()
{
}

void CFireMonster::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}

void CFireMonster::IsJumping()
{
	float fMoveY = m_tInfo.fY;

	if (m_bIsJump)
	{
		m_tInfo.fY -= m_fJumpPow*m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		if (m_fJumpPow*m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f > 0) {
			m_tFrame.iScene = 0;
		}
		else {
			m_tFrame.iScene = 1;
		}
		m_fJumpAcc += 0.035f;
	}
}