#include "stdafx.h"
#include "FlowerMonster.h"
#include "Player.h"
#include "Effect.h"
#include "Bullet.h"

CFlowerMonster::CFlowerMonster()
{
}


CFlowerMonster::~CFlowerMonster()
{
	Release();
}

void CFlowerMonster::Initialize()
{
	m_fPlusDir = 1.f;
	// 9 ~ 42
	m_fFlowerLengthY = 9;
	m_bDownAnim = true;
	m_pRightFrameKey = L"FlowerRight";
	m_pLeftFrameKey = L"FlowerLeft";
	m_tFrame.iFrameStart = 0;
	SetRangeValue(50, 100, 50, m_fFlowerLengthY);
	SetAdjustValue(6, -1, 0, 0);

	m_fDir = -1.0f;

	m_dwTime = GetTickCount();
	m_dwAnimTime = GetTickCount();
}

void CFlowerMonster::LateInit()
{
	m_pPlayer = CObjectMgr::GetInstance()->GetPlayer();
}

int CFlowerMonster::Update()
{
	CObj::LateInit();
	CObj* pObj;

	if (m_bIsDead)
	{
		pObj = CAbstractFactory<CEffect>::CreateObj(m_tInfo.fX - 20.f, m_tInfo.fY - 30.f);
		CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::EFFECT);

		CSoundMgr::GetInstance()->PlaySound(L"Shell SFX.wav", CSoundMgr::TURTLE);
		return DEAD_OBJ;
	}
	if (m_pPlayer->GetInfo().fX > m_tInfo.fX) m_fDir = 1.0f;
	if (m_pPlayer->GetInfo().fX < m_tInfo.fX) m_fDir = -1.0f;

	if (m_iIndex == 0) {
		if (m_pPlayer->GetInfo().fY > m_tInfo.fY + 100.f) { // 아래
			if (m_fDir > 0) {
				m_tFrame.iFrameStart = 1;
			}
			else {
				m_tFrame.iFrameStart = 2;
			}
		}
		else if (m_pPlayer->GetInfo().fY <= m_tInfo.fY + 100.f) {
			if (m_fDir > 0) {
				m_tFrame.iFrameStart = 0;
			}
			else {
				m_tFrame.iFrameStart = 3;
			}
		}
	}



	if (m_bDownAnim) {
		if (m_dwAnimTime + 1000 < GetTickCount()) {
			if (fabsf(m_pPlayer->GetInfo().fX - m_tInfo.fX) < 250.f) {
				m_bDownAnim = false;
			}
		}
		return NO_EVENT;
	}

	if (m_bUpAnim) {
		switch (m_iIndex)
		{
		case 0:
			if (m_dwAnimTime + 2000 < GetTickCount()) {
				if (m_pPlayer->GetInfo().fY > m_tInfo.fY + 100.f) { // 아래
					if (m_fDir > 0) {
						m_tFrame.iFrameStart = 3;
						pObj = CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX + m_fDir * 30.f, m_tInfo.fY - 20.f);
						pObj->SetObjectState(2);
						CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ENEMY_BULLET);
					}
					else {
						m_tFrame.iFrameStart = 0;
						pObj = CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX + m_fDir * 30.f, m_tInfo.fY - 20.f);
						pObj->SetObjectState(4);
						CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ENEMY_BULLET);
					}
				}
				else if (m_pPlayer->GetInfo().fY <= m_tInfo.fY + 100.f) {
					if (m_fDir > 0) {
						m_tFrame.iFrameStart = 2;
						pObj = CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX + m_fDir * 30.f, m_tInfo.fY - 20.f);
						pObj->SetObjectState(1);
						CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ENEMY_BULLET);
					}
					else {
						m_tFrame.iFrameStart = 1;
						pObj = CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX + m_fDir * 30.f, m_tInfo.fY - 20.f);
						pObj->SetObjectState(3);
						CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ENEMY_BULLET);
					}
				}
				m_dwAnimTime = GetTickCount();
				m_iIndex = 1;
			}
			break;
		case 1:
			if (m_dwAnimTime + 2000 < GetTickCount()) {
				m_bUpAnim = false;
			}
			break;
		}
		return NO_EVENT;
	}

	if (m_dwTime + 30 < GetTickCount()) {
		if (m_fFlowerLengthY < 9) {
			m_fPlusDir = 1.f;
			m_dwAnimTime = GetTickCount();
			m_iIndex = 0;
			m_bDownAnim = true;
		}
		if (m_fFlowerLengthY > 42) {
			m_fPlusDir = -1.f;
			m_dwAnimTime = GetTickCount();
			m_iIndex = 0;
			m_bUpAnim = true;
		}
		m_fFlowerLengthY += m_fPlusDir;
		m_tInfo.fY -= m_fPlusDir*3;

		SetRangeValue(50, 100, 50, m_fFlowerLengthY);

		m_dwTime = GetTickCount();
	}


	return NO_EVENT;
}

void CFlowerMonster::LateUpdate()
{
}

void CFlowerMonster::Render(HDC hDC)
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
		m_tInfo.fY - RENDER_MULTIPLE / 2 * 50 + fScrollY + m_tAdjust.iAxisMoveY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tRenInfo.fCX,
		0,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CFlowerMonster::Release()
{
}

void CFlowerMonster::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (_objectID == ObjectID::BULLET || _objectID == ObjectID::ATTACK || _objectID == ObjectID::TURTLE_MONSTER)
		m_bIsDead = true;
}

