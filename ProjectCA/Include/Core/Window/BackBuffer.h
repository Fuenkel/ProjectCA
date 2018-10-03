#pragma once

#include "..\..\..\stdafx.h"


class BackBuffer {

public:
	BackBuffer(const HDC& hDC);
	BackBuffer();
	~BackBuffer();


public:
	bool DrawSet(const HDC& hDC);
	bool DrawEnd();


public:
	//bool SetLoadBit();
	const HDC& GetMemDC() const { return m_hMemDC; }
	const HDC& GetDrawDC() const { return m_hDrawDC; }


private:
	HDC		m_hMemDC;		//Main DC�� �׸� ������ ����ִ� DC
	HDC		m_hDrawDC;		//Mem DC�� ������ ������� DC
	HBITMAP	m_hBit;			//Mem DC�� ������ Bitmap �ڵ�
	HBITMAP	m_hLoadBit;		
	HBITMAP	m_hOldBit;

};