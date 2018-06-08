#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_bIsInit(false), m_bIsDead(false), m_bColOpt(true), m_fSpeed(0.f), m_eLayer(LayerID::GAMEOBJECT), m_fMultiple(1.f), m_tFrame({}), m_iAnimState(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tStat, sizeof(STAT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}

void CObj::LateInit()
{
	if (!m_bIsInit)
		this->LateInit();

	m_bIsInit = true;
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY/ 2);
}

void CObj::FrameChange(int _startX, int _endX, int _lineY, int _time)
{
	m_iAnimInit = _startX;
	m_tFrame.iFrameStart = _startX;
	m_tFrame.iFrameEnd = _endX;
	m_tFrame.iScene = _lineY;
	m_tFrame.dwFrameSpd = _time;
	m_tFrame.dwFrameOld = GetTickCount();
}

void CObj::SetAdjustValue(int _axisX, int _axisY, int _marginX, int _marginY)
{
	m_tAdjust.iAxisMoveX = _axisX;
	m_tAdjust.iAxisMoveY = _axisY;
	m_tAdjust.iMarginX = _marginX;
	m_tAdjust.iMarginY = _marginY;
}

void CObj::SetRangeValue(int _cx, int _cy, int _rencx, int _rency)
{
	m_tInfo.fCX = _cx;
	m_tInfo.fCY = _cy;
	m_tRenInfo.fCX = _rencx;
	m_tRenInfo.fCY = _rency;

}

void CObj::Animation()
{
	if (bTimePause) return;

	if (m_tFrame.dwFrameOld + m_tFrame.dwFrameSpd < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameOld = GetTickCount();
	}

	if (m_bAnimOnce) {
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd) {
			m_tFrame.iFrameStart = m_iAnimInit;
			m_bAnimOnce = false;
		}
	}
	else {
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = m_iAnimInit;
	}

}
