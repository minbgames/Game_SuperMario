#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(const LINEINFO & rInfo)
	: m_tInfo(rInfo)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	MoveToEx(hDC, static_cast<int>(m_tInfo.tLPoint.fX + fScrollX), static_cast<int>(m_tInfo.tLPoint.fY+ fScrollY), nullptr);
	LineTo(hDC, static_cast<int>(m_tInfo.tRPoint.fX + fScrollX), static_cast<int>(m_tInfo.tRPoint.fY + fScrollY));
}
