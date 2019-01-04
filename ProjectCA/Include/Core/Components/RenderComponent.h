#pragma once


#include "..\..\..\stdafx.h"
#include "ComponentBase.h"

//NOTE: Rendering�� ����ϴ� ������Ʈ.
//			Rendering�� ���� ��ǥ���� ���� ������ ����.

class RenderComponent : public ComponentBase {

public:
	enum RenderMode {
		RENDER_DEFAULT, RENDER_BLEND, RENDER_FADE_OUT, RENDER_FADE_IN
	};

public:
	RenderComponent();
	virtual ~RenderComponent();


public:
	virtual bool	PostInit(CEntity* pOwner, const TSTRING& strTag = TEXT("RenderComponent"));
	virtual void	Init() override;
	virtual void	Update(double dDeltaTime) override;
	virtual void	LateUpdate() override;
	virtual void	Draw(const HDC& hDC) = 0;


public:
	void SetRenderMode(RenderMode mode);
	void SetDrawWidth(UINT iWidth);
	void SetDrawHeight(UINT iHeight);
	void SetDrawWidthRatio(float fRatio);
	void SetDrawHeightRatio(float fRatio);
	void SetDrawSize(UINT iWidth, UINT iHeight);
	void SetExpansionRatio(float fRatio);
	void SetWidthPivotRatio(float fRatio);
	void SetHeightPivotRatio(float fRatio);
	void SetPivotRatio(float fWidthRatio, float fHeightRatio);
	void SetAlpha(int iAlpha);
	void MovePivot(float fx, float fy);



public:
	const POSITION& GetDrawPivot() const;
	

public:
	void SwitchBlending();


protected:
	RenderMode			m_RenderMode;
	HDC						m_hRenderDC;		//Backbuffer�� m_hMemDC�� ���� Compatible DC
	HDC						m_hBlendingDC;	//Backbuffer�� m_hBlendingDC�� ���� Compatible DC
	UINT						m_iDrawWidth;
	UINT						m_iDrawHeight;
	float						m_fWidthExpansionRatio;
	float						m_fHeightExpansionRatio;
	float						m_fWidthPivotRatio;
	float						m_fHeightPivotRatio;
	POSITION				m_DrawPivot;		
	BLENDFUNCTION		m_BlendFunction;


private:


};