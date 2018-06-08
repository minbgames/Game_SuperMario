#pragma once

class CObstacle;
class CObstacleMgr
{
	DECLARE_SINGLETON(CObstacleMgr)

private:
	CObstacleMgr();
	~CObstacleMgr();

public:
	enum SCENE { STAGE, UNDERSTAGE, FINALSTAGE };

public:
	void Initialize();
	void Render(HDC hDC);
	void Release();

public:
	void ObstacleCollision(OBJLIST& _srcLst);
	void SetScene(SCENE _scene) { m_eScene = _scene; }

private:
	bool CheckRect(CObj * pSrc, CObstacle * pDst, float* pMoveX, float* pMoveY);
	void LoadData();

private:
	list<CObstacle*>		m_ObstacleLst;
	SCENE			m_eScene;

};

