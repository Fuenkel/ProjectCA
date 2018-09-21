#pragma once

/*
	NOTE:
		���� �� �������� �Է�ó���� ����ϴ� Manager Class

*/

#include "..\..\stdafx.h"
#include "..\Singleton.hpp"


class InputManager : public Singleton<InputManager> {

	DECLARE_SINGLETON(InputManager)

public:
	bool Init();
	void Update();
	

public:



private:
	void KeyProcess();



private:





};