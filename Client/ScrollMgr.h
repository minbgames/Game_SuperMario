#pragma once
class CScrollMgr
{
	DECLARE_SINGLETON(CScrollMgr)

private:
	CScrollMgr();
	~CScrollMgr();

public:
	float GetScrollX() { return WINCX / 2 - m_tInfo.fCX; }
	float GetScrollY() { return WINCY / 2 - m_tInfo.fCY; }

public:
	void SetScrollX(float x);
	void SetScrollY(float y);
	void SetMaxSizeX(int x) { m_iMaxSizeX = x; }
	void SetMaxSizeY(int y) { m_iMaxSizeY = y; }
	void SetMinSizeX(int x) { m_iMinSizeX = x; }
	void SetMinSizeY(int y) { m_iMinSizeY = y; }

public:
	void ShakeOn();
	void Shaking();

private:
	INFO m_tInfo;
	RECT m_tRect;
	int m_iMaxSizeX;
	int m_iMaxSizeY;
	int m_iMinSizeX;
	int m_iMinSizeY;
	
	bool m_bShakeOn;
	float m_fShakeX;
	float m_fShakeY;
	float m_fDir;

	DWORD m_dwTime;
	float m_fShakeLimit;
	float m_fMarginX;
	bool m_bArrive;
};

