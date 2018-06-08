#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	enum MODE { ENTER_MODE, EXIT_MODE, END_MODE};

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

protected:
	void Animation(MODE _mode);

protected:
	HBRUSH	m_hBrush;
	HBRUSH	m_hPrev;
	MODE m_eMode;
	bool m_bAnimOn;
	bool m_bSceneInit;
	int m_iAnimNumber;
	DWORD m_dwTime;
};

