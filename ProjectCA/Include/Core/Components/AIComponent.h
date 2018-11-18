#pragma once

/*
	NOTE:
		Enemy�� �ൿ ���ǿ� ���� AI������Ʈ.
		InputComponent�� �������̽��� ��ӹ޾Ƽ� �ۼ���.
*/

#include "..\..\..\stdafx.h"
#include "InputComponent.h"

using Callback = std::function<void(CActor* pActor)>;

class AIComponent : public InputComponent {

public:
	AIComponent();
	virtual ~AIComponent();


public:
	virtual void Init();
	virtual void Update(double fDeltaTime) override;
	virtual void LateUpdate(double dDeltaTime) override;

public:
	Callback SetDelegate(Callback pDelegater);


private:
	void BehaviorUpdate();


private:
	Callback m_pDelegate;

};