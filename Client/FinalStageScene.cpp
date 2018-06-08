#include "stdafx.h"
#include "FinalStageScene.h"
#include "Player.h"
#include "TurtleMonster.h"
#include "QuestionBox.h"
#include "PanelMgr.h"
#include "Coin.h"
#include "FinalItem.h"
#include "CircleMonster.h"
#include "FireMonster.h"
#include "Door.h"
#include "Boss.h"

CFinalStageScene::CFinalStageScene()
{
}

CFinalStageScene::~CFinalStageScene()
{
	Release();
}

void CFinalStageScene::Initialize()
{
	m_eMode = END_MODE;

	m_hBrush = CreateSolidBrush(RGB(0, 0, 0));

	CScrollMgr::GetInstance()->SetMaxSizeX(FINALSTAGE_REAL_X);
	CScrollMgr::GetInstance()->SetMaxSizeY(FINALSTAGE_REAL_Y);

	CObj* pObj = CAbstractFactory<CPlayer>::CreateObj();
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::PLAYER);
	CPanelMgr::GetInstance()->SetPlayer(pObj);
	CPanelMgr::GetInstance()->SetStageNumber(2);


	pObj = CAbstractFactory<CQuestionBox>::CreateObj(1756.f, 992.f);
	dynamic_cast<CQuestionBox*>(pObj)->SetItemID(ItemID::FLOWER);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::QUESTION_BOX);

	pObj = CAbstractFactory<CQuestionBox>::CreateObj(4730, 1084);
	dynamic_cast<CQuestionBox*>(pObj)->SetItemID(ItemID::LEAF);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::QUESTION_BOX);

	pObj = CAbstractFactory<CFireMonster>::CreateObj(892.f, 1350.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::CIRCLE_MONSTER);

	pObj = CAbstractFactory<CFireMonster>::CreateObj(1515.f, 1350.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::CIRCLE_MONSTER);

	pObj = CAbstractFactory<CFireMonster>::CreateObj(3990.f, 1350.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::CIRCLE_MONSTER);

	pObj = CAbstractFactory<CFireMonster>::CreateObj(4548.f, 1350.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::CIRCLE_MONSTER);

	pObj = CAbstractFactory<CCircleMonster>::CreateObj();
	dynamic_cast<CCircleMonster*>(pObj)->SetCenterPos(2718.f, 1038.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::CIRCLE_MONSTER);

	pObj = CAbstractFactory<CCircleMonster>::CreateObj();
	dynamic_cast<CCircleMonster*>(pObj)->SetCenterPos(3436.f, 1082.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::CIRCLE_MONSTER);

	pObj = CAbstractFactory<CCircleMonster>::CreateObj();
	dynamic_cast<CCircleMonster*>(pObj)->SetCenterPos(4397.f, 1130.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::CIRCLE_MONSTER);

	pObj = CAbstractFactory<CTurtleMonster>::CreateObj(5058.f, 1171.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TURTLE_MONSTER);
	
	pObj = CAbstractFactory<CDoor>::CreateObj(5263.f, 1159.f);
	pObj->SetObjectState(10);
	pObj->SetSize(50.f, 100.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::DOOR);

	pObj = CAbstractFactory<CDoor>::CreateObj(5934.f, 1159.f);
	pObj->SetObjectState(11);
	pObj->SetSize(50.f, 100.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::DOOR);

	IsBossTriger = 0;

	pObj = CAbstractFactory<CBoss>::CreateObj(7482.f, 1080.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::BOSS);

	CLineMgr::GetInstance()->SetScene(CLineMgr::FINALSTAGE);
	CLineMgr::GetInstance()->Initialize();
	CObstacleMgr::GetInstance()->SetScene(CObstacleMgr::FINALSTAGE);
	CObstacleMgr::GetInstance()->Initialize();
	CPanelMgr::GetInstance()->Initialize();
	CSoundMgr::GetInstance()->PlayBGM(L"3-19-fortress.mp3");

	m_bFinalBossOn = false;
}

void CFinalStageScene::Update()
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
		CScrollMgr::GetInstance()->Shaking();
	}

	if (KEY_DOWN(VK_RETURN)) {
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::MAP);
		bTimePause = false;
	}

	if (KEY_DOWN(VK_SHIFT))
		bTimePause = !bTimePause;
}

void CFinalStageScene::LateUpdate()
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

void CFinalStageScene::Render(HDC hDC)
{
	int iScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int iScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());
	if (!m_bFinalBossOn) {
		if (iScrollX == -6886) {
			m_bFinalBossOn = true;
			CScrollMgr::GetInstance()->SetMinSizeX(6886);
			CSoundMgr::GetInstance()->StopAll();
			CSoundMgr::GetInstance()->PlayBGM(L"3-23-koopa-kid-battle.mp3");
			IsBossTriger = 1;
		}
	}
	HDC hMemDC = nullptr;
	HDC hSceneMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"FinalStage"));
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

void CFinalStageScene::Release()
{
	CObjectMgr::GetInstance()->Release();

	CLineMgr::GetInstance()->Release();
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::BGM);
	CObstacleMgr::GetInstance()->Release();

}
