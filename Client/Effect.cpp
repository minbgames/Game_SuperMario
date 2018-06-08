#include "stdafx.h"
#include "Effect.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}


void CEffect::Initialize()
{
	m_hBrush = CreateSolidBrush(RGB(0, 200, 200));
	SetRangeValue(16, 16, 16, 16);
	m_dwTime = GetTickCount();
}

void CEffect::LateInit()
{
}

int CEffect::Update()
{
	if (m_dwTime + 250 < GetTickCount() ) return DEAD_OBJ;
	return NO_EVENT;
}

void CEffect::LateUpdate()
{
}

void CEffect::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"effects"));

	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - m_tRenInfo.fCX / 2 + fScrollX,
		m_tInfo.fY - m_tRenInfo.fCY / 2 + fScrollY,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY,
		hMemDC,
		51,
		26,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CEffect::Release()
{
}

void CEffect::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}
