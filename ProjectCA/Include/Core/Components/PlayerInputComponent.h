#pragma once

#include "..\..\..\stdafx.h"
#include "InputComponent.h"

//TODO :	 InputManager�� �����ؼ� ����Ű ������ �� �ְԲ� ������.


class PlayerInputComponent : public InputComponent {

public:
	PlayerInputComponent() { }
	virtual ~PlayerInputComponent();

	
public:
	virtual bool Init(CActor* pOwner, const Types::tstring& strTag = TEXT("InputComponent")) override;
	virtual void Update(double fDeltaTime) override;


private:
	void KeyProcess();
	void JumpKeyProcess();


};