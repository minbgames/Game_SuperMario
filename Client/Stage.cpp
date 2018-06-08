#include "stdafx.h"
#include "Stage.h"
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

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	m_eMode = END_MODE;

	m_hBrush = CreateSolidBrush(RGB(0, 0, 0));

	CObj* pObj = CAbstractFactory<CPlayer>::CreateObj();
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::PLAYER);
	CPanelMgr::GetInstance()->SetPlayer(pObj);
	CPanelMgr::GetInstance()->SetStageNumber(1);

	for (int i = 0; i < 12; i++)
	{
		pObj = CAbstractFactory<CCoin>::CreateObj(4540.f+48.f*i, 447.f);
		CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::COIN);
	}

	pObj = CAbstractFactory<CFinalItem>::CreateObj(8087.f, 1031.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::FINAL_ITEM);

	pObj = CAbstractFactory<CNoteBox>::CreateObj(4118.f, 836.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::NOTE_BOX);


	pObj = CAbstractFactory<CQuestionBox>::CreateObj(2000.f, 1176.f);
	dynamic_cast<CQuestionBox*>(pObj)->SetItemID(ItemID::FLOWER);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::QUESTION_BOX);

	pObj = CAbstractFactory<CQuestionBox>::CreateObj(3091.f, 1030.f);
	dynamic_cast<CQuestionBox*>(pObj)->SetItemID(ItemID::LEAF);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::QUESTION_BOX);

	for (int i = 0; i < 4; i++)
	{
		if (0 == i) {
			pObj = CAbstractFactory<CQuestionBox>::CreateObj(294.f + 48.f*i, 1083.f);
			dynamic_cast<CQuestionBox*>(pObj)->SetItemID(ItemID::MUSHROOM);
			CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::QUESTION_BOX);
		}
		else {
			pObj = CAbstractFactory<CQuestionBox>::CreateObj(294.f+48.f*i, 1083.f);
			dynamic_cast<CQuestionBox*>(pObj)->SetItemID(ItemID::COIN);
			CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::QUESTION_BOX);
		}
	}

	pObj = CAbstractFactory<CGumbaMonster>::CreateObj(673.f, 1076.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::GUMBA_MONSTER);

	pObj = CAbstractFactory<CFlowerMonster>::CreateObj(1105.f, 1154.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::FLOWER_MONSTER);

	pObj = CAbstractFactory<CFlowerMonster>::CreateObj(5427.f, 1202.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::FLOWER_MONSTER);

	pObj = CAbstractFactory<CTurtleMonster>::CreateObj(773.f,1076.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TURTLE_MONSTER);

	pObj = CAbstractFactory<CTurtleMonster>::CreateObj(1695.f,1107.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TURTLE_MONSTER);

	pObj = CAbstractFactory<CTurtleMonster>::CreateObj(3944.f, 1124.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TURTLE_MONSTER);

	pObj = CAbstractFactory<CTurtleMonster>::CreateObj(4042.f, 1022.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TURTLE_MONSTER);

	pObj = CAbstractFactory<CTurtleMonster>::CreateObj(4143.f, 890.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TURTLE_MONSTER);
	
	pObj = CAbstractFactory<CTurtleMonster>::CreateObj(6510.f, 1045.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TURTLE_MONSTER);

	pObj = CAbstractFactory<CDoor>::CreateObj(5617.f, 1085.f);
	pObj->SetSize(80.f, 30.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::DOOR);

	CScrollMgr::GetInstance()->SetMaxSizeX(MAINSTAGE_REAL_X);
	CScrollMgr::GetInstance()->SetMaxSizeY(MAINSTAGE_REAL_Y);

	CLineMgr::GetInstance()->SetScene(CLineMgr::STAGE);
	CLineMgr::GetInstance()->Initialize();
	CObstacleMgr::GetInstance()->SetScene(CObstacleMgr::STAGE);
	CObstacleMgr::GetInstance()->Initialize();
	CPanelMgr::GetInstance()->Initialize();
	CSoundMgr::GetInstance()->PlayBGM(L"3-09-overworld-1.mp3");

}

void CStage::Update()
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

void CStage::LateUpdate()
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

void CStage::Render(HDC hDC)
{
	int iScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int iScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());
	
	HDC hMemDC = nullptr;
	HDC hSceneMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"MainStage"));
	CHECK_NULL(hSceneMemDC = CBmpMgr::GetInstance()->FindImage(L"SceneChange"));


	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY,
	hMemDC, -iScrollX/3, -iScrollY / 3,
		WINCX/3, WINCY/3, RGB(0, 255, 0));

	CObjectMgr::GetInstance()->Render(hDC);
	CLineMgr::GetInstance()->Render(hDC);
	CObstacleMgr::GetInstance()->Render(hDC);

	if (1== IsShowPanel) {
		BitBlt(hDC, 0, 0, WINCX, WINCY- UI_MARGIN_Y, hDC, 0, UI_MARGIN_Y, SRCCOPY);
		CPanelMgr::GetInstance()->Render(hDC);

		GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY,
			hSceneMemDC, 0, WINCY*m_iAnimNumber,
			WINCX, WINCY, RGB(51, 200, 150));
	}
}

void CStage::Release()
{
	CObjectMgr::GetInstance()->Release();

	CLineMgr::GetInstance()->Release();
	CObstacleMgr::GetInstance()->Release();
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::BGM);
}
