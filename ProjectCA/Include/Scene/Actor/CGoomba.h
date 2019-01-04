#pragma once

#include "..\..\..\stdafx.h"
#include "CEnemy.h"

//NOTE: CEnemy�� ��ӹ޾� �ۼ��� Ŭ����.
//			Goomba�� ������.

class CGoomba : public CEnemy
{

public:
	CGoomba();
	virtual ~CGoomba();


public:
	virtual bool PostInit(const Types::ActorData&, CGameScene*) override;
	virtual void Init() override;
	virtual void Update(double dDeltaTime);
	virtual void Render(const HDC& hDC);


private:
	virtual void ActorBehavior(double dDeltaTime) override;
	virtual void DeadProcess(double dDeltaTime) override;
	virtual void HandlingEvent(EVENT_TYPE type) override;


};