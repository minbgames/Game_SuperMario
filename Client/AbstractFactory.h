#pragma once

class CObj;

template <typename T>
class CAbstractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* CreateObj(const INFO& rInfo)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetInfo(rInfo);

		return pObj;
	}

	static CObj* CreateObj(float x, float y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(x, y);

		return pObj;
	}

	static CObj* CreateObj(float x, float y, float angle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(x, y);
		pObj->SetAngle(angle);

		return pObj;
	}
};