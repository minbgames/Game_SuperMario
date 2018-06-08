#include "stdafx.h"
#include "MapScene.h"
#include "MapPlayer.h"

CMapScene::CMapScene()
{
}

CMapScene::~CMapScene()
{
	Release();
}

void CMapScene::Initialize()
{
	m_eMode = END_MODE;
	CScrollMgr::GetInstance()->SetScrollX(0.f);
	CScrollMgr::GetInstance()->SetScrollY(0.f);
	CPathMgr::GetInstance()->Initialize();

	CObj* pObj = CAbstractFactory<CMapPlayer>::CreateObj(136.f,155.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::MAP_PLAYER);
	CSoundMgr::GetInstance()->PlayBGM(L"3-01-world-map-1-grass-land-.mp3");
	m_pMapPlayer = pObj;
}

void CMapScene::Update()
{
	if (!m_bAnimOn && m_eMode == EXIT_MODE) {
		CSceneMgr::GetInstance()->SceneChange(m_eScene);
		return;
	}

	if (m_bAnimOn) {
		return;
	}

	if (KEY_DOWN(VK_RETURN))
	{
		if (m_pMapPlayer->GetInfo().fX == 243.f && m_pMapPlayer->GetInfo().fY == 60.f) {
			m_eMode = EXIT_MODE;
			m_bAnimOn = true;
			m_eScene = CSceneMgr::STAGE;
			CSoundMgr::GetInstance()->PlaySound(L"Stage Selected SFX.wav", CSoundMgr::EFFECT);
			return;
		}
		else if (m_pMapPlayer->GetInfo().fX == 615.f && m_pMapPlayer->GetInfo().fY == 349.f) {
			m_eMode = EXIT_MODE;
			m_bAnimOn = true;
			m_eScene = CSceneMgr::FINALSTAGE;
			CSoundMgr::GetInstance()->PlaySound(L"Stage Selected SFX.wav", CSoundMgr::EFFECT);
			return;
		}
		else if (m_pMapPlayer->GetInfo().fX == 626.f && m_pMapPlayer->GetInfo().fY == 158.f) {
			m_eMode = EXIT_MODE;
			m_bAnimOn = true;
			m_eScene = CSceneMgr::UNDERSTAGE;
			CSoundMgr::GetInstance()->PlaySound(L"Stage Selected SFX.wav", CSoundMgr::EFFECT);
			return;
		}
		else {
			CSoundMgr::GetInstance()->PlaySound(L"Bump V1 SFX.wav", CSoundMgr::EFFECT);
		}
	}
	CObjectMgr::GetInstance()->Update();
}

void CMapScene::LateUpdate()
{
	if(m_bAnimOn){
		CScene::Animation(m_eMode);
		return;
	}
	CObjectMgr::GetInstance()->LateUpdate();

	if (m_bSceneInit) {
		m_bAnimOn = true;
		m_bSceneInit = false;
		m_eMode = ENTER_MODE;
	}
}

void CMapScene::Render(HDC hDC)
{
	HDC hMemDC = nullptr;
	HDC hUIMemDC = nullptr;
	HDC hSceneMemDC = nullptr;

	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"MapScene"));
	CHECK_NULL(hUIMemDC = CBmpMgr::GetInstance()->FindImage(L"UIMapPanel"));
	CHECK_NULL(hSceneMemDC = CBmpMgr::GetInstance()->FindImage(L"SceneChange"));

	GdiTransparentBlt(hDC, (WINCX - 234 * 3) / 2, 10, 234 * 3, 162*3,
		hMemDC, 0, 0,
		234, 162, RGB(51, 200, 150));

	GdiTransparentBlt(hDC, (WINCX - 232 * 3)/2, WINCY- 28 * 3 - 10, 232*3, 28*3,
		hUIMemDC, 3, 3,
		232, 28, RGB(51, 200, 150));

	CPathMgr::GetInstance()->Render(hDC);
	CObjectMgr::GetInstance()->Render(hDC);

	GdiTransparentBlt(hDC, 0,0, WINCX, WINCY,
		hSceneMemDC, 0, WINCY*m_iAnimNumber,
		WINCX, WINCY, RGB(51, 200, 150));
}

void CMapScene::Release()
{
	CPathMgr::GetInstance()->Release();
	CObjectMgr::GetInstance()->Release();
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::BGM);
}
