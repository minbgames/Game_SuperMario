#include "stdafx.h"
#include "BmpMgr.h"
#include "MyBmp.h"

IMPLEMENT_SINGLETON(CBmpMgr)

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

HDC CBmpMgr::FindImage(const TCHAR* pBmpKey)
{
	if (m_MapBit.empty())
		return nullptr;

	auto& iter = find_if(m_MapBit.begin(), m_MapBit.end(), 
		[&pBmpKey](auto& MyPair)
	{
		return !lstrcmp(pBmpKey, MyPair.first);
	});

	if(m_MapBit.end() == iter)
		return nullptr;

	return iter->second->GetMemDC();
}

void CBmpMgr::InsertBmp(const TCHAR * pBmpKey, const TCHAR * pFilePath)
{
	CMyBmp* pBmp = new CMyBmp;

	if (true == m_MapBit.insert({ pBmpKey,  pBmp }).second)
		pBmp->LoadBmp(pFilePath);
	else
		SafeDelete(pBmp);
}

void CBmpMgr::Release()
{
	for_each(m_MapBit.begin(), m_MapBit.end(),
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_MapBit.clear();
}
