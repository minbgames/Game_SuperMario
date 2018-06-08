#include "stdafx.h"
#include "NoteBox.h"


CNoteBox::CNoteBox()
{
}


CNoteBox::~CNoteBox()
{
}


void CNoteBox::Initialize()
{
	m_bIsChange = false;
	m_hBrush = CreateSolidBrush(RGB(0, 0, 0));

	m_iState = 0;
}

void CNoteBox::LateInit()
{
	SetRangeValue(48, 48, 16, 16);
	FrameChange(0, 2, 3, 200);
}

int CNoteBox::Update()
{
	CObj::LateInit();
	if (m_bIsChange) {
		m_bIsChange = false;
		return NO_EVENT;
	}

	return NO_EVENT;
}

void CNoteBox::LateUpdate()
{
	CObj::Animation();
}

void CNoteBox::Render(HDC hDC)
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
		16 * m_tFrame.iScene,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CNoteBox::Release()
{
}

void CNoteBox::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (_objectID == ObjectID::PLAYER) {
		if (_dir == DirID::UP) {

		}
		else if (_dir == DirID::DOWN) {

		}
	}
}
