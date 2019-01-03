#pragma once

#include "..\..\..\stdafx.h"
#include "..\..\Singleton.hpp"

class BackBuffer : public Singleton<BackBuffer>{

	DECLARE_SINGLETON(BackBuffer)

public:
	bool Init(const HDC& hDC);
	void Update();
	bool DrawSet(const HDC& hDC);
	bool DrawEnd();


public:
	//bool SetLoadBit();
	HDC&&			AllocationCompatibleDC();
	const HDC&	GetMemDC() const;
	const HDC&	GetDrawDC() const;
	const HDC&	GetBlendDC() const;


private:
	HDC				m_hMemDC;		//Main DC�� �׸� ������ ����ִ� DC
	HDC				m_hDrawDC;		//Mem DC�� ������ ������� DC
	HDC				m_hBlendDC;		//AlphaBlending�� DC
	HBITMAP		m_hBit;			//Mem DC�� ������ Bitmap �ڵ�
	HBITMAP		m_hOldBit;


};