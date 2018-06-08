#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENE { LOGO, MAP, STAGE, UNDERSTAGE, FINALSTAGE, END };

private:
	CSceneMgr();
	~CSceneMgr();

public:
	SCENE GetCurScene() { return m_eCurScene; }

public:
	void SceneChange(SCENE eID);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

private:
	CScene*	m_pScene;
	SCENE	m_eCurScene;
	SCENE	m_ePreScene;
};

