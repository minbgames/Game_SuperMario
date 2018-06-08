#include "stdafx.h"
#include "FinalMsg.h"


CFinalMsg::CFinalMsg()
{
}


CFinalMsg::~CFinalMsg()
{
}

void CFinalMsg::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}

void CFinalMsg::Initialize()
{

	SetRangeValue(157*3, 54*3, 157, 54);
	FrameChange(0, 0, 0, 100);
	m_hBrush = CreateSolidBrush(RGB(0, 100, 100));
	m_dwTime = GetTickCount();
}

void CFinalMsg::LateInit()
{
}

int CFinalMsg::Update()
{
	if (m_dwTime + 1500 < GetTickCount() && 0 == m_iAnimState) {
		m_iAnimState = 1;
		m_dwTime = GetTickCount();
	}

	return NO_EVENT;
}

void CFinalMsg::LateUpdate()
{

}

void CFinalMsg::Render(HDC hDC)
{
	CObj::UpdateRect();
	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"FinalMessage"));


	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		0,
		54* m_iAnimState,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CFinalMsg::Release()
{
}
