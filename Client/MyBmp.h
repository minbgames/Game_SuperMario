#pragma once

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC GetMemDC() { return m_hMemDC; }

public:
	void LoadBmp(const TCHAR* pFilePath);
	void Release();

private:
	HBITMAP		m_hBit;
	HBITMAP		m_hOld;

	HDC			m_hMemDC;
};

