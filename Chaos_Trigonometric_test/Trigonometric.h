#pragma once

/*
 * Creator : Choi HyoSeok (goto co[kr] Chaos)
 * Phone : 010-7121-6633
 * Copyright 2022. Chaos. all rights reserved.
 *
 * Data(Init) : 2022-1021_2131
 * Data(Second) : 2025-0714_1611
 *
 * program subject :
 * 		1. 커스텀화 시킨 삼각함수 클래스 dll
 *
 * require Args :
 * 		1. 변경 점이 시작 될 값(x축)
 *		2. 같은 x축에서 위 또는 아래 값을 정하는 부울변수
 * 
 * Second Strain(변형)
 *		1. class 이름에서 _Library 삭제
 *		2. 파일명에서도 _Library 삭제
 *			Trigonometric.h
 *			Trigonometric.cpp
 */

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
using namespace glm;


#ifdef TRIGONOMETRIC_EXPORTS
#define TRIGONOMETRIC_API __declspec(dllexport)
#else
#define TRIGONOMETRIC_API __declspec(dllimport)
#endif

namespace Trigonometric_Library
{
	class TRIGONOMETRIC_API Trigonometric
	{
	private:
		float m_Cust_Start_Trans_Point;		// 무한대로 빠지지 않고 재한한 수로 수렴을 하기위한 시작값
		bool m_bTopOverPass_Priority;		// x 위치의 최대값이나 최소값의 중복을 막기 위한 변수

	public:
		const int MAX_START_TRANS_POINT = 80;
		const int MIN_START_TRANS_POINT = 10;

	public:
		Trigonometric();			// 기본 생성자
		Trigonometric(float fStartTransPoint, bool bTopOverPassPriority);			// 기본 생성자
		~Trigonometric();

		void SetStartTransPoint(float fStartTransPoint);
		void SetTopOverPassPriority(bool bTopOverPassPriority);

		float GetStartTransPoint();
		bool GetTopOverPassPriority();

		vec2 Tan2Df(float theta);
		vec2 Sin2Df(float theta);
		vec2 Cos2Df(float theta);
	};
}
