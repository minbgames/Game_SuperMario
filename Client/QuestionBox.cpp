#include "stdafx.h"
#include "QuestionBox.h"
#include "Flower.h"
#include "Leaf.h"
#include "Coin.h"
#include "Mushroom.h"

CQuestionBox::CQuestionBox()
{
}


CQuestionBox::~CQuestionBox()
{
}

void CQuestionBox::Initialize()
{
	m_hBrush = CreateSolidBrush(RGB(0, 200, 0));
	m_iState = 0;
}

void CQuestionBox::LateInit()
{
	SetRangeValue(48, 48, 16, 16);
	FrameChange(0, 3, 0, 200);
	CObj::UpdateRect();
	CLineMgr::GetInstance()->AddLine(m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.top);
}

int CQuestionBox::Update()
{
	CObj::LateInit();

	return NO_EVENT;
}

void CQuestionBox::LateUpdate()
{
	CObj::Animation();
}

void CQuestionBox::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"Blocks"));


	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		16 * m_tFrame.iFrameStart,
		16* m_tFrame.iScene,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CQuestionBox::Release()
{
}

void CQuestionBox::ChangeState(int _state)
{
	m_iState = _state;
	switch (m_iState)
	{
	case 0:
		m_hBrush = CreateSolidBrush(RGB(255, 255, 0));
		FrameChange(0, 3, 0, 200);
		break;
	case 1:
		m_hBrush = CreateSolidBrush(RGB(0, 255, 255));
		FrameChange(3, 3, 8, 200);
		break;
	default:
		break;
	}
}

void CQuestionBox::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if ((_objectID == ObjectID::PLAYER && _dir == DirID::DOWN)
		|| (_objectID == ObjectID::TURTLE_MONSTER && _dir != DirID::UP && _iState != 1)
		|| (_objectID == ObjectID::ATTACK)) {
		if (0 == m_iState) {
			CObj* pObj = nullptr;
			switch (m_eItemID)
			{
			case ItemID::FLOWER:
				pObj = CAbstractFactory<CFlower>::CreateObj(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY);
				CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::FLOWER);
				CSoundMgr::GetInstance()->PlaySoundW(L"Bump V2 SFX.wav", CSoundMgr::EFFECT);
				break;
			case ItemID::LEAF:
				pObj = CAbstractFactory<CLeaf>::CreateObj(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY);
				CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::LEAF);
				CSoundMgr::GetInstance()->PlaySoundW(L"Bump V2 SFX.wav", CSoundMgr::EFFECT);
				break;
			case ItemID::MUSHROOM:
				pObj = CAbstractFactory<CMushroom>::CreateObj(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY);
				CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::MUSHROOM);
				CSoundMgr::GetInstance()->PlaySoundW(L"Coin Obtained SFX.wav", CSoundMgr::EFFECT);
				break;
			case ItemID::COIN:
				pObj = CAbstractFactory<CCoin>::CreateObj(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY);
				CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::COIN);
				CSoundMgr::GetInstance()->PlaySoundW(L"Coin Obtained SFX.wav", CSoundMgr::EFFECT);
				break;
			default:
				break;
			}
			pObj->SetObjectState(0);
			ChangeState(1);
		}
	}
}
