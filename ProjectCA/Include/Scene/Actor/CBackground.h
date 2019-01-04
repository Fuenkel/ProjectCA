#pragma once

#include "..\..\..\stdafx.h"
#include "..\CEntity.h"

//NOTE: ����� �׸��� ��ɵ��� ������ Class.
//			MainCamera�� �̵��ӵ��� ���� ��ũ����.

class CSprite;
class CScene;

class CBackground : public CEntity {

public:
	CBackground();
	virtual ~CBackground();


public:
	virtual bool PostInit(const ENTITY_DATA& data, CScene* pScene);
	virtual void Update(double dDeltaTIme) override;
	virtual void Render(const HDC& hDC) override;


public:
	bool SetBackgroundImage(const TSTRING& strImageName);
	void SetStatic(bool bStatic);
	void SetScrollSpeed(float fSpeed);

public:
	bool IsStatic();


private:
	bool							m_bStatic;						//�����̴� ����ΰ� �����ִ� ����ΰ�
	float							m_fScrollSpeed;
	UINT							m_iBackgroundWidth;
	UINT							m_iBackgroundHeight;


};