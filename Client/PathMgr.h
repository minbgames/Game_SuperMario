#pragma once

class CLine;
class CPathMgr
{
	DECLARE_SINGLETON(CPathMgr)

private:
	CPathMgr();
	~CPathMgr();

public:
	void Initialize();
	void Render(HDC hDC);
	void Release();

public:
	bool LineFollowing(INFO& _tSrcInfo, INFO& _tDstInfo, DirID::DIRECTION _eDir);

private:
	DirID::DIRECTION CheckDirection(float _srcX, float _srcY, float _dstX, float _dstY);

private:
	list<CLine*>		m_LineLst;
};