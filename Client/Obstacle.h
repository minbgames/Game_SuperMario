#pragma once
class CObstacle
{
public:
	CObstacle();
	CObstacle(int _left, int _top, int _right, int _bottom);
	~CObstacle();

public:
	const INFO& GetInfo() const { return m_tInfo; }

public:
	void Render(HDC hDC);

private:
	INFO	m_tInfo;
	RECT m_tRect;
};

