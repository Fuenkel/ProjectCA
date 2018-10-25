#pragma once

/*
	NOTE:
		Enemy�� �ൿ ���ǿ� ���� AI������Ʈ.
		InputComponent�� �������̽��� ��ӹ޾Ƽ� �ۼ���.
*/

#include "..\..\..\stdafx.h"
#include "InputComponent.h"

using Delegater = std::function<void(std::weak_ptr<CActor> pActor)>;

class AIComponent : public InputComponent {

public:
	AIComponent();
	virtual ~AIComponent();


public:
	//virtual bool Init(CActor* pOwner, const Types::tstring& strTag = TEXT("InputComponent")) override;
	virtual void Init(){ }
	virtual void Update(double fDeltaTime) override;
	virtual void LateUpdate(double dDeltaTime) override;

public:
	Delegater SetDelegate(Delegater pDelegater);


private:
	void BehaviorUpdate();


private:
	Delegater m_pDelegate;

};