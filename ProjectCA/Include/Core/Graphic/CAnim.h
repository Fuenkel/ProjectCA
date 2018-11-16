#pragma once

#include "..\..\..\stdafx.h"

class CSprite;
class CActor;

typedef std::vector<std::weak_ptr<CSprite>> WeakSpriteTable;

class CAnim {


public:
	CAnim();
	~CAnim();


public:
	bool Init(const TSTRING& strSpriteName, UINT iWidth, UINT iHeight,
		double dPlayTime, bool bLoop, const TSTRING& strAnimTag = TEXT("Default"), bool bInterrupt = true);
	void Update(double dDeltaTIme);
	void Draw(const HDC& hDC, const HDC& hMemDC, const POSITION& point);


public:
	void SetCanInterrupt(bool bInterrupt);
	void SetReadyToChange(bool bReady);
	bool SetSprite(const Types::tstring& strSpriteName);
	bool SetTotalPlayTime(double dTime);
	bool SetPlaySpeed(double dSpeed);
	void SetDrawingWidth(UINT iWidth);
	void SetDrawingHeight(UINT iHeight);


public:
	bool						IsCanInterrupt() const;
	bool						IsReadyToChange() const;
	UINT						GetDrawWidth() const;
	UINT						GetDrawHeight() const;
	const Types::tstring	GetAnimTag() const;


public:
	void ClearEleapsedTime();


private:
	void DrawAnimation(const HDC& hDC, const HDC& hMemDC, const Types::Point& point);


private:
	bool							m_bInterrupt;
	bool							m_bReadyToChange;
	bool							m_bLoop;
	UINT							m_iCurFrame;
	UINT							m_iMaxFrame;
	UINT							m_iDrawWidth;
	UINT							m_iDrawHeight;
	COLORREF					m_colorRef;
	double						m_dPlaySectionLength;
	double						m_dPlayTime;		//�� ������ ���
	double						m_dPlaySpeed;
	double						m_dTimeElapsed;
	Types::tstring				m_strAnimTag;
	WeakSpriteTable			m_weakSpriteTable;
	std::weak_ptr<CSprite>	m_pWeakSprite;

};