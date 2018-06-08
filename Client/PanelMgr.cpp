#include "stdafx.h"
#include "PanelMgr.h"

IMPLEMENT_SINGLETON(CPanelMgr)

CPanelMgr::CPanelMgr()
{
}

CPanelMgr::~CPanelMgr()
{
	Release();
}

void CPanelMgr::Initialize()
{
	m_hBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_iSpeedLevel = 0;
	m_dwTime = GetTickCount();
	m_iTimer = 300;
	CalculateTimer();
}

void CPanelMgr::Update()
{
	if (m_pPlayer->GetSpeed() == 0.f) {
		m_iSpeedLevel = 0;
	}
	else if (m_pPlayer->GetSpeed() == 8.f) {
		m_iSpeedLevel = 8;
	}
	else {
		m_iSpeedLevel = (int)m_pPlayer->GetSpeed() + 1;
	}

	if (m_dwTime + 1000 < GetTickCount()) {
		--m_iTimer;
		if (m_iTimer < 0) m_iTimer = 0;
		CalculateTimer();
		m_dwTime = GetTickCount();
	}
}

void CPanelMgr::Render(HDC hDC)
{
	HDC hMemDC = nullptr;
	
	// === UI Part
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"UIFillPanel"));

	m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
	Rectangle(hDC, 0, 496, 800, 600);
	SelectObject(hDC, m_hPrev);
	
	GdiTransparentBlt(hDC, (WINCX - 232 * 3) / 2, WINCY - 28 * 3 - 10, 232 * 3, 28 * 3,
		hMemDC, 3, 3,
		232, 28, RGB(51, 200, 150));

	// === Speed Part
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"UISpeedPanel"));
	GdiTransparentBlt(hDC, (WINCX - 232 * 3) / 2, WINCY - 28 * 3 - 10, 232 * 3, 28 * 3,
		hMemDC, 3, 3 + 31 * m_iSpeedLevel,
		232, 28, RGB(51, 200, 150));

	// === Number Part
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"UINumber"));

	// # Stage
	GdiTransparentBlt(hDC, 163, 527, 24, 21,
		hMemDC, 10 * m_iStageNumber, 0,
		8, 7, RGB(51, 200, 150));

	// # Timer
	GdiTransparentBlt(hDC, 424, 551, 24, 21,
		hMemDC, 10* m_iTimerNumber[0], 0,
		8, 7, RGB(51, 200, 150));
	GdiTransparentBlt(hDC, 424+24, 551, 24, 21,
		hMemDC, 10* m_iTimerNumber[1], 0,
		8, 7, RGB(51, 200, 150));
	GdiTransparentBlt(hDC, 424 + 48, 551, 24, 21,
		hMemDC, 10 * m_iTimerNumber[2], 0,
		8, 7, RGB(51, 200, 150));
}

void CPanelMgr::Release()
{
}

void CPanelMgr::CalculateTimer()
{
	m_iTimerNumber[0] = m_iTimer / 100;
	m_iTimerNumber[1] = (m_iTimer % 100) / 10;
	m_iTimerNumber[2] = m_iTimer % 10;
}
