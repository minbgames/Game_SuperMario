#include "stdafx.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CScrollMgr)

CScrollMgr::CScrollMgr()
	: m_tInfo({}), m_tRect({})
{
	m_bShakeOn = false;
	m_iMinSizeX = 0.f;
	m_iMinSizeY = 0.f;
	m_fDir = -1.0f;
	m_fShakeLimit = -15.f;
	m_fMarginX = 0.f;
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::SetScrollX(float x)
{
	if (m_bShakeOn) return;

	if (x < m_iMinSizeX + WINCX / 2)
		m_tInfo.fCX = m_iMinSizeX + WINCX / 2;
	else if (x > m_iMaxSizeX - WINCX / 2)
		m_tInfo.fCX = m_iMaxSizeX - WINCX / 2;
	else
		m_tInfo.fCX = x;
}

void CScrollMgr::SetScrollY(float y)
{
	if (y - MARGIN_Y< WINCY / 2)
		m_tInfo.fCY = WINCY / 2;
	else if (y - MARGIN_Y> m_iMaxSizeY - WINCY / 2)
		m_tInfo.fCY = m_iMaxSizeY - WINCY / 2;
	else
		m_tInfo.fCY = y - MARGIN_Y;
}

void CScrollMgr::ShakeOn()
{
	m_fShakeX = m_tInfo.fCX;
	m_fShakeY = m_tInfo.fCY;
	m_bShakeOn = true;
	m_fDir = -1.0f;
	m_fShakeLimit = -15.f;
	m_fMarginX = 0.f;
	m_bArrive = false;
}

void CScrollMgr::Shaking()
{
	if (m_bShakeOn) {
			//-30 ~ 0 
			if (m_fMarginX <= m_fShakeLimit && m_bArrive) {
				m_fDir = 1.0f;
				m_fShakeLimit += 2.5f;
				m_bArrive = false;
			}
			else if(m_fMarginX >=0){
				m_bArrive = true;
				m_fDir = -1.0f;
			}
			m_fMarginX += 4*m_fDir;
			m_tInfo.fCX = m_fShakeX + m_fMarginX;

			if (m_fShakeLimit >= 0.f)
				m_bShakeOn = false;
	}

}

