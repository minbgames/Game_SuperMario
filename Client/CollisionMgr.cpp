#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(OBJLIST& dstLst, OBJLIST& srcLst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	int SrctState = 0;
	int DstState = 0;
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			SrctState = pSrc->GetObjectState();
			DstState = pDst->GetObjectState();
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				if (fMoveX > fMoveY)
				{
					float fX = pSrc->GetInfo().fX;
					float fY = pSrc->GetInfo().fY;

					if (pDst->GetInfo().fY > fY)
						fMoveY *= -1.f;

					if (fMoveY>0) {
						pDst->OnCollisionEnter(DirID::DOWN, pSrc->GetObjectID(), SrctState);
						pSrc->OnCollisionEnter(DirID::UP, pDst->GetObjectID(), DstState);
					}
					else { 
						pDst->OnCollisionEnter(DirID::UP, pSrc->GetObjectID(), SrctState);
						pSrc->OnCollisionEnter(DirID::DOWN, pDst->GetObjectID(), DstState);
					}
				}
				else
				{
					float fX = pSrc->GetInfo().fX;
					float fY = pSrc->GetInfo().fY;

					if (pDst->GetInfo().fX > fX)
						fMoveX *= -1.f;

					if (fMoveX>0) {
						pDst->OnCollisionEnter(DirID::RIGHT, pSrc->GetObjectID(), SrctState);
						pSrc->OnCollisionEnter(DirID::LEFT, pDst->GetObjectID(), DstState);
					}
					else {
						pDst->OnCollisionEnter(DirID::LEFT, pSrc->GetObjectID(), SrctState);
						pSrc->OnCollisionEnter(DirID::RIGHT, pDst->GetObjectID(), DstState);
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionRectEX(OBJLIST & dstLst, OBJLIST & srcLst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	int SrctState = 0;
	int DstState = 0;
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			SrctState = pSrc->GetObjectState();
			DstState = pDst->GetObjectState();
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				if (fMoveX > fMoveY)
				{
					float fX = pSrc->GetInfo().fX;
					float fY = pSrc->GetInfo().fY;

					if (pDst->GetInfo().fY > fY)
						fMoveY *= -1.f;

					if(pSrc->GetColOption()) pSrc->SetPos(fX, fY + fMoveY);

					if (fMoveY>0) {
						pDst->OnCollisionEnter(DirID::DOWN, pSrc->GetObjectID(), SrctState);
						pSrc->OnCollisionEnter(DirID::UP, pDst->GetObjectID(), DstState);
					}
					else {
						pDst->OnCollisionEnter(DirID::UP, pSrc->GetObjectID(), SrctState);
						pSrc->OnCollisionEnter(DirID::DOWN, pDst->GetObjectID(), DstState);
					}
				}
				else
				{
					float fX = pSrc->GetInfo().fX;
					float fY = pSrc->GetInfo().fY;

					if (pDst->GetInfo().fX > fX)
						fMoveX *= -1.f;

					if (pSrc->GetColOption()) pSrc->SetPos(fX + fMoveX, fY);

					if (fMoveX>0) {
						pDst->OnCollisionEnter(DirID::RIGHT, pSrc->GetObjectID(), SrctState);
						pSrc->OnCollisionEnter(DirID::LEFT, pDst->GetObjectID(), DstState);
					}
					else {
						pDst->OnCollisionEnter(DirID::LEFT, pSrc->GetObjectID(), SrctState);
						pSrc->OnCollisionEnter(DirID::RIGHT, pDst->GetObjectID(), DstState);
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(OBJLIST& dstLst, OBJLIST& srcLst)
{
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{			
			if (CheckSphere(pDst, pSrc))
			{
				pDst->SetDamage(pSrc->GetStat().fAttack);
				pSrc->SetDead();
			}
		}
	}
}

bool CCollisionMgr::CheckSphere(CObj * pDst, CObj * pSrc)
{
	float fSumRad = pDst->GetInfo().fCX * 0.5f + pSrc->GetInfo().fCX * 0.5f;

	float w = pDst->GetInfo().fX - pSrc->GetInfo().fX;
	float h = pDst->GetInfo().fY - pSrc->GetInfo().fY;
	float fDist = sqrtf(w * w + h * h);

	if (fSumRad >= fDist)
		return true;

	return false;
}

bool CCollisionMgr::CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY)
{
	if (pDst == pSrc) return false;
	float fSumRadX = pDst->GetInfo().fCX * 0.5f + pSrc->GetInfo().fCX * 0.5f;
	float fSumRadY = pDst->GetInfo().fCY * 0.5f + pSrc->GetInfo().fCY * 0.5f;

	float fDistX = fabsf(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float fDistY = fabsf(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}
