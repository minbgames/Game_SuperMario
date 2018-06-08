#include "stdafx.h"
#include "FinalItem.h"
#include "FinalMsg.h"

CFinalItem::CFinalItem()
{
	m_eLayer = LayerID::ITEM;
}


CFinalItem::~CFinalItem()
{
}


void CFinalItem::Initialize()
{
	m_bIsSetNumber = false;
	m_iSetNumber = 0;
}

void CFinalItem::LateInit()
{
	SetRangeValue(48, 48, 16, 16);
	FrameChange(0, 2, 0, 100);
	m_hBrush = CreateSolidBrush(RGB(0, 200, 200));
}

int CFinalItem::Update()
{
	CObj::LateInit();
	if (1 == m_iAnimState) {
		m_tInfo.fY -= 5.f;
		if (m_dwTime + 2400 < GetTickCount()) {
			CObj* pObj = CAbstractFactory<CFinalItem>::CreateObj(8270.f, 937.f);
			CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::FINAL_ITEM);
			dynamic_cast<CFinalItem*>(pObj)->SetItemNumber(m_tFrame.iFrameStart);
			m_iAnimState = 3;
			m_dwTime = GetTickCount();
		}
	}

	if (3 == m_iAnimState && m_dwTime + 2500 < GetTickCount()) {
		bGoToMap = true;
	}

	if (m_bIsDead)
		return DEAD_OBJ;

	return NO_EVENT;
}

void CFinalItem::LateUpdate()
{
	if (0 != m_iAnimState) return;
	CObj::Animation();
}

void CFinalItem::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"FinalItem"));


	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	if (m_bIsSetNumber) {
		GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX,
			m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY,
			(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
			hMemDC,
			20 * m_iSetNumber,
			0,
			(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
		return;
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		20 * m_tFrame.iFrameStart,
		0,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CFinalItem::Release()
{
}


void CFinalItem::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (_objectID == ObjectID::PLAYER) {
		m_iAnimState = 1;
		m_dwTime = GetTickCount();
		CSoundMgr::GetInstance()->StopSound(CSoundMgr::BGM);
		CSoundMgr::GetInstance()->PlaySound(L"3-26-course-clear.mp3", CSoundMgr::BGM);

		CObj* pObj = CAbstractFactory<CFinalMsg>::CreateObj(8087.f, 901.f);
		CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::FINAL_MSG);
	}
}
