#pragma once

#define CHECK_NULL(P) if(nullptr == (P)) { return; }

#define WINCX 800
#define WINCY 600

#define TILECX 64
#define TILECY 64

#define TILEX 30
#define TILEY 20

#define NO_EVENT 0
#define DEAD_OBJ 1

#define PI 3.141592f
#define GRAVITY 9.8f

#define RadianToDegree(X) X * 180.f / PI
#define DegreeToRadian(X) X * PI / 180.f

#define DECLARE_SINGLETON(ClassName)		\
public:										\
	static ClassName* GetInstance()			\
	{										\
		if (nullptr == m_pInstance)			\
			m_pInstance = new ClassName;	\
		return m_pInstance;					\
	}										\
	void DestroyInstance()					\
	{										\
		if (m_pInstance)					\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										\
private:									\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;