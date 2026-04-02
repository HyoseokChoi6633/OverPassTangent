#include "CMyDrawTrigonometric.h"

CMyDrawTrigonometric::CMyDrawTrigonometric()
{
}

CMyDrawTrigonometric::~CMyDrawTrigonometric()
{
    clear();
}

bool CMyDrawTrigonometric::OnCreate(HWND hWnd, float fStartTransPoint, float bTopOverPassPriority)
{
    bool bRetVal = true;
    int i;

    m_hWnd = hWnd;

    // Dll 로 만든 탄젠트 무한 제한 설정값 입력
    m_objCust_tri.SetStartTransPoint(fStartTransPoint);
    m_objCust_tri.SetTopOverPassPriority(bTopOverPassPriority);

    // Red, Green, Blue 펜 생성
    for (i = 0; i <= BLUE; i++) {
        m_harClrPen[i].reset(CreatePen(PS_SOLID, 2, m_arcclrRGB[i]));

        if (!m_harClrPen[i]) {
            bRetVal = false;
            break;
        }
    }

    return bRetVal;
}

void CMyDrawTrigonometric::OnLButtonDown()
{
    m_objCust_tri.SetTopOverPassPriority(!m_objCust_tri.GetTopOverPassPriority());
    InvalidateRect(m_hWnd, nullptr, false);
}

void CMyDrawTrigonometric::OnMouseWheel(WPARAM wParam)
{
    float fTriVal;

    fTriVal = m_objCust_tri.GetStartTransPoint();
    m_objCust_tri.SetStartTransPoint(fTriVal + GET_WHEEL_DELTA_WPARAM(wParam) / 100.0f);

    if (fTriVal != m_objCust_tri.GetStartTransPoint()) {
        InvalidateRect(m_hWnd, nullptr, false);
    }
}

void CMyDrawTrigonometric::OnSize(LPARAM lParam)
{
    int i;
    vec2 pt;

    // WM_SIZE 메시지 처리시
        // 사인과 코사인의 그래프를 배경으로 미리 그린다.
    SetRect(&m_rtClient, 0, 0, LOWORD(lParam), HIWORD(lParam));

    UniqueHdc hDC;
    hDC.reset(GetDC(m_hWnd));

    m_hBitmapBCK.reset(CreateCompatibleBitmap(hDC.get(), m_rtClient.right - m_rtClient.left, m_rtClient.bottom - m_rtClient.top));

    UniqueHdc hMemDCBck;
    hMemDCBck.reset(CreateCompatibleDC(hDC.get()));
    hDC.reset();

    GdiObjectSelector gdiBitmapSelector(hMemDCBck.get(), m_hBitmapBCK.get());
    FillRect(hMemDCBck.get(), &m_rtClient, (HBRUSH)(COLOR_WINDOW + 1));

    // 사용법 메세지
    TextOut(hMemDCBck.get(), 0, 0, lpctMsg, _tcslen(lpctMsg));

    // Flip Y axis
    SetMapMode(hMemDCBck.get(), MM_ANISOTROPIC);
    SetViewportOrgEx(hMemDCBck.get(), (m_rtClient.right - m_rtClient.left) / 2, (m_rtClient.bottom - m_rtClient.top) / 2, nullptr);
    SetWindowExtEx(hMemDCBck.get(), m_rtClient.bottom, m_rtClient.right, nullptr);
    SetViewportExtEx(hMemDCBck.get(), m_rtClient.bottom, - m_rtClient.right, nullptr);

    // 십자 표시
    MoveToEx(hMemDCBck.get(), -((m_rtClient.right - m_rtClient.left) / 2), 0, NULL);
    LineTo(hMemDCBck.get(), (m_rtClient.right - m_rtClient.left) / 2, 0);

    MoveToEx(hMemDCBck.get(), 0, -(m_rtClient.bottom - m_rtClient.top) / 2, NULL);
    LineTo(hMemDCBck.get(), 0, (m_rtClient.bottom - m_rtClient.top) / 2);

    // 사인파
    GdiObjectSelector gdiPenSelector(hMemDCBck.get(), m_harClrPen[RED].get());
    for (i = -360; i <= 360; i++) {
        pt = m_objCust_tri.Sin2Df(i);
        MoveToEx(hMemDCBck.get(), pt.x * 100, pt.y * 150, NULL);
        pt = m_objCust_tri.Sin2Df(i + 1);
        LineTo(hMemDCBck.get(), pt.x * 100, pt.y * 150);
    }

    // 코사인파
    gdiPenSelector.reset(m_harClrPen[GREEN].get());
    for (int i = -360; i <= 360; i++) {
        pt = m_objCust_tri.Cos2Df(i);
        MoveToEx(hMemDCBck.get(), pt.x * 100, pt.y * 150, NULL);
        pt = m_objCust_tri.Cos2Df(i + 1);
        LineTo(hMemDCBck.get(), pt.x * 100, pt.y * 150);
    }

    gdiBitmapSelector.reset();
    hMemDCBck.reset();

    InvalidateRect(m_hWnd, nullptr, false);
}

void CMyDrawTrigonometric::OnPaint(HDC hDC)
{
    UniqueHdc hMemDC;
    BITMAP bm;

    UniqueHBitmap hBitmap;

    vec2 pt;

    // 커스텀 탄젠트 곡선만 그리기 위한 메모리 dc 생성
    hMemDC.reset(CreateCompatibleDC(hDC));
    GetObject(m_hBitmapBCK.get(), sizeof(bm), &bm);

    hBitmap.reset(CreateCompatibleBitmap(hDC, bm.bmWidth, bm.bmHeight));

    GdiObjectSelector gdiBitmapSelector(hMemDC.get(), hBitmap.get());

    // WM_SIZE 에서 그려진 사인과 코사인의 비트맵 배경을 BitBlt로 이미지 복사
    UniqueHdc hMemDCBck;
    hMemDCBck.reset(CreateCompatibleDC(hDC));
    GdiObjectSelector gdiBitmapBckSelector(hMemDCBck.get(), m_hBitmapBCK.get());

    BitBlt(hMemDC.get(), 0, 0, (m_rtClient.right - m_rtClient.left), (m_rtClient.bottom - m_rtClient.top), hMemDCBck.get(), 0, 0, SRCCOPY);

    gdiBitmapBckSelector.reset();
    hMemDCBck.reset();
    // WM_SIZE 에서 그려진 사인과 코사인의 비트맵 배경을 BitBlt로 이미지 복사 끝

    // 커스텀 탄젠트를 그리기 위해 메모리 dc 좌표계를 클라이언트 영역 중심으로 변경
    // Flip Y axis
    SetMapMode(hMemDC.get(), MM_ANISOTROPIC);
    SetViewportOrgEx(hMemDC.get(), (m_rtClient.right - m_rtClient.left) / 2, (m_rtClient.bottom - m_rtClient.top) / 2, NULL);
    SetWindowExtEx(hMemDC.get(), m_rtClient.bottom, m_rtClient.right, NULL);
    SetViewportExtEx(hMemDC.get(), m_rtClient.bottom, -m_rtClient.right, NULL);

    // 화면 출력 dc의 좌표계 설정
    // Required for both contexts
    SetMapMode(hDC, MM_ANISOTROPIC);
    SetViewportOrgEx(hDC, 0, m_rtClient.bottom, NULL);
    SetWindowExtEx(hDC, m_rtClient.bottom, m_rtClient.right, NULL);
    SetViewportExtEx(hDC, m_rtClient.bottom, -m_rtClient.right, NULL);

    // 커스텀 탄젠트파
    GdiObjectSelector gdiPenSelector(hMemDC.get(), m_harClrPen[BLUE].get());

    for (int i = -360; i <= 360; i++) {
        pt = m_objCust_tri.Tan2Df(i);
        MoveToEx(hMemDC.get(), pt.x * 100, pt.y * 50, NULL);

        if (i % 90 == 0) {
            Ellipse(hMemDC.get(), pt.x * 100 - 5, pt.y * 50 - 5, pt.x * 100 + 5, pt.y * 50 + 5);
        }

        pt = m_objCust_tri.Tan2Df(i + 1);
        LineTo(hMemDC.get(), pt.x * 100, pt.y * 50);
    }

    gdiPenSelector.reset();

    // 메모리 dc의 내용을 화면에 출력
    BitBlt(hDC, 0, 0, (m_rtClient.right - m_rtClient.left), (m_rtClient.bottom - m_rtClient.top), hMemDC.get(), -(m_rtClient.right - m_rtClient.left) / 2, -(m_rtClient.bottom - m_rtClient.top) / 2, SRCCOPY);

    gdiBitmapSelector.reset();
    hBitmap.reset();
    hMemDC.reset();
}

void CMyDrawTrigonometric::clear()
{
    int i;
    m_hBitmapBCK.reset();

    for (i = 0; i <= BLUE; i++) {
        m_harClrPen[i].reset();
    }
}
