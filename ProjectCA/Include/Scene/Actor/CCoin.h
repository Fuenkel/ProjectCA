#pragma once

#include "..\..\..\stdafx.h"
#include "CPickup.h"

//NOTE: CPickup�� ��ӹ޾� �ۼ��� Pickup Class.
//			������ ������.

class CCoin : public CPickup
{
public:
	CCoin();
	virtual ~CCoin();


public:
	virtual bool PostInit(const Types::ActorData& data, CGameScene* pScene) override;
	virtual void Init() override;
	virtual void Update(double dDeltaTime) override;
	virtual void Render(const HDC& hDC) override;




};