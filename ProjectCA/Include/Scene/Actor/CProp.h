#pragma once

#include "..\..\..\stdafx.h"
#include "..\CObject.h"

//NOTE: ���� �� Ground, Block �� ��ü���� ��ӹް� �� Class

class CProp : public CObject {

public:
	CProp();
	virtual ~CProp();


public:
	virtual bool PostInit(const OBJECT_DATA& data, CScene* pScene) override;

};