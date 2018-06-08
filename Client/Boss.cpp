#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "Effect.h"
#include "EnemyAttack.h"
#include "TurtleMonster.h"
#include "Bullet.h"

CBoss::CBoss()
{
}


CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize()
{
	m_pRightFrameKey = L"Boss";
	m_pLeftFrameKey = L"Boss";

	FrameChange(0, 1, 0, 20);
	SetRangeValue(24* 2*BOSS_MULTIPLE, 23* 2 * BOSS_MULTIPLE, 24, 23);
	// ROI 설정

	m_bIsFall = true;
	m_bIsJump = false;
	
	m_fSpeed = 1.f;
	m_fDir = -1.0f;
	m_fJumpPow = 12.f;
	m_fDashPow = 15.f;
	m_fJumpAcc = 0.f;
	m_iState = 0;
	m_tStat.fMaxHp = 6.f;
	m_tStat.fHp = m_tStat.fMaxHp;
	m_iAttackPattern = 0;
	m_iBulletCount = 0;
	m_fAngle = 180;
	// 멤버변수
}

void CBoss::LateInit()
{
	m_dwTime = GetTickCount();
}

int CBoss::Update()
{
	if (0 == IsBossTriger) return NO_EVENT;
	CObj::LateInit();

	if (m_bIsDead)
	{
		CObj* pObj = CAbstractFactory<CEffect>::CreateObj(m_tInfo.fX - 20.f, m_tInfo.fY - 30.f);
		CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::EFFECT);

		CSoundMgr::GetInstance()->StopAll();
		CSoundMgr::GetInstance()->PlaySound(L"Shell SFX.wav", CSoundMgr::TURTLE);
		CSoundMgr::GetInstance()->PlaySound(L"3-25-king-restored.mp3", CSoundMgr::UI);

		return DEAD_OBJ;
	}

	switch (m_iState)
	{
	case 0:
		PatternA();
		break;
	case 1:
		PatternB();
		break;
	case 2:
		PatternC();
		break;
	}

	return NO_EVENT;
}

void CBoss::LateUpdate()
{
	CObj::Animation();
}

void CBoss::Render(HDC hDC)
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

	GdiTransparentBlt(hDC, m_tInfo.fX - BOSS_MULTIPLE  * m_tRenInfo.fCX + fScrollX + m_tAdjust.iAxisMoveX,
		m_tInfo.fY - BOSS_MULTIPLE * m_tRenInfo.fCY + fScrollY + m_tAdjust.iAxisMoveY,
		(int)m_tRenInfo.fCX*2* BOSS_MULTIPLE, (int)m_tRenInfo.fCY*2* BOSS_MULTIPLE,
		hMemDC,
		m_tFrame.iFrameStart * 25,
		0,
		24, 23, EXCEPT_COLOR);
}

void CBoss::Release()
{
}

void CBoss::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (_objectID == ObjectID::TURTLE_MONSTER) {
		if (2 == _iState) {
			m_tStat.fHp -= 1.f;
		}
	}
	else if (_objectID == ObjectID::BULLET) {
		m_tStat.fHp -= 1.f;
	}
	else if (_objectID == ObjectID::ATTACK) {
		m_tStat.fHp -= 1.f;
	}
}

void CBoss::IsJumping()
{
	float fMoveY = m_tInfo.fY;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.fX, &fMoveY, this);

	if (m_bIsJump)
	{
		m_tInfo.fY -= m_fJumpPow*m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		if (TURTLE_JUMP_ZERO == m_fJumpAcc) {
			m_fJumpAcc = TURTLE_JUMP_INIT;
		}
		else {
			m_fJumpAcc += TURTLE_ACCEL_THROW_INC;
		}
		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f)
		{
			m_bIsJump = false;
			m_fJumpAcc = TURTLE_JUMP_ZERO;
			m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;

			CObj* pObj = CAbstractFactory<CEnemyAttack>::CreateObj(7268.f, 1180.f);
			CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ENEMY_ATTACK);

			for (int i = 0; i < 2; i++)
			{
				pObj = CAbstractFactory<CTurtleMonster>::CreateObj(7100.f + i*170.f, 770.f);
				CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::TURTLE_MONSTER);
			}
			CScrollMgr::GetInstance()->ShakeOn();
		}
	}
	else if (m_bIsFall)
	{
		m_tInfo.fY += GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		m_fJumpAcc += TURTLE_ACCEL_FALL_INC;
		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f)
		{
			m_bIsFall = false;
			m_fJumpAcc = TURTLE_JUMP_ZERO;
			m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;
		}
	}
	else if (bColl)
		m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;

	m_fPrevMoveY = fMoveY;
}

void CBoss::PatternA()
{
	if (m_dwTime + 6000 < GetTickCount()) {
		m_bIsJump = true;
		m_fJumpAcc = 1.0f;
		m_dwTime = GetTickCount();
	}

	if (m_tStat.fHp == 4.f) {
		m_iState = 1;
		m_iAttackPattern = 0;
		m_dwTime = GetTickCount();
	}

	IsJumping();
}

void CBoss::PatternB()
{
	CObj* pObj;
	if (2 == m_iAttackPattern) { // 미사일 발사
		if (m_dwTime + 60 < GetTickCount()) {

			m_fAngle += 27.f;
			if (m_fAngle > 360.f) m_fAngle -= 360.f;

			pObj = CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
			pObj->SetObjectState(5);
			dynamic_cast<CBullet*>(pObj)->SetVector(cosf(m_fAngle*3.141592f/180.f), sinf(m_fAngle*3.141592f / 180.f));
			CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ENEMY_BULLET);
			m_iBulletCount++;
			m_dwTime = GetTickCount();
			if (m_iBulletCount > 400) { m_iAttackPattern++; }
		}
		return;
	}

	if (m_dwTime + 2000 < GetTickCount() && 0== m_iAttackPattern) {
		m_bIsJump = true;
		m_fJumpAcc = 1.0f;
		m_dwTime = GetTickCount();
		m_iAttackPattern = 1; // 대기
	}

	if (m_dwTime + 4000 < GetTickCount() && ( 1 == m_iAttackPattern || 3 == m_iAttackPattern)) {
		m_iAttackPattern++;
		m_iBulletCount = 0;
		m_dwTime = GetTickCount();
		if (m_iAttackPattern == 4) m_iAttackPattern = 0;
	}

	if (m_tStat.fHp == 2.f) {
		m_iState = 2;
		m_iAttackPattern = 0;
		m_fAngle = 180.f;
		m_dwTime = GetTickCount();
	}

	IsJumping();
}

void CBoss::PatternC()
{
	CObj* pObj;
	if (2 == m_iAttackPattern) { // 미사일 발사

		if (m_dwTime + 300 < GetTickCount()) {
			for (int i = 0; i < 360; i += 30)
			{
				pObj = CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
				pObj->SetObjectState(5);
				dynamic_cast<CBullet*>(pObj)->SetVector(cosf(i*3.141592f / 180.f), sinf(i*3.141592f / 180.f));
				CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ENEMY_BULLET);
			}
			m_dwTime = GetTickCount();
		}
		m_tInfo.fX -= m_fDashPow*m_fDashAcc - GRAVITY * m_fDashAcc * m_fDashAcc * 0.5f;
		m_fDashAcc += 0.05f;
		if (m_tInfo.fX > m_fOriginX) {
			m_tInfo.fX = m_fOriginX;
			m_iAttackPattern = 3;
		}
		return;
	}

	if (m_dwTime + 2000 < GetTickCount() && 0 == m_iAttackPattern) {
		m_bIsJump = true;
		m_fJumpAcc = 1.0f;
		m_dwTime = GetTickCount();
		m_iAttackPattern = 1; // 대기
	}

	if (m_dwTime + 4000 < GetTickCount() && (1 == m_iAttackPattern || 3 == m_iAttackPattern)) {
		m_iAttackPattern++;
		if (2 == m_iAttackPattern) {
			m_fOriginX = m_tInfo.fX;
			m_fDashAcc = 1.0f;
		}
		if (m_iAttackPattern == 4) m_iAttackPattern = 0;
		m_dwTime = GetTickCount();
	}

	if (m_tStat.fHp == 0.f)
		m_bIsDead = true;

	IsJumping();
}

