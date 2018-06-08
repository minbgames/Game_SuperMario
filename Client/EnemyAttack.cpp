#include "stdafx.h"
#include "EnemyAttack.h"


CEnemyAttack::CEnemyAttack()
{
}


CEnemyAttack::~CEnemyAttack()
{
}

void CEnemyAttack::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
}

void CEnemyAttack::Initialize()
{
	m_dwTime = GetTickCount();
	SetRangeValue(1000, 40, 0, 0);
}

void CEnemyAttack::LateInit()
{
}

int CEnemyAttack::Update()
{
	if (m_dwTime + 100 < GetTickCount()) return DEAD_OBJ;

	return NO_EVENT;
}

void CEnemyAttack::LateUpdate()
{
}

void CEnemyAttack::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());
	if (1 == IsShowCollider) {
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
	}
}

void CEnemyAttack::Release()
{
}
