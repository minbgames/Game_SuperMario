#pragma once
#include "Scene.h"
class CUnderStageScene :public CScene
{
public:
	CUnderStageScene();
	virtual ~CUnderStageScene();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

