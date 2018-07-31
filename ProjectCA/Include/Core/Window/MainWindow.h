#pragma once

/*
	NOTE:
		���� �� MainWindow�� ������ ������ Class.
		�� Class�� ������ �ٸ� Window���� MyWindow Class�� ��ӹ޾Ƽ� �ۼ��ؾ���.
		���α׷��� �����ϴ� ���� Instance�� 1������ �����ϱ� ���� Singleton Template Class�� ���
*/

#include "..\..\..\stdafx.h"
#include "..\..\Singleton.hpp"


class MainWindow : public Singleton<MainWindow> {

	DECLARE_SINGLETON(MainWindow)
	
public:
	bool Init(HINSTANCE hInstance, UINT iWidth, UINT iHeight);
	void Update();
	void Render();


public:
	void SetWndSize(UINT iWidth, UINT iHeight);
	bool SetVisible(HWND hWnd, BOOL bIsVisible);
	UINT MessageLoop();


private:
	bool CreateMyWindow(const Types::tstring& wndClassName,
		const Types::tstring& wndName, BOOL bIsVisible);


private:
	void DeadtimeLogic();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 
	

private:
	WNDCLASS			m_WndClass;
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;
	HDC					m_hDC;
	UINT					m_iWidth;
	UINT					m_iHeight;


private:
	class CSceneManager*	m_pSceneManager;
	class Timer*					m_pTimer;

};