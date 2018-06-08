#include "stdafx.h"
#include "Logo.h"
#include "ScreenNumber.h"
#include "PlayerSelect.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CSoundMgr::GetInstance()->PlayBGM(L"Intro.wav");

	CScrollMgr::GetInstance()->SetScrollX(0.f);
	CScrollMgr::GetInstance()->SetScrollY(0.f);

	CObj* pObj = CAbstractFactory<CScreenNumber>::CreateObj(420.f,310.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TITLE_NUMBER);

	pObj = CAbstractFactory<CPlayerSelect>::CreateObj(390.f, 417.f);
	CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TITLE_SELECT);


}

void CLogo::Update()
{
	if (KEY_DOWN(VK_RETURN))
	{
		CSoundMgr::GetInstance()->PlaySound(L"Coin Obtained SFX.wav", CSoundMgr::EFFECT);
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::MAP);
		return;
	}

	CObjectMgr::GetInstance()->Update();
}

void CLogo::LateUpdate()
{
	CObjectMgr::GetInstance()->LateUpdate();
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"TitleScene"));
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CObjectMgr::GetInstance()->Render(hDC);
}

void CLogo::Release()
{
	CObjectMgr::GetInstance()->Release();
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::BGM);
}
