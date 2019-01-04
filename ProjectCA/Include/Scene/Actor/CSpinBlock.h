#pragma once

#include "..\..\..\stdafx.h"
#include "CProb.h"

//NOTE: SpinBlock�� ������ Ŭ����.

class CSpinBlock : public CProb
{
public:
	CSpinBlock();
	virtual ~CSpinBlock();


public:
	virtual bool PostInit(const OBJECT_DATA&, CScene*) override;
	virtual void Init() override;
	virtual void Update(double dDeltaTime) override;
	virtual void Render(const HDC& hDC) override;


private:
	void BlockBehavior(double dDeltaTime);
	virtual void HandlingEvent(EVENT_TYPE type);


private:
	double m_dTimeElapsed;


};
