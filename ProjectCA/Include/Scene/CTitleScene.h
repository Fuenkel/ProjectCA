#pragma once

#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CScene.h"

//NOTE: TitleScene ����

class CTitleScene : public CScene 
{

public:
	CTitleScene();
	virtual ~CTitleScene();


public:
	virtual bool Init();
	virtual void Update(double dDeltaTime);
	virtual void Render(const HDC& hDC);


};