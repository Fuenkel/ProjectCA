#pragma once

#include "..\..\..\stdafx.h"
#include "CProp.h"

//NOTE: Pipe�� ������ Class
//			������ �� Width, Height���� Ÿ���� ������ ���� ���̾�� ��.

class CPipe : public CProp
{
	const int PIPE_UNIT_WIDTH		= SPRITE_WIDTH * 2.5f;
	const int PIPE_UNIT_HEIGHT	= SPRITE_HEIGHT * 0.5f * 2.5f;

	//Ÿ�� ��
	enum PipeInfo {
		PIPE_HEAD = 0, PIPE_BODY
	};

public:
	//������ Pipe Head�� �����ִ� ���� ����
	enum PipeType {
		PIPE_RIGHT, PIPE_LEFT, PIPE_TOP, PIPE_BOT
	};


public:
	CPipe();
	virtual ~CPipe();


public:
	virtual bool PostInit(const OBJECT_DATA&, CScene*) override;
	virtual void Init() override;
	virtual void Update(double dDeltaTime) override;
	virtual void Render(const HDC& hDC) override;
	virtual void LateUpdate() override;


public:
	void SetPipeSize(int iSize);


private:
	void GeneratePipe(UINT iHeight);


private:
	PipeType			m_PipeType;
	typedef std::vector<std::weak_ptr<class CSprite>> PipeImageList;
	PipeImageList	m_PipeImageList;


};