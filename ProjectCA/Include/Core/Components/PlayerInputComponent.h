#pragma once

#include "..\..\..\stdafx.h"
#include "InputComponent.h"

//TODO :	 InputManager�� �����ؼ� ����Ű ������ �� �ְԲ� ������.



class PlayerInputComponent : public InputComponent {

public:
	PlayerInputComponent() { }
	virtual ~PlayerInputComponent();

	
public:
	virtual bool PostInit(CEntity* pOwner, const Types::tstring& strTag = TEXT("InputComponent")) override;
	virtual void Init();
	virtual void Update(double fDeltaTime) override;
	virtual void LateUpdate() override;


private:
	//void UpdateKeyDown();
	void KeyProcess();


private:
	class CInputManager*		m_pInputManager;


};