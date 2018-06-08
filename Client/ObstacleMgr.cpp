#include "stdafx.h"
#include "ObstacleMgr.h"
#include "Obstacle.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObstacleMgr)

CObstacleMgr::CObstacleMgr()
{
}


CObstacleMgr::~CObstacleMgr()
{
	Release();
}

void CObstacleMgr::Initialize()
{
	if (m_eScene == STAGE) {
		m_ObstacleLst.push_back(new CObstacle(1059, 1104, 1059 + OBSTACLE_PIPE_SIZE_X, 1249));
		m_ObstacleLst.push_back(new CObstacle(5378, 1152, 5378 + OBSTACLE_PIPE_SIZE_X, 1250));
		m_ObstacleLst.push_back(new CObstacle(5570, 1104, 5570 + OBSTACLE_PIPE_SIZE_X, 1250));
		m_ObstacleLst.push_back(new CObstacle(6772, 1104, 6772 + OBSTACLE_PIPE_SIZE_X, 1250));
		m_ObstacleLst.push_back(new CObstacle(6964, 1152, 6964 + OBSTACLE_PIPE_SIZE_X, 1250));
		m_ObstacleLst.push_back(new CObstacle(6772, 336, 6772 + OBSTACLE_PIPE_SIZE_X, 960));

		m_ObstacleLst.push_back(new CObstacle(1875, 1200, 1875 + OBSTACLE_SIZE_X, 1249));
		m_ObstacleLst.push_back(new CObstacle(3262- OBSTACLE_SIZE_X, 1200, 3262, MAINSTAGE_REAL_Y));
		m_ObstacleLst.push_back(new CObstacle(3458, 1250, 3458 + OBSTACLE_SIZE_X, MAINSTAGE_REAL_Y));
		m_ObstacleLst.push_back(new CObstacle(4511 - OBSTACLE_SIZE_X, 1250, 4511, MAINSTAGE_REAL_Y));
		m_ObstacleLst.push_back(new CObstacle(4610, 1250, 4610 + OBSTACLE_SIZE_X, MAINSTAGE_REAL_Y));
		m_ObstacleLst.push_back(new CObstacle(4848 - OBSTACLE_SIZE_X, 1250, 4848, MAINSTAGE_REAL_Y));
		m_ObstacleLst.push_back(new CObstacle(4995, 1250, 4995 + OBSTACLE_SIZE_X, MAINSTAGE_REAL_Y));
		m_ObstacleLst.push_back(new CObstacle(6719 - OBSTACLE_SIZE_X, 1250, 6719, MAINSTAGE_REAL_Y));
		m_ObstacleLst.push_back(new CObstacle(6770, 1250, 6770 + OBSTACLE_SIZE_X, MAINSTAGE_REAL_Y));

		m_ObstacleLst.push_back(new CObstacle(4514, 1008, 4606, 1058)); 
		m_ObstacleLst.push_back(new CObstacle(4707, 1200, 4753, 1250));
		m_ObstacleLst.push_back(new CObstacle(4753, 1152, 4802, 1250));
		m_ObstacleLst.push_back(new CObstacle(4802, 1104, 4848, 1250));
		m_ObstacleLst.push_back(new CObstacle(4995, 1104, 5042, 1250));
		m_ObstacleLst.push_back(new CObstacle(5042, 1152, 5091, 1250));
		m_ObstacleLst.push_back(new CObstacle(5091, 1200, 5139, 1250));

		m_ObstacleLst.push_back(new CObstacle(4227, 576, 4419, 626));
		m_ObstacleLst.push_back(new CObstacle(4468, 529, 5091, 579));
	}
	else if (m_eScene == UNDERSTAGE) {
		m_ObstacleLst.push_back(new CObstacle(342, 50 + 141, 390, 550 + 141));
		m_ObstacleLst.push_back(new CObstacle(390, 0 + 141, 484, 98 + 141));
		m_ObstacleLst.push_back(new CObstacle(484, 0 + 141, 1060, 50 + 141));
		m_ObstacleLst.push_back(new CObstacle(1060, 0 + 141, 1158, 98 + 141));
		m_ObstacleLst.push_back(new CObstacle(1158, 50 + 141, 1208, 200 + 141));
		m_ObstacleLst.push_back(new CObstacle(1015, 195 + 141, 1215, 245 + 141));
		m_ObstacleLst.push_back(new CObstacle(777, 434 + 141, 777 + 50, 434 + 50 + 141));
		m_ObstacleLst.push_back(new CObstacle(821, 385 + 141, 821 + 50, 385 + 50 + 141));
		m_ObstacleLst.push_back(new CObstacle(869, 338 + 141, 869 + 50, 338 + 50 + 141));
		m_ObstacleLst.push_back(new CObstacle(916, 290 + 141, 916 + 50, 290 + 50 + 141));
		m_ObstacleLst.push_back(new CObstacle(965, 242 + 141, 965 +50, 242 +50 + 141));
	}
	else if (m_eScene == FINALSTAGE) {
		m_ObstacleLst.push_back(new CObstacle(0, 169, 3890, 769));
		m_ObstacleLst.push_back(new CObstacle(0, 1011, 481, 1056));
		m_ObstacleLst.push_back(new CObstacle(484, 964, 529, 1008));
		m_ObstacleLst.push_back(new CObstacle(532, 914, 577, 960));
		m_ObstacleLst.push_back(new CObstacle(579, 771, 626, 912));
		m_ObstacleLst.push_back(new CObstacle(583, 1157, 627, 1202));
		m_ObstacleLst.push_back(new CObstacle(631, 1108, 674, 1155));
		m_ObstacleLst.push_back(new CObstacle(678, 1060, 724, 1107));
		m_ObstacleLst.push_back(new CObstacle(773, 1062, 819, 1300));
		m_ObstacleLst.push_back(new CObstacle(969, 1014, 1157, 1300));
		m_ObstacleLst.push_back(new CObstacle(1257, 1204, 1348, 1300));
		m_ObstacleLst.push_back(new CObstacle(1348, 1156, 1398, 1300));
		m_ObstacleLst.push_back(new CObstacle(1398, 1060, 1444, 1300));
		m_ObstacleLst.push_back(new CObstacle(1591, 1156, 1825, 1201));
		m_ObstacleLst.push_back(new CObstacle(2025, 1060, 2164, 1300));
		m_ObstacleLst.push_back(new CObstacle(2164, 1108, 2211, 1300));
		m_ObstacleLst.push_back(new CObstacle(2211, 1156, 2258, 1300));

		m_ObstacleLst.push_back(new CObstacle(3125, 1156, 3175, 1300));
		m_ObstacleLst.push_back(new CObstacle(3175, 1108, 3224, 1300));
		m_ObstacleLst.push_back(new CObstacle(3224, 1060, 3747, 1300));
		m_ObstacleLst.push_back(new CObstacle(3747, 1108, 3795, 1300));
		m_ObstacleLst.push_back(new CObstacle(3795, 1156, 3891, 1300));

		m_ObstacleLst.push_back(new CObstacle(4089, 1156, 4179, 1300));
		m_ObstacleLst.push_back(new CObstacle(4326, 1108, 4466, 1300));
		m_ObstacleLst.push_back(new CObstacle(4614, 1156, 4656, 1300));

		m_ObstacleLst.push_back(new CObstacle(2261, 769, 3024, 1057));
		m_ObstacleLst.push_back(new CObstacle(5335, 1010, 5860, 1204));

		m_ObstacleLst.push_back(new CObstacle(4759, 770, 4805, 817));
		m_ObstacleLst.push_back(new CObstacle(4805, 770, 4902, 866));
		m_ObstacleLst.push_back(new CObstacle(4902, 770, 4998, 913));
		m_ObstacleLst.push_back(new CObstacle(4998, 770, 5142, 962));
		m_ObstacleLst.push_back(new CObstacle(5142, 770, 5335, 1010));
		m_ObstacleLst.push_back(new CObstacle(5860, 770, 6913, 1008));

		m_ObstacleLst.push_back(new CObstacle(6916, 722, 7700, 770));
		m_ObstacleLst.push_back(new CObstacle(7641, 770, 7700, 1204));
	}



	//LoadData();
}

void CObstacleMgr::Render(HDC hDC)
{
	if (1==IsShowObstacle) {
		for (auto& pObstacle : m_ObstacleLst)
			pObstacle->Render(hDC);
	}
}

void CObstacleMgr::Release()
{
	for_each(m_ObstacleLst.begin(), m_ObstacleLst.end(), SafeDelete<CObstacle*>);
	m_ObstacleLst.clear();
}

void CObstacleMgr::ObstacleCollision(OBJLIST& _srcLst)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto& pDst : m_ObstacleLst)
	{
		for (auto& pSrc : _srcLst)
		{
			// pDst: 벽
			if (CheckRect(pSrc, pDst, &fMoveX, &fMoveY))
			{
				if (fMoveX > fMoveY)	
				{
					float fX = pSrc->GetInfo().fX;
					float fY = pSrc->GetInfo().fY;

					if (pDst->GetInfo().fY > fY)
						fMoveY *= -1.f;

					pSrc->SetPos(fX, fY + fMoveY);

					if (fMoveY>0) { // 윗 충돌
						pSrc->OnCollisionEnter(DirID::UP, ObjectID::OBSTACLE, 0);
					}
					else { // 아랫 충돌
						pSrc->OnCollisionEnter(DirID::DOWN, ObjectID::OBSTACLE, 0);
					}
				}
				else
				{
					float fX = pSrc->GetInfo().fX;
					float fY = pSrc->GetInfo().fY;

					if (pDst->GetInfo().fX > fX)
						fMoveX *= -1.f;

					pSrc->SetPos(fX + fMoveX, fY);

					if (fMoveX>0) { // 왼쪽 충돌
						pSrc->OnCollisionEnter(DirID::LEFT, ObjectID::OBSTACLE, 0);
					}
					else { // 오른쪽 충돌
						pSrc->OnCollisionEnter(DirID::RIGHT, ObjectID::OBSTACLE, 0);
					}
				}
			}
		}
	}
}

bool CObstacleMgr::CheckRect(CObj * pSrc, CObstacle * pDst, float * pMoveX, float * pMoveY)
{
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

void CObstacleMgr::LoadData()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"No Data", L"Load failed", MB_OK);
		return;
	}

	//RECT tLoad = {};
	//DWORD dwByte = 0;

	//while (true)
	//{
	//	ReadFile(hFile, &tLoad, sizeof(RECT), &dwByte, nullptr);

	//	// dwByte에 0이 기록되었다는 것은 더이상 읽을 자료가 없다는 의미!
	//	if (0 == dwByte)
	//		break;

	//	m_ObstacleLst.push_back(new CObstacle(tLoad));
	//}

	//CloseHandle(hFile);
}
