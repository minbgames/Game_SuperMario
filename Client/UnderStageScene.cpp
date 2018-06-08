#include "stdafx.h"
#include "UnderStageScene.h"
#include "Player.h"
#include "TurtleMonster.h"
#include "QuestionBox.h"
#include "NoteBox.h"
#include "PanelMgr.h"
#include "Coin.h"
#include "FinalItem.h"
#include "GumbaMonster.h"
#include "FlowerMonster.h"
#include "Door.h"

CUnderStageScene::CUnderStageScene()
{
}

CUnderStageScene::~CUnderStageScene()
{
	Release();
}

void CUnderStageScene::Initialize()
{
	m_eMode = END_MODE;

	m_hBrush = CreateSolidBrush(RGB(0, 23, 0));

	CScrollMgr::GetInstance()->SetMaxSizeX(UNDERSTAGE_REAL_X);
	CScrollMgr::GetInstance()->SetMaxSizeY(UNDERSTAGE_REAL_Y);

	CObj* pObj = CAbstractFactory<CPlayer>::CreateObj(435.f,120.f+141.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::PLAYER);
	

	//for (int i = 0; i < 5; i++)
	//{
	//	pObj = CAbstractFactory<CCoin>::CreateObj(535.f+i*48.f, 400.f);
	//	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::COIN);
	//}
	pObj = CAbstractFactory<CCoin>::CreateObj(631.f-24.f, 400.f + 141.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::COIN);

	pObj = CAbstractFactory<CCoin>::CreateObj(631.f - 72.f, 400.f + 141.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::COIN);

	pObj = CAbstractFactory<CCoin>::CreateObj(631.f - 96.f, 352.f + 141.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::COIN);

	pObj = CAbstractFactory<CDoor>::CreateObj(1107.f, 120.f + 141.f);
	pObj->SetObjectState(9);
	pObj->SetSize(100.f, 30.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::DOOR);
	for (int i = 1; i < 5; i++)
	{
		pObj = CAbstractFactory<CCoin>::CreateObj(631.f, 400.f - i*48.f + 141.f);
		CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::COIN);
	}

	for (int i = 0; i < 5; i++)
	{
		pObj = CAbstractFactory<CCoin>::CreateObj(535.f + 48.f * i, 208.f + 141.f);
		CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::COIN);
	}
	CLineMgr::GetInstance()->SetScene(CLineMgr::UNDERSTAGE);
	CLineMgr::GetInstance()->Initialize();
	CObstacleMgr::GetInstance()->SetScene(CObstacleMgr::UNDERSTAGE);
	CObstacleMgr::GetInstance()->Initialize();
	CPanelMgr::GetInstance()->Initialize();
	CPanelMgr::GetInstance()->SetPlayer(pObj);
	CPanelMgr::GetInstance()->SetStageNumber(1);
	CSoundMgr::GetInstance()->PlayBGM(L"3-18-toad-s-house.mp3");
	CSoundMgr::GetInstance()->PlaySound(L"Pipe Maze SFX.wav", CSoundMgr::PLAYER);


}

void CUnderStageScene::Update()
{
	if (m_bAnimOn) {
		return;
	}

	if (bGoToMap) {
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::MAP);
		bTimePause = false;
		bGoToMap = false;
	}

	CObjectMgr::GetInstance()->Update();
	if (!bTimePause) {
		CPanelMgr::GetInstance()->Update();
	}

	if (KEY_DOWN(VK_RETURN)) {
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::MAP);
		bTimePause = false;
	}

	if (KEY_DOWN(VK_SHIFT))
		bTimePause = !bTimePause;
}

void CUnderStageScene::LateUpdate()
{
	if (m_bAnimOn) {
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

void CUnderStageScene::Render(HDC hDC)
{
	int iScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int iScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	HDC hSceneMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"UnderStage"));
	CHECK_NULL(hSceneMemDC = CBmpMgr::GetInstance()->FindImage(L"SceneChange"));

	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY,
		hMemDC, -iScrollX / 3, -iScrollY / 3,
		WINCX / 3, WINCY / 3, RGB(0, 255, 0));

	CObjectMgr::GetInstance()->Render(hDC);
	CLineMgr::GetInstance()->Render(hDC);
	CObstacleMgr::GetInstance()->Render(hDC);

	if (1== IsShowPanel) {
		BitBlt(hDC, 0, 0, WINCX, WINCY - UI_MARGIN_Y, hDC, 0, UI_MARGIN_Y, SRCCOPY);
		CPanelMgr::GetInstance()->Render(hDC);

		GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY,
			hSceneMemDC, 0, WINCY*m_iAnimNumber,
			WINCX, WINCY, RGB(51, 200, 150));
	}
}

void CUnderStageScene::Release()
{
	CObjectMgr::GetInstance()->Release();

	CLineMgr::GetInstance()->Release();
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::BGM);
	CObstacleMgr::GetInstance()->Release();

}
