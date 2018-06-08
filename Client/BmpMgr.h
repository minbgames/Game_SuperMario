#pragma once

class CMyBmp;
class CBmpMgr
{
	DECLARE_SINGLETON(CBmpMgr)

private:
	CBmpMgr();
	~CBmpMgr();

public:
	HDC FindImage(const TCHAR* pBmpKey);

public:
	void InsertBmp(const TCHAR* pBmpKey, const TCHAR* pFilePath);
	void Release();

private:
	map<const TCHAR*, CMyBmp*>	m_MapBit;
};

