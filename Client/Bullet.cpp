#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}


void CBullet::Initialize()
{
	m_tStat.fAttack = 5.f;
	m_fJumpPow = 0.f;
	m_fJumpAcc = 0.1f;

	m_fSpeed = 10.f;
	m_fSlowSpeed = 1.f;
	m_bBulletInit = true;
	m_iState = 0;

	m_fVectorX = 0.f;
	m_fVectorY = 0.f;

	m_hBrush = CreateSolidBrush(RGB(255, 0, 0));
	SetRangeValue(20, 20, 16, 16);
	SetAdjustValue(-8, -8, 0, 0);
	m_dwTime = GetTickCount();
}

void CBullet::LateInit()
{
	if(m_fDir>0)
		FrameChange(0, 3, 1, 100);
	else
		FrameChange(0, 3, 0, 100);
}

int CBullet::Update()
{
	CObj::LateInit();

	if (m_dwTime + 10000 < GetTickCount()) m_bIsDead = true;

	if (m_bIsDead)
		return DEAD_OBJ;

	if (0 == m_iState) {
		IsJumping();
		m_tInfo.fX += m_fSpeed*m_fDir;
	}
	else {
		if (m_tInfo.fY > 1240) return DEAD_OBJ;
		
		switch (m_iState)
		{
		case 1:
			m_tInfo.fX += m_fSlowSpeed;
			m_tInfo.fY -= m_fSlowSpeed;
			break;
		case 2:
			m_tInfo.fX += m_fSlowSpeed;
			m_tInfo.fY += m_fSlowSpeed;
			break;
		case 3:
			m_tInfo.fX -= m_fSlowSpeed;
			m_tInfo.fY -= m_fSlowSpeed;
			break;
		case 4:
			m_tInfo.fX -= m_fSlowSpeed;
			m_tInfo.fY += m_fSlowSpeed;
			break;
		case 5:
			m_tInfo.fX += m_fSpeed*m_fVectorX / 4.0f;
			m_tInfo.fY += m_fSpeed*m_fVectorY / 4.0f;
			break;
		}
	}



	if (m_tInfo.fX < -m_tInfo.fCX / 2 || m_tInfo.fX > MAINSTAGE_REAL_X + m_tInfo.fCX / 2)
		m_bIsDead = true;
	else if (m_tInfo.fY < -m_tInfo.fCY / 2 || m_tInfo.fY > MAINSTAGE_REAL_Y + m_tInfo.fCY / 2)
		m_bIsDead = true;
	
	return NO_EVENT;
}

void CBullet::LateUpdate()
{
	CObj::Animation();
}

void CBullet::Render(HDC hDC)
{
	CObj::UpdateRect();

	int fScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
	int fScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

	HDC hMemDC = nullptr;
	CHECK_NULL(hMemDC = CBmpMgr::GetInstance()->FindImage(L"FireBall"));


	if (1 == IsShowCollider) {
		m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE / 2 * m_tRenInfo.fCX + fScrollX+ m_tAdjust.iAxisMoveX,
		m_tInfo.fY - RENDER_MULTIPLE / 2 * m_tRenInfo.fCY + fScrollY+ m_tAdjust.iAxisMoveY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		16 * m_tFrame.iFrameStart,
		16 * m_tFrame.iScene,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CBullet::Release()
{
}

void CBullet::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (_objectID == ObjectID::OBSTACLE) {
		if (_dir == DirID::LEFT || _dir == DirID::RIGHT) {
			m_bIsDead = true;
		}
	}
	else {
		m_bIsDead = true;
	}

	if (m_eObjectID == ObjectID::ENEMY_BULLET)
		if(_objectID == ObjectID::PLAYER)
			m_bIsDead = true;
}

void CBullet::IsJumping()
{
	float fMoveY = m_tInfo.fY;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.fX, &fMoveY, this);

	m_tInfo.fY -= m_fJumpPow  - GRAVITY * m_fJumpAcc * 0.5f;

	m_fSpeed -= 0.1f;
	m_fJumpAcc += 0.2f;

	if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f) // 점프 도중 지면에 닿았을 때
	{
		if (m_fJumpPow - GRAVITY * m_fJumpAcc * 0.5f < 0) {
			if (m_bBulletInit) {
				m_fJumpPow = 8.f;
				m_bBulletInit = false;
			}
			else {
				m_fJumpPow -= 1.5f;
				if (m_fJumpPow < 0.f) m_bIsDead = true;
			}
			m_fJumpAcc = 0.f;
		}
	}
}
