#include "stdafx.h"
#include "Obstacle.h"


CObstacle::CObstacle()
	:m_tInfo({}), m_tRect({})
{
}

CObstacle::CObstacle(int _left, int _top, int _right, int _bottom)
{
	m_tRect.left = _left;
	m_tRect.top = _top;
	m_tRect.right = _right;
	m_tRect.bottom = _bottom;

	m_tInfo.fCX = _right - _left;
	m_tInfo.fCY = _bottom - _top;
	m_tInfo.fX = _left + m_tInfo.fCX / 2.f;
	m_tInfo.fY = _top + m_tInfo.fCY / 2.f;
}

CObstacle::~CObstacle()
{
}

void CObstacle::Render(HDC hDC)
{
	int iScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int iScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	Rectangle(hDC, m_tRect.left+ iScrollX, m_tRect.top+ iScrollY, m_tRect.right+ iScrollX, m_tRect.bottom+ iScrollY);
}
