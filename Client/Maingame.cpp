#include "stdafx.h"
#include "Maingame.h"


CMaingame::CMaingame()
{
	IsShowCollider = 0;
	IsShowObstacle = 0;
	IsShowPanel = 1;
	IsShowCursur = 0;
	IsPlayerNotDead = 0;
	IsBossTriger = 0;
}


CMaingame::~CMaingame()
{
	Release();
}

void CMaingame::Initialize()
{
	m_hDC = GetDC(g_hWnd);	


	CBmpMgr::GetInstance()->InsertBmp(L"Back", L"../FinalImage/Back.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"BackBuffer", L"../FinalImage/BackBuffer.bmp");
	//Buffer

	CBmpMgr::GetInstance()->InsertBmp(L"UIBlankPanel", L"../FinalImage/UIBlankPanel.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"UIFillPanel", L"../FinalImage/UIFillPanel.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"UIMapPanel", L"../FinalImage/UIMapPanel.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"UINumber", L"../FinalImage/UINumber.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"UISpeedPanel", L"../FinalImage/UISpeedPanel.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"SceneChange", L"../FinalImage/SceneChange.bmp");
	//UI
	
	CBmpMgr::GetInstance()->InsertBmp(L"BigMarioRight", L"../FinalImage/BigMarioRight.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"BigMarioLeft", L"../FinalImage/BigMarioLeft.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"FireMarioRight", L"../FinalImage/FireMarioRight.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"FireMarioLeft", L"../FinalImage/FireMarioLeft.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"RacoonDogMarioRight", L"../FinalImage/RacoonDogMarioRight.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"RacoonDogMarioLeft", L"../FinalImage/RacoonDogMarioLeft.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"SmallMarioRight", L"../FinalImage/SmallMarioRight.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"SmallMarioLeft", L"../FinalImage/SmallMarioLeft.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"MarioDead", L"../FinalImage/MarioDead.bmp");
	//Mario

	CBmpMgr::GetInstance()->InsertBmp(L"FireBall", L"../FinalImage/FireBall.bmp");
	//Bullet

	CBmpMgr::GetInstance()->InsertBmp(L"NormalTurtleLeft", L"../FinalImage/NormalTurtleLeft.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"NormalTurtleRight", L"../FinalImage/NormalTurtleRight.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"FlowerLeft", L"../FinalImage/FlowerLeft.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"FlowerRight", L"../FinalImage/FlowerRight.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"NormalMushroom", L"../FinalImage/NormalMushroom.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"CircleMonster", L"../FinalImage/CircleMonster.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"FireMonster", L"../FinalImage/FireMonster.bmp");
	// Monster

	CBmpMgr::GetInstance()->InsertBmp(L"Boss", L"../FinalImage/Boss.bmp");
	// Boss

	CBmpMgr::GetInstance()->InsertBmp(L"Item", L"../FinalImage/Item.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"Blocks", L"../FinalImage/Blocks.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"effects", L"../FinalImage/effects.bmp");
	// Components

	CBmpMgr::GetInstance()->InsertBmp(L"TitleScreenNumber", L"../FinalImage/TitleScreenNumber.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"TitlePlayerSelect", L"../FinalImage/TitlePlayerSelect.bmp");
	// Menu

	CBmpMgr::GetInstance()->InsertBmp(L"MapPlayer", L"../FinalImage/MapPlayer.bmp");
	// Map

	CBmpMgr::GetInstance()->InsertBmp(L"FinalItem", L"../FinalImage/FinalItem.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"FinalMessage", L"../FinalImage/FinalMessage.bmp");
	// Final

	CBmpMgr::GetInstance()->InsertBmp(L"MainStage", L"../Image2/MainStage.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"TitleScene", L"../Image2/TitleScene.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"MapScene", L"../FinalImage/MapScene.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"FinalStage", L"../FinalImage/FinalStage.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"UnderStage", L"../FinalImage/UnderStage.bmp");

	CSoundMgr::GetInstance()->Initialize();
	CSceneMgr::GetInstance()->SceneChange(CSceneMgr::LOGO);
	m_ePreScene = CSceneMgr::LOGO;
}

void CMaingame::Update()
{
	if (KEY_DOWN(VK_F9)) {
		if (1 == IsShowCollider)
			IsShowCollider = 0;
		else
			IsShowCollider = 1;
	}

	if (KEY_DOWN(VK_F8)) {
		if (1 == IsShowObstacle)
			IsShowObstacle = 0;
		else
			IsShowObstacle = 1;
	}

	if (KEY_DOWN(VK_F7)) {
		if (1 == IsShowObstacle)
			IsShowObstacle = 0;
		else
			IsShowObstacle = 1;
	}

	if (KEY_DOWN(VK_F6)) {
		if (1 == IsShowPanel)
			IsShowPanel = 0;
		else
			IsShowPanel = 1;
	}

	if (KEY_DOWN(VK_F5)) {
		if (1 == IsShowCursur)
			IsShowCursur = 0;
		else
			IsShowCursur = 1;
	}

	if (KEY_DOWN(VK_F4)) {
		if (1 == IsPlayerNotDead) {
			IsPlayerNotDead = 0;
			cout << "公利 Off" << endl;
		}
		else {
			IsPlayerNotDead = 1;
			cout << "公利 On" << endl;
		}
	}
	CSceneMgr::GetInstance()->Update();
}

void CMaingame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
	CSoundMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
}

void CMaingame::Render()
{
	if (m_ePreScene != CSceneMgr::GetInstance()->GetCurScene())
	{
		m_ePreScene = CSceneMgr::GetInstance()->GetCurScene();
		return;
	}
	HDC hBackBuffer = nullptr;
	CHECK_NULL(hBackBuffer = CBmpMgr::GetInstance()->FindImage(L"BackBuffer"));

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"Back"));
	BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CSceneMgr::GetInstance()->Render(hBackBuffer);

	if (1 == IsShowCursur) {
		int iScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
		int iScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		TCHAR szBuf[50] = L"";
		swprintf_s(szBuf, L"x: %ld y: %ld", pt.x - iScrollX, pt.y - iScrollY);
		TextOut(hBackBuffer, 50, 50, szBuf, lstrlen(szBuf));
	}

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMaingame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);	

	CSceneMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CScrollMgr::GetInstance()->DestroyInstance();
	CBmpMgr::GetInstance()->DestroyInstance();
	CObstacleMgr::GetInstance()->DestroyInstance();
	CLineMgr::GetInstance()->DestroyInstance();
	CObjectMgr::GetInstance()->DestroyInstance();	
	CPathMgr::GetInstance()->DestroyInstance();
	CPanelMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();	
}
