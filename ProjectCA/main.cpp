#include "stdafx.h"
#include "Include/Core/Window/MainWindow.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpszCmdLine, int nCmdShow) {

	//�ʿ���� �Ķ����
	UNREFERENCED_PARAMETER(hPreInstance);
	UNREFERENCED_PARAMETER(lpszCmdLine);

	if (!MainWindow::GetInstance()->Init(hInstance, MAX_WIDTH, MAX_HEIGHT)) {
		MessageBox(NULL, TEXT("WNDCLASS Init Failed"), TEXT("Error"), MB_ICONERROR | MB_OK);
		return 0;
	}

	UINT retValue = MainWindow::GetInstance()->MessageLoop();
	MessageBox(NULL, TEXT("Main ����"), TEXT("Info"), MB_ICONINFORMATION);

	MainWindow::Destroy();

	return retValue;

}