#pragma once

/*
	NOTE:
		���� ���� Frame �� ���õ� ��� �ǽ��ϴ� Class
		�� �� �̻� ������ �ʿ䰡 �����Ƿ� Singleton��ü�� �ۼ�
*/


#include "..\..\stdafx.h"
#include	"..\Singleton.hpp"


class Timer : public Singleton<Timer>{

	DECLARE_SINGLETON(Timer)

public:
	bool Init();
	void Update();


public:
	float GetDeltaTime() const { return m_fDeltaTime; }
	float GetFPS()	const { return m_fFPS; }


private:
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;
	float					m_fDeltaTime;
	float					m_fFPS;
	float					m_fFPSTime;
	float					m_iFrameMax;
	float					m_iFrame;



};