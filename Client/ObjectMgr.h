#pragma once

class CObj;

class CObjectMgr
{
	DECLARE_SINGLETON(CObjectMgr)

private:
	CObjectMgr();
	~CObjectMgr();

public:
	CObj* GetPlayer() { return m_ObjLst[ObjectID::PLAYER].front(); }
	CObj* GetMapPlayer() { return m_ObjLst[ObjectID::MAP_PLAYER].front(); }
	CObj* GetTarget(CObj* pSrc, ObjectID::OBJID eID);

public:
	void AddObject(CObj* pObj, ObjectID::OBJID eID);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	void DeleteObject(ObjectID::OBJID eID);

private:
	OBJLIST m_ObjLst[ObjectID::END];
	OBJLIST m_RenderLst[LayerID::END];
};

