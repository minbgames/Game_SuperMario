#include "stdafx.h"
#include "ScreenNumber.h"


CScreenNumber::CScreenNumber()
{
}


CScreenNumber::~CScreenNumber()
{
}


void CScreenNumber::Initialize()
{
}

void CScreenNumber::LateInit()
{
	m_hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SetRangeValue(136, 136, 136, 136);
	FrameChange(0, 3, 0, 500);
}

int CScreenNumber::Update()
{
	CObj::LateInit();
	return NO_EVENT;
}

void CScreenNumber::LateUpdate()
{
	CObj::Animation();
}

void CScreenNumber::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"TitleScreenNumber"));


	if (1==IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - m_tRenInfo.fCX / 2,
		m_tInfo.fY - m_tRenInfo.fCY / 2,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY,
		hMemDC,
		136 * m_tFrame.iFrameStart,
		0,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CScreenNumber::Release()
{
}

void CScreenNumber::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}
