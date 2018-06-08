#include "stdafx.h"
#include "CircleMonster.h"

CCircleMonster::CCircleMonster()
{
}


CCircleMonster::~CCircleMonster()
{
	Release();
}

void CCircleMonster::Initialize()
{
	m_pRightFrameKey = L"CircleMonster";
	m_pLeftFrameKey = L"CircleMonster";

	FrameChange(0, 20, 0, 20);
	SetRangeValue(48, 48, 17, 17);
	SetAdjustValue(0, 0, 0, 0);
	// ROI ¼³Á¤

	m_fDir = 1.0f;
	m_fAngle = 0.f;
	m_fLength = 180.f;
}

void CCircleMonster::LateInit()
{
}

int CCircleMonster::Update()
{
	CObj::LateInit();

	m_fAngle += 2.f;
	if (m_fAngle > 360.f) m_fAngle -= 360.f;

	m_tInfo.fX = m_fCenterX + m_fLength*cosf(m_fAngle*3.141592 / 180);
	m_tInfo.fY = m_fCenterY + m_fLength*sinf(m_fAngle*3.141592 / 180);

	return NO_EVENT;
}

void CCircleMonster::LateUpdate()
{
	CObj::Animation();
}

void CCircleMonster::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	if (m_fDir > 0) {
		CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(m_pRightFrameKey));
	}
	else {
		CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(m_pLeftFrameKey));
	}

	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX + m_tAdjust.iAxisMoveX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY + m_tAdjust.iAxisMoveY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		(m_tFrame.iFrameStart % 3) *17,
		(m_tFrame.iFrameStart / 3)* 17,
		16, 16, EXCEPT_COLOR);
}

void CCircleMonster::Release()
{
}

void CCircleMonster::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	
}

