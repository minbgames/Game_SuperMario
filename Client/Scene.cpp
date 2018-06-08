#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
	:m_iAnimNumber(0), m_bAnimOn(false), m_bSceneInit(true)
{
	m_dwTime = GetTickCount();
}

CScene::~CScene()
{
}

void CScene::Animation(MODE _mode)
{
	if (ENTER_MODE == _mode) {
		if (m_dwTime + 75 < GetTickCount()) {
			++m_iAnimNumber;
			m_dwTime = GetTickCount();
			if (m_iAnimNumber == 13) {
				m_bAnimOn = false;
			}
		}
	}
	else if (EXIT_MODE == _mode) {
		if (m_dwTime + 75 < GetTickCount()) {
			--m_iAnimNumber;
			m_dwTime = GetTickCount();
			if (m_iAnimNumber == 0) {
				m_bAnimOn = false;
			}
		}
	}
}
