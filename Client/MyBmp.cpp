#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::LoadBmp(const TCHAR * pFilePath)
{
	HDC hDC = GetDC(g_hWnd);
	
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBit = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0
		, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBit);
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOld);
	DeleteObject(m_hBit);
	DeleteDC(m_hMemDC);
}
