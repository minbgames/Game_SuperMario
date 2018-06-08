#include "stdafx.h"
#include "Door.h"


CDoor::CDoor()
{
}


CDoor::~CDoor()
{
}


void CDoor::Initialize()
{
	m_hBrush = CreateSolidBrush(RGB(0, 200, 200));
	SetRangeValue(0, 0, 0, 0);
	m_dwTime = GetTickCount();
}

void CDoor::LateInit()
{
}

int CDoor::Update()
{
	return 0;
}

void CDoor::LateUpdate()
{
}

void CDoor::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}
}

void CDoor::Release()
{
}

void CDoor::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}
