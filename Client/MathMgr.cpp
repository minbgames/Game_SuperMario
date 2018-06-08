#include "stdafx.h"
#include "MathMgr.h"
#include "Obj.h"


CMathMgr::CMathMgr()
{
}


CMathMgr::~CMathMgr()
{
}

float CMathMgr::CalcDistance(CObj* pDst, CObj* pSrc)
{
	float fWidth = pDst->GetInfo().fX - pSrc->GetInfo().fX;
	float fHeight = pDst->GetInfo().fY - pSrc->GetInfo().fY;

	return sqrtf(fWidth * fWidth + fHeight * fHeight);
}

float CMathMgr::CalcRadian(CObj* pDst, CObj* pSrc)
{
	float fWidth = pDst->GetInfo().fX - pSrc->GetInfo().fX;
	float fHeight = pDst->GetInfo().fY - pSrc->GetInfo().fY;
	float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float fAngle = acosf(fWidth / fDist);

	if (pSrc->GetInfo().fY < pDst->GetInfo().fY)
		fAngle *= -1.f;

	return fAngle;
}

float CMathMgr::CalcDegree(CObj * pDst, CObj * pSrc)
{
	float fWidth = pDst->GetInfo().fX - pSrc->GetInfo().fX;
	float fHeight = pDst->GetInfo().fY - pSrc->GetInfo().fY;
	float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float fAngle = acosf(fWidth / fDist);

	if (pSrc->GetInfo().fY < pDst->GetInfo().fY)
		fAngle *= -1.f;

	return fAngle * 180.f / PI;
}
