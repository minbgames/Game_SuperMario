#include "stdafx.h"
#include "Leaf.h"


CLeaf::CLeaf()
{
	m_eLayer = LayerID::ITEM;
}


CLeaf::~CLeaf()
{
}

void CLeaf::Initialize()
{
	m_bIsJump = false;
	m_bIsFall = false;
	m_fJumpPow = 20.f;
	m_iState = 1;
	m_fParabolaX = 0.f;
	m_fDir = 1.0f;
}

void CLeaf::LateInit()
{
	SetRangeValue(48, 48, 16, 16);
	m_hBrush = CreateSolidBrush(RGB(200, 200, 0));
	if (0 == m_iState)
		SetJumpInit(JUMP);
	else if(1== m_iState)
		SetJumpInit(FALL);
}

int CLeaf::Update()
{
	CObj::LateInit();

	if (m_bIsDead)
		return DEAD_OBJ;

	if (0 == m_iState) {
		isJumping();
	}
	else if (1 == m_iState) {
		isJumping();
	}

	return NO_EVENT;
}

void CLeaf::LateUpdate()
{
}

void CLeaf::Render(HDC hDC)
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
		48,
		0,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CLeaf::isJumping()
{
	float fMoveY = m_tInfo.fY;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.fX, &fMoveY, this);

	if (m_bIsJump)
	{
		m_tInfo.fY -= m_fJumpPow * m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
	
		m_fJumpAcc += 0.5f;
		if (m_fJumpPow * m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f < 0) {
			SetJumpInit(FALL);
			m_fParabolaAxisX = m_tInfo.fX;
		}
	}
	else if (m_bIsFall)
	{
		m_fJumpAcc = 0.5f;
		m_tInfo.fY += GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f - m_fParabolaX * m_fParabolaX * 0.00013f;
		m_tInfo.fX = m_fParabolaAxisX + m_fParabolaX;
		
		float temp;
		if (m_fParabolaX >= 0) {
			temp = (100.f - m_fParabolaX) / 30.f;
			if (temp < 1.f) temp = 1.f;
			if (m_fDir >= 0) {
				m_fParabolaX += temp;
			}
			else {
				m_fParabolaX -= temp;
			}
		}
		else{
			temp = (-100.f - m_fParabolaX) / 30.f;
			if (temp > -1.f) temp = -1.f;

			if (m_fDir >= 0) {
				m_fParabolaX -= temp;
			}
			else {
				m_fParabolaX += temp;
			}
		}
		//m_fParabolaX += 1.f * m_fDir;


		if (m_fParabolaX > 100) m_fDir = -1.f;
		if (m_fParabolaX < -100) m_fDir = 1.f;

		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f && m_tInfo.fY >1150)
		{
			SetJumpInit(GROUND);
		}
	}
	else if (bColl)
		m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;
}

void CLeaf::SetJumpInit(MODE _mode)
{
	if (JUMP == _mode) {
		m_bIsJump = true;
		m_bIsFall = false;
		m_fJumpAcc = 1.f;
	}
	else if (FALL == _mode) {
		m_bIsJump = false;
		m_bIsFall = true;
		m_fJumpAcc = 0.f;
	}
	else if (GROUND == _mode) {
		m_bIsJump = false;
		m_bIsFall = false;
	}
}

void CLeaf::Release()
{
}

void CLeaf::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	m_bIsDead = true;
}
