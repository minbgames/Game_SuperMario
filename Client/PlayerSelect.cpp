#include "stdafx.h"
#include "PlayerSelect.h"


CPlayerSelect::CPlayerSelect()
{
}


CPlayerSelect::~CPlayerSelect()
{
}


void CPlayerSelect::Initialize()
{
	m_iState = 0;
}

void CPlayerSelect::LateInit()
{
	m_hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SetRangeValue(360, 150, 360, 150);
}

int CPlayerSelect::Update()
{
	CObj::LateInit();

	if (KEY_DOWN(VK_DOWN)) {
		if (0 == m_iState) {
			m_iState = 1;
		}
	}

	if (KEY_DOWN(VK_UP)) {
		if (1 == m_iState) {
			m_iState = 0;
		}
	}

	return NO_EVENT;
}

void CPlayerSelect::LateUpdate()
{
}

void CPlayerSelect::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"TitlePlayerSelect"));


	if (1==IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - m_tRenInfo.fCX / 2,
		m_tInfo.fY - m_tRenInfo.fCY / 2,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY,
		hMemDC,
		20+356* m_iState,
		0,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CPlayerSelect::Release()
{
}

void CPlayerSelect::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}
