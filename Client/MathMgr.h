#pragma once

class CObj;
class CMathMgr
{
public:
	CMathMgr();
	~CMathMgr();

public:
	static float CalcDistance(CObj* pDst, CObj* pSrc);
	static float CalcRadian(CObj* pDst, CObj* pSrc);
	static float CalcDegree(CObj* pDst, CObj* pSrc);
};

