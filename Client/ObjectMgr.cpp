#include "stdafx.h"
#include "ObjectMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr()
{
}


CObjectMgr::~CObjectMgr()
{
	Release();
}

CObj * CObjectMgr::GetTarget(CObj* pSrc, ObjectID::OBJID eID)
{
	if (m_ObjLst[eID].empty())
		return nullptr;

	OBJITER iter_begin = m_ObjLst[eID].begin();
	OBJITER iter_end = m_ObjLst[eID].end();

	CObj* pTarget = *iter_begin;	
	float fDistance = CMathMgr::CalcDistance(pTarget, pSrc);

	for (auto& pObj : m_ObjLst[eID])
	{
		float fTempDist = CMathMgr::CalcDistance(pObj, pSrc);

		if (fTempDist < fDistance)
		{
			pTarget = pObj;
			fDistance = fTempDist;
		}
	}

	return pTarget;
}

void CObjectMgr::AddObject(CObj * pObj, ObjectID::OBJID eID)
{
	pObj->SetObjectID(eID);
	m_ObjLst[eID].push_back(pObj);
}

void CObjectMgr::Update()
{
	for (int i = 0; i < ObjectID::END; ++i)
	{
		auto iter_begin = m_ObjLst[i].begin();
		auto iter_end = m_ObjLst[i].end();

		for (; iter_begin != iter_end; )
		{
			int iEvent = NO_EVENT;
			if (!bTimePause || i == 0) {
				iEvent = (*iter_begin)->Update();
			}

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjLst[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}
}

void CObjectMgr::LateUpdate()
{
	for (int i = 0; i < ObjectID::END; ++i)
	{
		for (auto& pObj : m_ObjLst[i])
		{
			pObj->LateUpdate();

			if (m_ObjLst[i].empty())
				return;

			m_RenderLst[pObj->GetLayer()].push_back(pObj);
		}
	}

	// 사각형 충돌
	if (!m_ObjLst[ObjectID::PLAYER].empty()) {
		if (!(*m_ObjLst[ObjectID::PLAYER].begin())->GetHold()) {
			CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::TURTLE_MONSTER], m_ObjLst[ObjectID::PLAYER]);
			CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::QUESTION_BOX], m_ObjLst[ObjectID::TURTLE_MONSTER]);
			CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::NOTE_BOX], m_ObjLst[ObjectID::TURTLE_MONSTER]);
			CObstacleMgr::GetInstance()->ObstacleCollision(m_ObjLst[ObjectID::TURTLE_MONSTER]);
		}
	}
	CCollisionMgr::CollisionRect(m_ObjLst[ObjectID::TURTLE_MONSTER], m_ObjLst[ObjectID::ATTACK]);
	CCollisionMgr::CollisionRect(m_ObjLst[ObjectID::QUESTION_BOX], m_ObjLst[ObjectID::ATTACK]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::FINAL_ITEM], m_ObjLst[ObjectID::PLAYER]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::LEAF], m_ObjLst[ObjectID::PLAYER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::FLOWER], m_ObjLst[ObjectID::PLAYER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::COIN], m_ObjLst[ObjectID::PLAYER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::MUSHROOM], m_ObjLst[ObjectID::PLAYER]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::NOTE_BOX], m_ObjLst[ObjectID::MUSHROOM]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::QUESTION_BOX], m_ObjLst[ObjectID::MUSHROOM]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::QUESTION_BOX], m_ObjLst[ObjectID::PLAYER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::NOTE_BOX], m_ObjLst[ObjectID::PLAYER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::TURTLE_MONSTER], m_ObjLst[ObjectID::TURTLE_MONSTER]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::TURTLE_MONSTER], m_ObjLst[ObjectID::BULLET]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::QUESTION_BOX], m_ObjLst[ObjectID::BULLET]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::GUMBA_MONSTER], m_ObjLst[ObjectID::QUESTION_BOX]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::GUMBA_MONSTER], m_ObjLst[ObjectID::NOTE_BOX]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::GUMBA_MONSTER], m_ObjLst[ObjectID::BULLET]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::GUMBA_MONSTER], m_ObjLst[ObjectID::ATTACK]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::GUMBA_MONSTER], m_ObjLst[ObjectID::TURTLE_MONSTER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::GUMBA_MONSTER], m_ObjLst[ObjectID::PLAYER]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::FLOWER_MONSTER], m_ObjLst[ObjectID::BULLET]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::FLOWER_MONSTER], m_ObjLst[ObjectID::TURTLE_MONSTER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::FLOWER_MONSTER], m_ObjLst[ObjectID::ATTACK]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::FLOWER_MONSTER], m_ObjLst[ObjectID::PLAYER]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::BOSS], m_ObjLst[ObjectID::BULLET]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::BOSS], m_ObjLst[ObjectID::TURTLE_MONSTER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::BOSS], m_ObjLst[ObjectID::ATTACK]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::BOSS], m_ObjLst[ObjectID::PLAYER]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::CIRCLE_MONSTER], m_ObjLst[ObjectID::PLAYER]);

	CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::ENEMY_BULLET], m_ObjLst[ObjectID::PLAYER]);

	CCollisionMgr::CollisionRect(m_ObjLst[ObjectID::DOOR], m_ObjLst[ObjectID::PLAYER]);
	CCollisionMgr::CollisionRect(m_ObjLst[ObjectID::ENEMY_ATTACK], m_ObjLst[ObjectID::PLAYER]);


	CObstacleMgr::GetInstance()->ObstacleCollision(m_ObjLst[ObjectID::PLAYER]);
	CObstacleMgr::GetInstance()->ObstacleCollision(m_ObjLst[ObjectID::BULLET]);
	CObstacleMgr::GetInstance()->ObstacleCollision(m_ObjLst[ObjectID::GUMBA_MONSTER]);
	CObstacleMgr::GetInstance()->ObstacleCollision(m_ObjLst[ObjectID::MUSHROOM]);
	//CCollisionMgr::CollisionRect(m_ObjLst[ObjectID::MONSTER], m_ObjLst[ObjectID::BULLET]);
	//CCollisionMgr::CollisionRectEX(m_ObjLst[ObjectID::MONSTER], m_ObjLst[ObjectID::PLAYER]);

	// 원 충돌
	//CCollisionMgr::CollisionSphere(m_ObjLst[ObjectID::MONSTER], m_ObjLst[ObjectID::MOUSE]);
	//CCollisionMgr::CollisionSphere(m_ObjLst[ObjectID::MONSTER], m_ObjLst[ObjectID::BULLET]);
	//CCollisionMgr::CollisionSphere(m_ObjLst[ObjectID::MONSTER], m_ObjLst[ObjectID::SHIELD]);
}

void CObjectMgr::Render(HDC hDC)
{
	for (int i = 0; i < LayerID::END; ++i)
	{
		m_RenderLst[i].sort(LessY<CObj*>);

		for (auto& pObj : m_RenderLst[i])
			pObj->Render(hDC);

		m_RenderLst[i].clear();
	}
}

void CObjectMgr::Release()
{
	for (int i = 0; i < ObjectID::END; ++i)
	{
		for_each(m_ObjLst[i].begin(), m_ObjLst[i].end(),
			[](auto& obj)
		{
			if (obj)
			{
				delete obj;
				obj = nullptr;
			}
		});
		m_ObjLst[i].clear();
	}
}

void CObjectMgr::DeleteObject(ObjectID::OBJID eID)
{
	for_each(m_ObjLst[eID].begin(), m_ObjLst[eID].end(), SafeDelete<CObj*>);
	m_ObjLst[eID].clear();
}
