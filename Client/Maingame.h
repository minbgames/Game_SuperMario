#pragma once

class CObj;
class CMaingame
{
public:
	CMaingame();
	~CMaingame();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	HDC					m_hDC;	
	CSceneMgr::SCENE	m_ePreScene;
};

