#include "pch.h"
#include "Trigonometric.h"

/*
 * Creator : Choi HyoSeok (goto co[kr] Chaos)
 * Phone : 010-7121-6633
 * Copyright 2022. Chaos. all rights reserved.
 *
 * Data(Init) : 2022-1021_2131
 *
 * program subject :
 * 		1. 커스텀화 시킨 삼각함수 클래스 dll
 *
 * require Args :
 * 		1. 변경 점이 시작 될 값(x축)
 *		2. 같은 x축에서 위 또는 아래 값을 정하는 부울변수
 */

#define MY_RADIANS pi<float>() / 180.0f

namespace Trigonometric_Library
{
    // template <typename T, typename V>
    Trigonometric::Trigonometric() : m_Cust_Start_Trans_Point(0), m_bTopOverPass_Priority(true)
    {
    }

    // template <typename T, typename V>
    Trigonometric::Trigonometric(float fStartTransPoint, bool bTopOverPassPriority)
    {
        Trigonometric();

        SetStartTransPoint(fStartTransPoint);

        SetTopOverPassPriority(bTopOverPassPriority);
    }

    Trigonometric::~Trigonometric()
    {
    }

    void Trigonometric::SetStartTransPoint(float fStartTransPoint)
    {
        if (fStartTransPoint > MAX_START_TRANS_POINT) {
            fStartTransPoint = MAX_START_TRANS_POINT;
        }
        else if (fStartTransPoint < MIN_START_TRANS_POINT) {
            fStartTransPoint = MIN_START_TRANS_POINT;
        }

        m_Cust_Start_Trans_Point = fStartTransPoint;
    }

    void Trigonometric::SetTopOverPassPriority(bool bTopOverPassPriority)
    {
        m_bTopOverPass_Priority = bTopOverPassPriority;
    }

    float Trigonometric::GetStartTransPoint()
    {
        return m_Cust_Start_Trans_Point;
    }

    bool Trigonometric::GetTopOverPassPriority()
    {
        return m_bTopOverPass_Priority;
    }

    vec2 Trigonometric::Sin2Df(float theta) {
        float outVal = 0.0f;
        float radianVal;

        radianVal = theta * MY_RADIANS;

        outVal = sinf(radianVal);

        return vec2(radianVal, outVal);
    }

    vec2 Trigonometric::Cos2Df(float theta)
    {
        float outVal = 0.0f;
        float radianVal;

        radianVal = theta * MY_RADIANS;

        outVal = cosf(radianVal);

        return vec2(radianVal, outVal);
    }

    // template<typename T, typename V>
    vec2 Trigonometric::Tan2Df(float theta)
    {
        float fOutVal = 0.0f;
        float fRadianVal;
        float fRatio;
        float fSinThetaAdd;
        float fModVal1 = 0.0f;
        float fModVal2 = 0.0f;

        fRadianVal = theta * MY_RADIANS;

        fRatio = 90.0f / fmodf(90.0f - m_Cust_Start_Trans_Point, 90.0f);
        if (theta >= 0.0f) {
            fModVal1 = theta != 0.0f && fmodf(theta, 90.0f) == 0.0f ? 90.0f : fmodf(theta, 90.0f);
            fModVal2 = theta != 0.0f && fmodf(theta, 180.0f) == 0.0f ? 180.0f : fmodf(theta, 180.0f);

            if (m_bTopOverPass_Priority) {
                if (fModVal1 > m_Cust_Start_Trans_Point && fModVal1 <= 90.0f && fModVal2 != 180.0f && ((int)abs(floorf(theta / 90.0f)) % 2 == 0 || fModVal1 == 90.0f)) {
                    fOutVal = tanf(m_Cust_Start_Trans_Point * MY_RADIANS);        // 기존의 제한된 tan 값

                    // 무한대의 tan 값 대신 sin 값 0 ~ 90 도의 일정 비율로 값을 넣어줌
                    fSinThetaAdd = (fModVal1 - m_Cust_Start_Trans_Point) * fRatio;
                    fOutVal += sinf(fSinThetaAdd * MY_RADIANS);
                }
                else if (fModVal2 > 90.0f && fModVal2 < (180.0f - m_Cust_Start_Trans_Point) && (int)abs(floorf(theta / 90.0f)) % 2 == 1) {
                    fOutVal = tanf(-m_Cust_Start_Trans_Point * MY_RADIANS);

                    // 무한대의 tan 값 대신 sin 값 -90 ~ 0 도의 일정 비율로 값을 넣어줌
                    fSinThetaAdd = (fModVal2 - m_Cust_Start_Trans_Point) * fRatio;
                    fOutVal -= sinf(fSinThetaAdd * MY_RADIANS);
                }
                else {
                    fOutVal = tanf(fRadianVal);
                }
            }
            else {
                if (fModVal1 > m_Cust_Start_Trans_Point && fModVal1 < 90.0f && fModVal2 != 180.0f && (int)abs(floorf(theta / 90.0f)) % 2 == 0) {
                    fOutVal = tanf(m_Cust_Start_Trans_Point * MY_RADIANS);        // 기존의 제한된 tan 값

                    // 무한대의 tan 값 대신 sin 값 0 ~ 90 도의 일정 비율로 값을 넣어줌
                    fSinThetaAdd = (fModVal1 - m_Cust_Start_Trans_Point) * fRatio;
                    fOutVal += sinf(fSinThetaAdd * MY_RADIANS);
                }
                else if (fModVal2 >= 90.0f && fModVal2 < (180.0f - m_Cust_Start_Trans_Point) && ((int)abs(floorf(theta / 90.0f)) % 2 == 1 || fModVal1 == 90.0f)) {
                    fOutVal = tanf(-m_Cust_Start_Trans_Point * (float)MY_RADIANS);

                    // 무한대의 tan 값 대신 sin 값 -90 ~ 0 도의 일정 비율로 값을 넣어줌
                    fSinThetaAdd = (fModVal2 - m_Cust_Start_Trans_Point) * fRatio;
                    fOutVal -= sinf(fSinThetaAdd * MY_RADIANS);
                }
                else {
                    fOutVal = tanf(fRadianVal);
                }
            }
        }
        else {
            fModVal1 = theta != 0.0f && fmodf(theta, 90.0f) == -0.0f ? -90.0f : fmodf(theta, 90.0f);
            fModVal2 = theta != 0.0f && fmodf(theta, 180.0f) == -0.0f ? -180.0f : fmodf(theta, 180.0f);

            if (!m_bTopOverPass_Priority) {
                if (fModVal1 < -m_Cust_Start_Trans_Point && fModVal1 <= -m_Cust_Start_Trans_Point && fModVal2 != -180.0f && ((int)abs(floorf(theta / 90.0f)) % 2 == 1 || fModVal1 == -90.0f)) {
                    fOutVal = tanf(-m_Cust_Start_Trans_Point * (float)MY_RADIANS);        // 기존의 제한된 tan 값

                    // 무한대의 tan 값 대신 sin 값 0 ~ 90 도의 일정 비율로 값을 넣어줌
                    fSinThetaAdd = (fModVal1 + m_Cust_Start_Trans_Point) * fRatio;
                    fOutVal += sinf(fSinThetaAdd * MY_RADIANS);

                    if (fModVal1 == -90.0f) {
                        float aaa = 1.0f;
                    }
                }
                else if (fModVal2 < -90.0f && fModVal2 >(-180.0f + m_Cust_Start_Trans_Point) && (int)abs(floorf(theta / 90.0f)) % 2 == 0) {
                    fOutVal = tanf(m_Cust_Start_Trans_Point * (float)MY_RADIANS);

                    // 무한대의 tan 값 대신 sin 값 -90 ~ 0 도의 일정 비율로 값을 넣어줌
                    fSinThetaAdd = (fModVal2 + m_Cust_Start_Trans_Point) * fRatio;
                    fOutVal -= sinf(fSinThetaAdd * MY_RADIANS);

                    if (fModVal1 == -90.0f) {
                        float aaa = 1.0f;
                    }
                }
                else {
                    fOutVal = tanf(fRadianVal);
                }
            }
            else {
                if (fModVal2 <= -90.0f && fModVal2 > (-180.0f + m_Cust_Start_Trans_Point) && ((int)abs(floorf(theta / 90.0f)) % 2 == 0 || fModVal1 == -90.0f)) {
                    fOutVal = tanf(m_Cust_Start_Trans_Point * (float)MY_RADIANS);

                    // 무한대의 tan 값 대신 sin 값 -90 ~ 0 도의 일정 비율로 값을 넣어줌
                    fSinThetaAdd = (fModVal2 + m_Cust_Start_Trans_Point) * fRatio;
                    fOutVal -= sinf(fSinThetaAdd * MY_RADIANS);
                }
                else if (fModVal1 < -m_Cust_Start_Trans_Point && fModVal1 <= -m_Cust_Start_Trans_Point && fModVal2 != -180.0f && (int)abs(floorf(theta / 90.0f)) % 2 == 1) {
                    fOutVal = tanf(-m_Cust_Start_Trans_Point * (float)MY_RADIANS);        // 기존의 제한된 tan 값

                    // 무한대의 tan 값 대신 sin 값 0 ~ 90 도의 일정 비율로 값을 넣어줌
                    fSinThetaAdd = (fModVal1 + m_Cust_Start_Trans_Point) * fRatio;
                    fOutVal += sinf(fSinThetaAdd * MY_RADIANS);
                }
                else {
                    fOutVal = tanf(fRadianVal);
                }
            }
        }

        return vec2(fRadianVal, fOutVal);
    }
}
