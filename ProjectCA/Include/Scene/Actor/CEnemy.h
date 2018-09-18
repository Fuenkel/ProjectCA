#pragma once

/*
	NOTE:
		Enemy ��ü���� ��ӹް� �� Class
		
*/


#include "..\..\..\stdafx.h"
#include "CActor.h"



class CEnemy : public CActor {

public:
	CEnemy();
	virtual ~CEnemy();


public:
	virtual bool Init(const Types::ActorData&) override;
	virtual void Update(float fDeltaTime) override;
	virtual void Render(const HDC& hDC) override;


protected:
	virtual void ActorBehavior() = 0;


protected:




};