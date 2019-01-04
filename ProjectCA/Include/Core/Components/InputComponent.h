#pragma once

#include "..\..\..\stdafx.h"
#include "ComponentBase.h"

//NOTE : InputComponent���� �߻�Ŭ����

class CActor;

class InputComponent :public ComponentBase {

public:
	InputComponent();
	virtual ~InputComponent() = default;

	
public:
	virtual bool PostInit(CEntity* pOwner, const Types::tstring& strTag = TEXT("InputComponent"));
	virtual void Update(double fDeltaTime) = 0;
	virtual void LateUpdate() = 0;


};