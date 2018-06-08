#include "stdafx.h"
#include "MapPlayer.h"


CMapPlayer::CMapPlayer()
{
}

CMapPlayer::~CMapPlayer()
{
}


void CMapPlayer::Initialize()
{
	SetRangeValue(14*3, 16 * 3, 14, 16);
	FrameChange(0, 1, 0, 150);
	m_hBrush = CreateSolidBrush(RGB(255, 255, 255));
	m_bIsMove = false;
}

int CMapPlayer::Update()
{
	if (m_bIsMove) {
		switch (m_eDir)
		{
		case DirID::UP:
			m_tInfo.fY -= 5.f;
			break;
		case DirID::DOWN:
			m_tInfo.fY += 5.f;
			break;
		case DirID::LEFT:
			m_tInfo.fX -= 5.f;
			break;
		case DirID::RIGHT:
			m_tInfo.fX += 5.f;
			break;
		default:
			break;
		}
		if (fabsf(m_tInfo.fX - m_tDstInfo.fX) < 5.f && fabsf(m_tInfo.fY - m_tDstInfo.fY) < 5.f) {
			m_tInfo.fX = m_tDstInfo.fX;
			m_tInfo.fY = m_tDstInfo.fY;
			m_bIsMove = false;
		}
		return NO_EVENT;
	}

	if (KEY_DOWN(VK_UP)) {
		m_eDir = DirID::UP;
	}
	else if (KEY_DOWN(VK_DOWN)) {
		m_eDir = DirID::DOWN;
	}
	else if (KEY_DOWN(VK_LEFT)) {
		m_eDir = DirID::LEFT;
	}
	else if (KEY_DOWN(VK_RIGHT)) {
		m_eDir = DirID::RIGHT;
	}
	else {
		m_eDir = DirID::END;
	}

	if (CPathMgr::GetInstance()->LineFollowing(m_tInfo, m_tDstInfo, m_eDir)) {
		m_bIsMove = true;
		CSoundMgr::GetInstance()->PlaySound(L"Moving SFX.wav", CSoundMgr::EFFECT);
	}
	else if (m_eDir != DirID::END) {
		CSoundMgr::GetInstance()->PlaySound(L"Bump V1 SFX.wav", CSoundMgr::EFFECT);
	}

	return NO_EVENT;
}

void CMapPlayer::LateUpdate()
{
	CObj::Animation();
}

void CMapPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"MapPlayer"));


	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		4 + 20* m_tFrame.iFrameStart,
		116,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CMapPlayer::Release()
{
}

void CMapPlayer::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}
