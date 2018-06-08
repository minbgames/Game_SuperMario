#pragma once
#include "Scene.h"
class CFinalStageScene :
	public CScene
{
public:
	CFinalStageScene();
	virtual ~CFinalStageScene();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	bool m_bFinalBossOn;
};

