#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"

#include "Logo.h"
#include "MapScene.h"
#include "Stage.h"
#include "UnderStageScene.h"
#include "FinalStageScene.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(END), m_ePreScene(END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SCENE eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		SafeDelete(m_pScene);

		switch (m_eCurScene)
		{
		case LOGO:
			m_pScene = new CLogo;
			break;
		case MAP:
			m_pScene = new CMapScene;
			break;
		case STAGE:
			m_pScene = new CStage;
			break;
		case UNDERSTAGE:
			m_pScene = new CUnderStageScene;
			break;
		case FINALSTAGE:
			m_pScene = new CFinalStageScene;
			break;
		}

		CScrollMgr::GetInstance()->SetMinSizeX(0);
		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
}
