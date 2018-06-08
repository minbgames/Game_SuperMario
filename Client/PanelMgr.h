#pragma once
#include "Obj.h"
class CPanelMgr
{
	DECLARE_SINGLETON(CPanelMgr)

private:
	CPanelMgr();
	~CPanelMgr();

public:
	void SetStageNumber(int _iNumber) { m_iStageNumber = _iNumber; }
	void SetPlayer(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

public:
	void Initialize();
	void Update();
	void Render(HDC hDC);
	void Release();

private:
	void CalculateTimer();

private:
	int m_iStageNumber;
	int m_iTimer;
	int m_iTimerNumber[3];
	int m_iSpeedLevel;
	CObj* m_pPlayer;
	HBRUSH	m_hBrush;
	HBRUSH	m_hPrev;
	DWORD m_dwTime;
};

