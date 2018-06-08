#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CLineMgr)

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	if (m_eScene == STAGE) {
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(-100, MAINSTAGE_REAL_Y+100), LINEPOS(MAINSTAGE_REAL_X +100, MAINSTAGE_REAL_Y + 100))));

		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(0, 1250), LINEPOS(1875, 1250))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1875, 1200), LINEPOS(3262, 1200))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3458, 1250), LINEPOS(4511, 1250))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4610, 1250), LINEPOS(4820, 1250))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(5020, 1250), LINEPOS(6719, 1250))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(6770, 1250), LINEPOS(MAINSTAGE_REAL_X, 1250))));
		// Ground

		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(724, 1104), LINEPOS(863, 1104))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(823, 1008), LINEPOS(958, 1008))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1206, 1104), LINEPOS(1438, 1104))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1397, 1008), LINEPOS(1583, 1008))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1542, 912), LINEPOS(1726, 912))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1542, 1152), LINEPOS(1823, 1152))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3795, 1152), LINEPOS(4128, 1152))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3893, 1056), LINEPOS(4224, 1056))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3989, 960), LINEPOS(4320, 960))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(6437, 1104), LINEPOS(6575, 1104))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(6532, 816), LINEPOS(6671, 816))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3940, 433), LINEPOS(4127, 433))));
		//Block

		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1059, 1104), LINEPOS(1152, 1104))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(5378, 1152), LINEPOS(5471, 1152))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(5570, 1104), LINEPOS(5663, 1104))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(6772, 1104), LINEPOS(6866, 1104))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(6964, 1152), LINEPOS(7058, 1152))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(6772, 336), LINEPOS(6866, 336))));
		//Pipe

		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4514, 1008), LINEPOS(4606, 1008))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4707, 1200), LINEPOS(4753, 1200))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4753, 1152), LINEPOS(4802, 1152))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4802, 1104), LINEPOS(4848, 1104))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4995, 1104), LINEPOS(5042, 1104))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(5042, 1152), LINEPOS(5091, 1152))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(5091, 1200), LINEPOS(5139, 1200))));
		//Wall

		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4227, 576), LINEPOS(4419, 576))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4468, 529), LINEPOS(5091, 529))));
		//Cloud
	}
	else if (m_eScene == UNDERSTAGE) {
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(-100, UNDERSTAGE_REAL_Y + 100), LINEPOS(UNDERSTAGE_REAL_X + 100, UNDERSTAGE_REAL_Y + 100))));

		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(390,482+141), LINEPOS(777, 482 + 141))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(777, 434 + 141), LINEPOS(821, 434 + 141))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(821, 385 + 141), LINEPOS(869, 385 + 141))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(869, 338 + 141), LINEPOS(916, 338 + 141))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(916, 290 + 141), LINEPOS(965, 290 + 141))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(965, 242 + 141), LINEPOS(1014, 242 + 141))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1014, 195 + 141), LINEPOS(1158, 195 + 141))));
	}
	else if (m_eScene == FINALSTAGE) {
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(-100, FINALSTAGE_REAL_Y + 100), LINEPOS(FINALSTAGE_REAL_X + 100, FINALSTAGE_REAL_Y + 100))));

		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(0, 1204), LINEPOS(580, 1204))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(580, 1157), LINEPOS(630, 1157))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(630, 1109), LINEPOS(680, 1109))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(680, 1061), LINEPOS(830, 1061))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(969, 1014), LINEPOS(1157, 1014))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1257, 1204), LINEPOS(1348, 1204))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1348, 1156), LINEPOS(1398, 1156))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1398, 1060), LINEPOS(1441, 1060))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(1591, 1156), LINEPOS(1825, 1156))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(2025, 1060), LINEPOS(2164, 1060))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(2164, 1108), LINEPOS(2211, 1108))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(2211, 1156), LINEPOS(2258, 1156))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(2258, 1204), LINEPOS(3125, 1204))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3125, 1156), LINEPOS(3175, 1156))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3175, 1108), LINEPOS(3224, 1108))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3224, 1060), LINEPOS(3747, 1060))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3747, 1108), LINEPOS(3795, 1108))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(3795, 1156), LINEPOS(3891, 1156))));

		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4089, 1156), LINEPOS(4179, 1156))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4326, 1108), LINEPOS(4466, 1108))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4614, 1156), LINEPOS(4656, 1156))));
		m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(4614, 1204), LINEPOS(7700, 1204))));
	}

}

void CLineMgr::Render(HDC hDC)
{
	if (LINE_RENDER_OK) {
		for (auto& pLine : m_LineLst)
			pLine->Render(hDC);
	}
}

void CLineMgr::Release()
{
	for_each(m_LineLst.begin(), m_LineLst.end(), SafeDelete<CLine*>);
	m_LineLst.clear();
}

bool CLineMgr::LineCollision(float fInX, float* pOutY, CObj* _pObj)
{
	if (m_LineLst.empty())
		return false;

	ObjectID::OBJID _ID = ObjectID::END;
	if (_pObj != nullptr) {
		_ID = _pObj->GetObjectID();
	}

	float size_x = 0.f;

	switch (_ID)
	{
	case ObjectID::PLAYER:
	case ObjectID::TURTLE_MONSTER:
		size_x = _pObj->GetInfo().fCX / 2;
		break;
	default:
		break;
	}

	CLine* pTarget = nullptr;

	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	int count = 0;
	float fMinValue = -1.0f;
	for (auto& pLine : m_LineLst)
	{
		if (fInX > pLine->GetInfo().tLPoint.fX- size_x && fInX < pLine->GetInfo().tRPoint.fX+ size_x)
		{
			float fLineY = (pLine->GetInfo().tRPoint.fY - pLine->GetInfo().tLPoint.fY) / (pLine->GetInfo().tRPoint.fX - pLine->GetInfo().tLPoint.fX)*(fInX- pLine->GetInfo().tLPoint.fX) + pLine->GetInfo().tLPoint.fY;
			float fTempValue = fLineY - *pOutY;
			if (fTempValue > 0) {
				if (fMinValue == -1.0f) {
					fMinValue = fabsf(fTempValue);
					pTarget = pLine;
				}
				else if (fMinValue > fabsf(fTempValue)) {
					fMinValue = fabsf(fTempValue);
					pTarget = pLine;
				}
				count++;
			}
		}
	}

	//cout << count << endl;
	if (nullptr == pTarget)
		return false;

	float x1 = pTarget->GetInfo().tLPoint.fX;
	float y1 = pTarget->GetInfo().tLPoint.fY;
	float x2 = pTarget->GetInfo().tRPoint.fX;
	float y2 = pTarget->GetInfo().tRPoint.fY;

	*pOutY = (y2 - y1) / (x2 - x1) * (fInX - x1) + y1;
	return true;
}

void CLineMgr::AddLine(int _leftX, int _leftY, int _rightX, int _rightY)
{
	m_LineLst.push_back(new CLine(LINEINFO(LINEPOS(_leftX, _leftY), LINEPOS(_rightX, _rightY))));
}

void CLineMgr::LoadData()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"No Data", L"Load failed", MB_OK);
		return;
	}

	LINEINFO tLoad = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tLoad, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineLst.push_back(new CLine(tLoad));
	}

	CloseHandle(hFile);
}
