//int iScrollX = static_cast<int>(CScrollMgr::GetInstance()->GetScrollX());
//int iScrollY = static_cast<int>(CScrollMgr::GetInstance()->GetScrollY());

//m_tFrame.iFrameStart = 0; // 왼쪽 프레임
//m_tFrame.iFrameEnd = 2; // 오른쪽 끝 프레임
//m_tFrame.iScene = 1; // 높이
//m_pFrameKey와 CX CY를 잘 설정해줘야 한다.

//HBRUSH	m_hBrush;
//HBRUSH	m_hPrev;
//m_hBrush = CreateSolidBrush(RGB(0, 200, 0));
//m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
//Rectangle(hDC, m_tRect.left, m_tRect.top - (int)fScrollY, m_tRect.right, m_tRect.bottom - (int)fScrollY);
//SelectObject(hDC, m_hPrev);


//// 총알 개수 출력
//TCHAR szBuf[32] = L"";
//
//// swprintf_s: 두번째 인수와 세번째 인수가 결합되어 완성된 문자열을 첫번째 인수에 기록한다.
//swprintf_s(szBuf, L"Bullet: %d", m_ObjLst[ObjectID::BULLET].size());
//TextOut(m_hDC, 50, 50, szBuf, lstrlen(szBuf));

//POINT pt = {};
//
//// GetCursorPos: 현재 전체 스크린 상의 마우스 커서의 위치 정보를 얻어오는 함수.
//GetCursorPos(&pt);
//
//// ScreenToClient: 스크린 좌표를 클라이언트 좌표로 변환하는 함수.
//ScreenToClient(g_hWnd, &pt);

//GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY,
//	hMemDC, m_tFrame.iFrameStart * (int)m_tRenInfo.fCX, m_tFrame.iScene * (int)m_tRenInfo.fCY,
//	(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, RGB(0, 255, 0));

//GdiTransparentBlt(hDC, m_tRenRect.left + fScrollX, m_tRenRect.top + fScrollY, (int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY,
//	hMemDC, m_tFrame.iFrameStart * (int)m_tRenInfo.fCX, m_tFrame.iScene * (int)m_tRenInfo.fCY,
//	(int)m_tRenInfo.fCX, (int)m_tRenInfo.fCY, RGB(0, 255, 0));
// 화면에 찍히는 크기, 이미지에서 불러올 크기


//m_hPrev = (HBRUSH)SelectObject(hDC, m_hBrush);
//Rectangle(hDC, 0, 496, 800, 600);
//SelectObject(hDC, m_hPrev);
//
//GdiTransparentBlt(hDC, (WINCX - 232 * 3) / 2, WINCY - 28 * 3 - 10, 232 * 3, 28 * 3,
//	hUIMemDC, 3, 3,
//	232, 28, RGB(51, 200, 150));

//CSoundMgr::GetInstance()->PlayBGM(L"Intro.wav");
//CSoundMgr::GetInstance()->PlaySound(L"Shot.wav", CSoundMgr::EFFECT);
//CSoundMgr::GetInstance()->StopAll();
//CSoundMgr::GetInstance()->StopSound(CSoundMgr::EFFECT);

