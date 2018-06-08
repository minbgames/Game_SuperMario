#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Attack.h"

CPlayer::CPlayer()	
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 145.f;
	m_tInfo.fY = 1203.f;
	// 초기 위치 설정
	SetRangeValue(38.f, 82.f, 34.f, 42.f);

	SetJumpInit(GROUND,0.f);
	m_bIsInit = true;
	m_bIsHolding = false;
	m_bIsFall = true;
	m_bIsJump = false;
	m_bUpThrow = false;
	m_bIsCtrl = false;
	m_bIsChange = false;
	m_bIsSitDown = false;
	m_bIsStart = true;
	m_iAnimState = 0;
	m_iAnimInit = 0;
	m_bAnimOnce = false;
	m_bSceneTimer = false;
	m_bUpKeyDown = false;
	m_bDownKeyDown = false;

	m_fDir = 1.0f;
	m_fSpeed = PLAYER_SPEED_ZERO;
	m_fJumpPow = PLAYER_JUMP_POW;
	m_fJumpAcc = PLAYER_JUMP_INIT;
	m_iState = 0;
	// 멤버변수

	m_ePlayerMode = DEFAULT;
	ChangeMode(MINI);
	m_eCurScene = WALK;
	m_ePreScene = m_eCurScene;
	m_dwTime = GetTickCount();
}

void CPlayer::LateInit()
{
}

int CPlayer::Update()
{
	CObj::LateInit();	
	
	if (1 == m_iAnimState) {
		IsJumping();
		if (m_iAnimInit == 1) {
			m_eCurScene = WALK;
			SceneChange();
			m_tFrame.dwFrameSpd = 20;
		}
		m_tInfo.fX += 3.0f;
		return NO_EVENT;
	}

	if (1 == IsPlayerNotDead) m_bIsDead = false;

	if (m_bIsDead) //죽음
	{
		if (!m_bSceneTimer) {
			CSoundMgr::GetInstance()->StopAll();
			CSoundMgr::GetInstance()->PlaySound(L"3-27-you-re-dead.mp3", CSoundMgr::PLAYER);


			m_pRightFrameKey = L"MarioDead";
			m_pLeftFrameKey = L"MarioDead";
			SetAdjustValue(0, 0, 0, 0);
			SetRangeValue(48, 48, 16, 16);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iScene = 0;
			bTimePause = true;
			m_dwTime = GetTickCount();
			m_bSceneTimer = true;
		}
		else {
			if (m_dwTime + 5000 < GetTickCount()) {
				bGoToMap = true;
			}
		}
		return NO_EVENT;
	}

	if (bTimePause) return NO_EVENT;


	if (m_bIsChange) {
		m_bIsChange = false;
	}

	bool bIsPressed = false;
	if (KEY_PRESSING(VK_LEFT))
	{
		m_fDir = -1.0f;
		if (fabsf(m_fSpeed) > 7.5) {
			m_eCurScene = RUN;
		}
		else {
			m_eCurScene = WALK;
		}
		bIsPressed = true;
	}
	else if (KEY_PRESSING(VK_RIGHT))
	{
		m_fDir = 1.0f;
		if (fabsf(m_fSpeed) > 7.5) {
			m_eCurScene = RUN;
		}
		else {
			m_eCurScene = WALK;
		}
		bIsPressed = true;
	}
	else
	{
		m_eCurScene = IDLE;
	}

	m_bUpKeyDown = false;
	m_bDownKeyDown = false;

	if (KEY_DOWN(VK_UP)) {
		m_bUpKeyDown = true;
	}
	else if (KEY_PRESSING(VK_UP)) {
		m_bUpThrow = true;
	}
	else {
		m_bUpThrow = false;
	}


	if (KEY_DOWN(VK_CONTROL)) {
		m_iState = 1;
		m_bIsCtrl = true;
		if (FIRE == m_ePlayerMode) {
			CObj* pObj = CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX+5.f*m_fDir, m_tInfo.fY);
			pObj->SetDir(m_fDir);
			CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::BULLET);
			CSoundMgr::GetInstance()->PlaySound(L"Flame Ball SFX.wav", CSoundMgr::PLAYER);
		}
		if (RACCOON == m_ePlayerMode) {
			m_bAnimOnce = true;
			m_ePreScene = ATTACK;
			FrameChange(0, 4, 11, 40);
			CObj* pObj = CAbstractFactory<CAttack>::CreateObj();
			dynamic_cast<CAttack*>(pObj)->SetPlayer(this);
			dynamic_cast<CAttack*>(pObj)->SetMargin(-31.f,27.f);
			CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ATTACK);

			pObj = CAbstractFactory<CAttack>::CreateObj();
			dynamic_cast<CAttack*>(pObj)->SetPlayer(this);
			dynamic_cast<CAttack*>(pObj)->SetMargin(31.f, 27.f);
			CObjectMgr::GetInstance()->AddObject(pObj, ObjectID::ATTACK);

			CSoundMgr::GetInstance()->PlaySound(L"Raccoon Tail Whip SFX.wav", CSoundMgr::PLAYER);
		}
	}
	else if (KEY_PRESSING(VK_CONTROL))
	{
		if (bIsPressed) {
			ChangeSpeed(PLAYER_MAX_SPEED*m_fDir);
		}
		else {
			ChangeSpeed(PLAYER_SPEED_ZERO);
		}
	}
	else if (KEY_UP(VK_CONTROL)) {
		m_iState = 0;
		m_bIsHolding = false;
		m_bIsCtrl = false;
	}
	else
	{
		if (bIsPressed) {
			ChangeSpeed(PLAYER_BASIC_SPEED*m_fDir);
		}
		else {
			ChangeSpeed(PLAYER_SPEED_ZERO);
		}
	}

	m_tInfo.fX += m_fSpeed;

	if (KEY_DOWN(VK_SPACE)) {
		if (!m_bIsFall && !m_bIsJump) {
			m_fJumpPow = PLAYER_JUMP_POW;
			SetJumpInit(JUMP,1.0f);
		}
		else if (m_ePlayerMode == RACCOON) {
			if (fabsf(m_fSpeed) > 7.5) {
				m_fJumpPow = 10.f;
				SetJumpInit(JUMP, 1.0f);
			}
		}
	}


	IsJumping();
	if (KEY_DOWN(VK_DOWN)) {
		m_bDownKeyDown = true;
	}
	else if (KEY_PRESSING(VK_DOWN) && MINI != m_ePlayerMode) {
		m_eCurScene = SITDOWN;
		m_bIsHolding = false;
		m_bIsSitDown = true;
	}
	else if (KEY_UP(VK_DOWN)) {
		m_bIsSitDown = false;
	}

	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	if (0 == m_iAnimState) {
		if (m_tInfo.fX < m_tInfo.fCX / 2)
			m_tInfo.fX = m_tInfo.fCX / 2;
		else if (m_tInfo.fX > MAINSTAGE_REAL_X - m_tInfo.fCX / 2)
			m_tInfo.fX = MAINSTAGE_REAL_X - m_tInfo.fCX / 2;
	}

	if (m_tInfo.fY < m_tInfo.fCY / 2)
		m_tInfo.fY = m_tInfo.fCY / 2;
	else if (m_tInfo.fY > MAINSTAGE_REAL_Y+100)
		m_tInfo.fY = MAINSTAGE_REAL_Y + 100;

	if (1 == IsPlayerNotDead) m_bIsDead = false;

	if (!m_bIsDead) {
		SceneChange();
		CObj::Animation();
	}

	CScrollMgr::GetInstance()->SetScrollX(m_tInfo.fX);
	CScrollMgr::GetInstance()->SetScrollY(m_tInfo.fY);
}

void CPlayer::Render(HDC hDC)
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
		Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY, m_tRect.right +fScrollX, m_tRect.bottom+ fScrollY);
		SelectObject(hDC, m_hPrev);
	}

	GdiTransparentBlt(hDC, m_tInfo.fX - RENDER_MULTIPLE/2*m_tRenInfo.fCX + fScrollX + m_tAdjust.iAxisMoveX, 
		m_tInfo.fY - RENDER_MULTIPLE / 2* m_tRenInfo.fCY + fScrollY+ m_tAdjust.iAxisMoveY,
		(int)m_tRenInfo.fCX*RENDER_MULTIPLE, (int)m_tRenInfo.fCY*RENDER_MULTIPLE,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tRenInfo.fCX + m_tAdjust.iMarginX,
		m_tFrame.iScene * (int)m_tRenInfo.fCY + m_tAdjust.iMarginY,
		(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, EXCEPT_COLOR);
}

void CPlayer::Release()
{
}

void CPlayer::OnCollisionEnter(DirID::DIRECTION _dir, ObjectID::OBJID _objectID, int _iState)
{
	if (_objectID == ObjectID::TURTLE_MONSTER) {
		if (_dir == DirID::DOWN) {
			if (3 == _iState) { //공중일떄
				if (m_bIsCtrl) {
					m_fJumpPow = PLAYER_STEP_CTRL_AIR;
				}
				else {
					m_fJumpPow = PLAYER_STEP_AIR;
				}
				m_bColOpt = true;
			}
			else {
				if (m_bIsCtrl) {
					m_fJumpPow = PLAYER_STEP_CTRL_GROUND;
				}
				else {
					m_fJumpPow = PLAYER_STEP_GROUND;
				}
			}
			SetJumpInit(JUMP, 1.0f);
		}
		else {
			if (0 == _iState || 2 == _iState) {
				if (RACCOON == m_ePlayerMode || FIRE == m_ePlayerMode) ChangeMode(NORMAL);
				else if (NORMAL == m_ePlayerMode) ChangeMode(MINI);
				else if (MINI == m_ePlayerMode) ChangeMode(PLAYER_DEAD);
			}
		}
	}
	else if (_objectID == ObjectID::GUMBA_MONSTER) {
		if (_dir == DirID::DOWN) {
			if (m_bIsCtrl) {
				m_fJumpPow = PLAYER_STEP_CTRL_GROUND;
			}
			else {
				m_fJumpPow = PLAYER_STEP_GROUND;
			}
			SetJumpInit(JUMP, 1.0f);
		}
		else {
			if (RACCOON == m_ePlayerMode || FIRE == m_ePlayerMode) ChangeMode(NORMAL);
			else if (NORMAL == m_ePlayerMode) ChangeMode(MINI);
			else if (MINI == m_ePlayerMode) ChangeMode(PLAYER_DEAD);
		}
	}
	else if (_objectID == ObjectID::ENEMY_BULLET || _objectID == ObjectID::FLOWER_MONSTER || _objectID == ObjectID::CIRCLE_MONSTER || _objectID == ObjectID::ENEMY_ATTACK) {
		if (RACCOON == m_ePlayerMode || FIRE == m_ePlayerMode) ChangeMode(NORMAL);
		else if (NORMAL == m_ePlayerMode) ChangeMode(MINI);
		else if (MINI == m_ePlayerMode) ChangeMode(PLAYER_DEAD);
	}
	else if (_objectID == ObjectID::BOSS) {
		ChangeMode(PLAYER_DEAD);
	}
	else if (_objectID == ObjectID::OBSTACLE || _objectID == ObjectID::QUESTION_BOX) {
		if (_dir == DirID::LEFT || _dir == DirID::RIGHT) {
			ChangeSpeed(PLAYER_SPEED_ZERO*m_fDir);
		}
		else if (_dir == DirID::UP) {
			SetJumpInit(FALL, 1.0f);
			CSoundMgr::GetInstance()->PlaySound(L"Bump V2 SFX.wav", CSoundMgr::PLAYER);
		}
	}
	else if (_objectID == ObjectID::NOTE_BOX) {
		if (_dir == DirID::LEFT || _dir == DirID::RIGHT) {
			ChangeSpeed(PLAYER_SPEED_ZERO*m_fDir);
		}
		else if (_dir == DirID::DOWN) {
			m_fJumpPow = 8.f;
			SetJumpInit(JUMP, 0.1f);
		}
		else if (_dir == DirID::UP) {
			SetJumpInit(FALL, 1.0f);
			CSoundMgr::GetInstance()->PlaySound(L"Bump V2 SFX.wav", CSoundMgr::PLAYER);
		}
	}
	else if (_objectID == ObjectID::FLOWER) {
		ChangeMode(FIRE);
	}
	else if (_objectID == ObjectID::MUSHROOM) {
		ChangeMode(NORMAL);
	}
	else if (_objectID == ObjectID::LEAF) {
		ChangeMode(RACCOON);
	}
	else if (_objectID == ObjectID::FINAL_ITEM) {
		SetJumpInit(FALL, 0.0f);
		m_iAnimState = 1;
		m_fDir = 1.0f;
	}
	else if (_objectID == ObjectID::DOOR) {
		if (m_bUpKeyDown) {
			if (_iState == 10) {
				m_tInfo.fX += 664.f;
			}
			else if (_iState == 11) {
				m_tInfo.fX -= 664.f;
			}
			else if (_iState == 9) {
				CSoundMgr::GetInstance()->PlaySound(L"Pipe Maze SFX.wav", CSoundMgr::PLAYER);
				bGoToMap = true;
			}
			m_bUpKeyDown = false;
		}
		else if (m_bDownKeyDown) {

		}
	}
}

void CPlayer::SceneChange()
{
	if (m_bAnimOnce) return;
	if (m_ePreScene != m_eCurScene)
	{
		switch (m_eCurScene)
		{
		case IDLE:
			FrameChange(0, 0, 0, 200);
			break;
		case WALK:
			if (m_ePlayerMode == MINI)
				FrameChange(0, 1, 1, 100);
			else if (m_ePlayerMode == NORMAL)
				FrameChange(0, 2, 1, 100);
			else
				FrameChange(0, 3, 1, 100);
			break;
		case RUN:
			if (m_ePlayerMode == MINI)
				FrameChange(0, 1, 2, 50);
			else if (m_ePlayerMode == NORMAL)
				FrameChange(0, 2, 2, 50);
			else
				FrameChange(0, 2, 2, 50);
			break;
		case AIR:
			FrameChange(0, 0, 3, 300);
			break;
		case FLY:
			if (m_ePlayerMode == RACCOON) {
				FrameChange(0, 2, 4, 300);
			}
			else {
				FrameChange(0, 0, 4, 300);
			}
			break;
		case SITDOWN:
			FrameChange(0, 0, 5, 300);
			break;
		}
		m_ePreScene = m_eCurScene;
	}
}

void CPlayer::ChangeMode(PLAYERMODE _ePlayerMode)
{
	if (!m_bIsStart && m_dwTime+2000 > GetTickCount()) return;
	if (m_ePlayerMode == _ePlayerMode) return;
	m_bAnimOnce = false;
	m_dwTime = GetTickCount();

	m_bIsChange = true;

	if (m_bIsStart) m_bIsStart = false;

	switch (_ePlayerMode)
	{
	case MINI:
		m_hBrush = CreateSolidBrush(RGB(255, 255, 255));
		SetAdjustValue(-13, -16, 0, 0);
		SetRangeValue(38, 44, 29, 28);

		if (!m_bIsInit)
			CSoundMgr::GetInstance()->PlaySound(L"Suit Loss (Japanese) SFX.wav", CSoundMgr::PLAYER);
		else
			m_bIsInit = false;

		if (m_ePlayerMode == NORMAL) {
			CSoundMgr::GetInstance()->PlaySound(L"Suit Loss (Japanese) SFX.wav", CSoundMgr::PLAYER);
		}
		break;
	case NORMAL:
		m_hBrush = CreateSolidBrush(RGB(0, 255, 0));
		SetAdjustValue(-13, -20, 0, 0);
		SetRangeValue(38, 82, 34, 42);

		if (m_ePlayerMode == FIRE || m_ePlayerMode == RACCOON) {
			CSoundMgr::GetInstance()->PlaySound(L"Suit Loss (Japanese) SFX.wav", CSoundMgr::PLAYER);
		}
		else if (m_ePlayerMode == MINI) {
			CSoundMgr::GetInstance()->PlaySound(L"Mushroom Obtained SFX.wav", CSoundMgr::PLAYER);
		}
		break;
	case FIRE:
		m_hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SetAdjustValue(-3, -16, 4, 0);
		SetRangeValue(38, 82, 28, 40);
		CSoundMgr::GetInstance()->PlaySound(L"Level Chest Opened SFX.wav", CSoundMgr::PLAYER);
		break;
	case RACCOON:
		m_hBrush = CreateSolidBrush(RGB(0, 0, 255));
		SetAdjustValue(0, -30, 10, 0);
		SetRangeValue(38, 82, 38, 50);
		CSoundMgr::GetInstance()->PlaySound(L"Raccoon Leaf Obtained SFX.wav", CSoundMgr::PLAYER);
		break;
	case PLAYER_DEAD:
		m_bIsDead = true;
		break;
	default:
		break;
	}
	m_ePlayerMode = _ePlayerMode;

	SetFrameKey();
}

void CPlayer::ReturnAdjust()
{
	switch (m_ePlayerMode)
	{
	case MINI:
		SetAdjustValue(-13, -16, 0, 0);
		SetRangeValue(38, 44, 29, 28);
		break;
	case NORMAL:
		SetAdjustValue(-13, -20, 0, 0);
		SetRangeValue(38, 82, 34, 42);
		break;
	case FIRE:
		SetAdjustValue(-3, -16, 4, 0);
		SetRangeValue(38, 82, 28, 40);
		break;
	case RACCOON:
		SetAdjustValue(0, -30, 10, 0);
		SetRangeValue(38, 82, 38, 50);
		break;
	default:
		break;
	}
}

void CPlayer::SetFrameKey()
{
	switch (m_ePlayerMode)
	{
	case MINI:
		m_pRightFrameKey = L"SmallMarioRight";
		m_pLeftFrameKey = L"SmallMarioLeft";
		break;
	case NORMAL:
		m_pRightFrameKey = L"BigMarioRight";
		m_pLeftFrameKey = L"BigMarioLeft";
		break;
	case FIRE:
		m_pRightFrameKey = L"FireMarioRight";
		m_pLeftFrameKey = L"FireMarioLeft";
		break;
	case RACCOON:
		m_pRightFrameKey = L"RacoonDogMarioRight";
		m_pLeftFrameKey = L"RacoonDogMarioLeft";
		break;
	default:
		break;
	}
}

void CPlayer::ChangeSpeed(float _fSpeed)
{
	if (m_bIsSitDown) _fSpeed = 0.f;

	if (fabsf(m_fSpeed - _fSpeed) <= PLAYER_SPEED_INC) {
		m_fSpeed = _fSpeed;
		return;
	}

	if (m_fSpeed > _fSpeed) {
		m_fSpeed -= PLAYER_SPEED_INC;
	}
	else if(m_fSpeed < _fSpeed){
		m_fSpeed += PLAYER_SPEED_INC;
	}
}

void CPlayer::SetJumpInit(MODE _mode, float _initAccel)
{
	if (JUMP == _mode) {
		m_bIsJump = true;
		m_bIsFall = false;
		m_fJumpAcc = _initAccel;
		if(m_fJumpPow == PLAYER_JUMP_POW)
			CSoundMgr::GetInstance()->PlaySound(L"Froggy Hop SFX.wav", CSoundMgr::PLAYER);
	}
	else if (FALL == _mode) {
		m_bIsJump = false;
		m_bIsFall = true;
		m_fJumpAcc = _initAccel;
	}
	else if (GROUND == _mode) {
		m_bIsJump = false;
		m_bIsFall = false;
	}
}

void CPlayer::IsJumping()
{
	if (m_tInfo.fY > 1350) m_bIsDead = true;

	float fMoveY = m_tInfo.fY;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.fX, &fMoveY, this);	

	if (!m_bIsFall && !m_bIsJump) {
		if (m_fPrevMoveY + 10.f < fMoveY) SetJumpInit(FALL, 0.5f);
	}

	if (m_bIsJump || m_bIsFall) {
		if (fabsf(m_fSpeed) > 7.5) {
			m_eCurScene = FLY;
		}
		else {
			m_eCurScene = AIR;
		}
	}
	
	if (m_bIsJump)
	{
		m_tInfo.fY -= m_fJumpPow * m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		
		if(m_fJumpAcc < PLAYER_ACCEL_LIMIT) m_fJumpAcc += PLAYER_ACCEL_INC;

		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f) // 점프 도중 지면에 닿았을 때
		{
			if (m_fJumpPow * m_fJumpAcc - GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f < 0) {
				SetJumpInit(GROUND,0.f);
				m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;
			}
		}
	}
	else if (m_bIsFall)
	{
		m_tInfo.fY += GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		if (m_fJumpAcc < PLAYER_ACCEL_LIMIT) m_fJumpAcc += PLAYER_ACCEL_INC;

		if (bColl && m_tInfo.fY > fMoveY - m_tInfo.fCY * 0.5f)
		{
			SetJumpInit(GROUND,0.f);
			m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;
			if (1 == m_iAnimState) m_iAnimInit = 1;
		}
	}
	else if(bColl)	
		m_tInfo.fY = fMoveY - m_tInfo.fCY * 0.5f;

	m_fPrevMoveY = fMoveY;
}

void CPlayer::OffSet()
{
}

