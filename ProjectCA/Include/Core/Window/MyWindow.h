#pragma once

/*
NOTE:
	���� ������ �����ϰ� �� Window�鿡 ���� ������ �⺻Class
	Init() �޼ҵ带 �̿��ؼ��� �ʱ�ȭ �����ϰ� ����.
	MainWindow�� ������ ���� �� Window���� Class���� �ݵ�� �� Ŭ������ ��ӹ޾Ƽ� �ۼ�.
*/

#include "..\..\..\stdafx.h"


class MyWindow {

public:
	MyWindow() { };
	virtual ~MyWindow();


public:
	virtual bool Init(HINSTANCE hInstance, UINT iWidth, UINT iHeight);
	virtual void Update(const float fDeltaTime);
	virtual void Render(const float fDeltaTime);


public:
	void SetWndSize(UINT iWidth, UINT iHeight);
	bool SetVisible(HWND hWnd, BOOL bIsVisible);
	

protected:
	void DeadtimeLogic();
	bool CreateMyWindow(const Types::tstring& wndClassName,
		const Types::tstring& wndName, BOOL bIsVisible);
	UINT MessageLoop();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //���� �޼ҵ��̱� ������ virtualŰ����� ���� �Ⱥ���.



protected:
	WNDCLASS			m_WndClass;
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;
	HDC					m_hDC;
	UINT					m_iWidth;
	UINT					m_iHeight;


protected:
	//class CSceneManager*			m_pSceneManager;



};