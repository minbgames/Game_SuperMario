#pragma once

#define MAX_VK 0xff

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool KeyPressing(int iVKey);
	bool KeyDown(int iVKey);
	bool KeyUp(int iVKey);

	void Update();

private:
	bool m_bKeyState[MAX_VK];
};