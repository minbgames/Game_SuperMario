#pragma once
#include "Scene.h"
class CMapScene :
	public CScene
{
public:
	CMapScene();
	virtual ~CMapScene();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	CObj* m_pMapPlayer;
	CSceneMgr::SCENE m_eScene;
};

