#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}
CKeyMgr::~CKeyMgr()
{

}

bool CKeyMgr::KeyPressing(int iVKey)
{
	if (GetAsyncKeyState(iVKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::KeyDown(int iVKey)
{
	if (!m_bKeyState[iVKey] && GetAsyncKeyState(iVKey) & 0x8000)
	{
		m_bKeyState[iVKey] = !m_bKeyState[iVKey];
		return true;
	}

	return false;
}

bool CKeyMgr::KeyUp(int iVKey)
{
	if (m_bKeyState[iVKey] && !(GetAsyncKeyState(iVKey) & 0x8000))
	{
		m_bKeyState[iVKey] = !m_bKeyState[iVKey];
		return true;
	}

	return false;
}

void CKeyMgr::Update()
{
	for (int i = 0; i < MAX_VK; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];

		if (!m_bKeyState[i] && GetAsyncKeyState(i) & 0x8000)
			m_bKeyState[i] = !m_bKeyState[i];
	}
}