#pragma once

#include "..\..\..\stdafx.h"
#include "..\CObject.h"

//NOTE: ���� �� Ground, Block �� ��ü���� ��ӹް� �� Class

class CProb : public CObject {

public:
	CProb();
	virtual ~CProb();


public:
	virtual bool PostInit(const OBJECT_DATA&, CScene*) override;

};