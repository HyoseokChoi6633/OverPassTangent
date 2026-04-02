#pragma once

/*
 * Creator : Choi HyoSeok (goto co[kr] Chaos)
 * Phone : 010-7121-6633
 * Copyright 2022. Chaos. all rights reserved.
 *
 * Data(Init)   : 2025-0714_1615 (초기설정)
 *
 * program subject :
 * 		1. 커스텀화 시킨 삼각함수 클래스 dll을 확인해 주는 뷰어 프로그램에서 화면을 그려주는 객체 생성 클래스
 *      2. 더블 버퍼링 화면 출력 적용
 *      3. 삼각함수 출력 코드를 class 로 작성
 *
 * require Args :
 *
 */


#ifndef CMYDRAWTRIGONOMETRIC_H
#define CMYDRAWTRIGONOMETRIC_H
#include "Trigonometric.h"
#include "SSGdi.h"          // 스마트 포인터로 구현된 gdi 객체 선언 헤더
#include <tchar.h>

using namespace Trigonometric_Library;

#endif // !CMYDRAWTRIGONOMETRIC_H



class CMyDrawTrigonometric
{
public:
    CMyDrawTrigonometric();         // 생성자
    ~CMyDrawTrigonometric();        // 소멸자

    // WM_CREATE 시 사용
    bool OnCreate(HWND hWnd, float fStartTransPoint, float bTopOverPassPriority);

    void OnLButtonDown();               // WM_LBUTTONDOWN 시 사용
    void OnMouseWheel(WPARAM wParam);   // WM_MOUSEWHEEL 시 사용
    void OnSize(LPARAM lParam);         // WM_SIZE 시 사용
    void OnPaint(HDC hDC);              // WM_PAINT 시 사용
    void clear();                       // WM_DESTROY 시 사용

    // 색 인덱스 용 열거형 선언
    typedef enum _enClrDef {
        RED = 0,
        GREEN,
        BLUE
    } enClrDef;

    // 색 상에 대한 컬러값 상수 지정 (빨강, 녹색, 파랑)
    const COLORREF m_arcclrRGB[3] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) };

    // 화면 출력시 메시지를 표시하기 위한 상수
    LPCTSTR lpctMsg = _T("왼쪽 마우스 클릭과 휠을 조작해 보세요(화면 출력시 더블 버퍼링 적용)");

private:
    // 커스텀 삼각함수 호출 객체 선언(dll의 내용)
    Trigonometric m_objCust_tri;

    HWND m_hWnd;        // 그림을 그릴 윈도우 헨들 멤버 변수

    RECT m_rtClient;    // OnSize() 에서 클라이언트 크기를 담을 RECT 멤버 변수
    
    UniqueHBitmap m_hBitmapBCK;     // 스마트 포인터로 선언된 HBITMAP 타입의 멤버 변수

    UniqueHPen m_harClrPen[3];      // 스마트 포인터로 선언된 HPEN 타입의 멤버 변수
};
