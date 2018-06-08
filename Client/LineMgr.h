#pragma once

class CLine;
class CLineMgr
{
	DECLARE_SINGLETON(CLineMgr)

private:
	CLineMgr();
	~CLineMgr();

public:
	enum SCENE { STAGE, UNDERSTAGE, FINALSTAGE };

public:
	void Initialize();
	void Render(HDC hDC);
	void Release();

public:
	bool LineCollision(float fInX, float* pOutY, CObj* _pObj);
	void AddLine(int _leftX, int _leftY, int _rightX, int _rightY);
	void SetScene(SCENE _scene) { m_eScene = _scene; }

private:
	void LoadData();

private:
	list<CLine*>		m_LineLst;
	SCENE			m_eScene;
};

