#include "stdafx.h"
#include "Attack.h"


CAttack::CAttack()
{
}


CAttack::~CAttack()
{
}

void CAttack::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}

void CAttack::Initialize()
{
	m_dwTime = GetTickCount();
	SetRangeValue(26, 26, 0, 0);
}

void CAttack::LateInit()
{
}

int CAttack::Update()
{
	m_tInfo.fX = m_pPlayer->GetInfo().fX+m_fMarginX;
	m_tInfo.fY = m_pPlayer->GetInfo().fY+m_fMarginY;
	if (m_dwTime + 200 < GetTickCount()) return DEAD_OBJ;

	return NO_EVENT;
}

void CAttack::LateUpdate()
{
}

void CAttack::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());
	if (1 == IsShowCollider) {
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
	}
}

void CAttack::Release()
{
}
