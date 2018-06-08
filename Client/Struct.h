#pragma once

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;
}INFO;

typedef struct tagStat
{
	float fAttack;
	float fHp;
	float fMaxHp;
}STAT;

typedef struct tagLinePos
{
	tagLinePos()
		: fX(0.f), fY(0.f) {}

	tagLinePos(float x, float y)
		: fX(x), fY(y) {}

	float fX;
	float fY;
}LINEPOS;


typedef struct tagLineInfo
{
	tagLineInfo()
		: tLPoint({}), tRPoint({}) {}

	tagLineInfo(const LINEPOS& tLeft, const LINEPOS& tRight)
		: tLPoint(tLeft), tRPoint(tRight) {}

	LINEPOS tLPoint;
	LINEPOS tRPoint;
}LINEINFO;

typedef struct tagFrame
{
	int iFrameStart;	// 스프라이트 이미지의 x축의 시작점
	int iFrameEnd;		// 스프라이트 이미지의 x축의 끝점
	int iScene;			// 스프라이트 이미지의 y축의 시작점

	DWORD dwFrameOld;	// 애니메이션 재생이 시작되면 흐르는 시간.
	DWORD dwFrameSpd;	// 재생 속도
}FRAME;

typedef struct tagAdjust
{
	int iAxisMoveX;
	int iAxisMoveY;
	int iMarginX;
	int iMarginY;


}ADJUST;