#include "stdafx.h"
#include "PathMgr.h"
#include "Line.h"

IMPLEMENT_SINGLETON(CPathMgr)

CPathMgr::CPathMgr()
{
}


CPathMgr::~CPathMgr()
{
}

void CPathMgr::Initialize()
{
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(136, 155), LINEPOS(243, 155))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(243, 155), LINEPOS(243, 60))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(243, 60), LINEPOS(339, 60))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(339, 60), LINEPOS(435, 60))));

	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(435, 60), LINEPOS(527, 60))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(527, 60), LINEPOS(626, 60))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(626, 60), LINEPOS(626, 158))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(435, 60), LINEPOS(435, 158))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(435, 158), LINEPOS(527, 158))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(527, 158), LINEPOS(626, 158))));

	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(435, 158), LINEPOS(435, 253))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(435, 253), LINEPOS(329, 253))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(329, 253), LINEPOS(242, 253))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(242, 253), LINEPOS(242, 350))));
	
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(242, 350), LINEPOS(242, 443))));

	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(242, 443), LINEPOS(339, 443))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(339, 443), LINEPOS(436, 443))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(436, 443), LINEPOS(436, 349))));

	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(436, 349), LINEPOS(532, 349))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(436, 349), LINEPOS(328, 349))));
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(532, 349), LINEPOS(615, 349))));
}

void CPathMgr::Render(HDC hDC)
{
	if (PATH_RENDER_OK) {
		for (auto& pLine : m_LineLst)
			pLine->Render(hDC);
	}
}

void CPathMgr::Release()
{
	for_each(m_LineLst.begin(), m_LineLst.end(), SafeDelete<CLine*>);
	m_LineLst.clear();
}

bool CPathMgr::LineFollowing(INFO& _tSrcInfo, INFO& _tDstInfo, DirID::DIRECTION _eDir)
{
	if (_eDir == DirID::END) return false;
	for (auto& pLine : m_LineLst)
	{
		float leftX = pLine->GetInfo().tLPoint.fX;
		float leftY = pLine->GetInfo().tLPoint.fY;
		float rightX = pLine->GetInfo().tRPoint.fX;
		float rightY = pLine->GetInfo().tRPoint.fY;

		if (leftX == _tSrcInfo.fX && leftY == _tSrcInfo.fY)
		{
			_tDstInfo.fX = rightX;
			_tDstInfo.fY = rightY;
			if (_eDir == CheckDirection(leftX, leftY, rightX, rightY)) return true;
		}
		else if (rightX == _tSrcInfo.fX && rightY == _tSrcInfo.fY) {

			_tDstInfo.fX = leftX;
			_tDstInfo.fY = leftY;
			if (_eDir == CheckDirection(rightX, rightY, leftX, leftY)) return true;
		}
	}

	return false;
}

DirID::DIRECTION CPathMgr::CheckDirection(float _srcX, float _srcY, float _dstX, float _dstY)
{
	if (_srcX == _dstX) {
		if (_srcY > _dstY) {
			return DirID::UP;
		}
		else {
			return DirID::DOWN;
		}
	}
	else if (_srcY == _dstY) {

		if (_srcX > _dstX) {
			return DirID::LEFT;
		}
		else {
			return DirID::RIGHT;
		}
	}
	return DirID::END;
}
