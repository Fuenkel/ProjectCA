#pragma once

#include "..\..\..\stdafx.h"
#include "InputComponent.h"

//TODO :	 InputManager�� �����ؼ� ����Ű ������ �� �ְԲ� ������.

struct KeyInfo {
	KeyInfo(const Types::tstring& strKeyname, SHORT iKeyCode, bool bPressed) 
		:m_strKeyName(strKeyname), m_iKeyKode(iKeyCode), m_bPressed(bPressed)
	{

	}

	Types::tstring	m_strKeyName;
	SHORT			m_iKeyKode;
	bool				m_bPressed;
};


class PlayerInputComponent : public InputComponent {

public:
	PlayerInputComponent() { }
	virtual ~PlayerInputComponent();

	
public:
	virtual bool Init(CActor* pOwner, const Types::tstring& strTag = TEXT("InputComponent")) override;
	virtual void Update(double fDeltaTime) override;


public:
	bool GetKeyDown(const Types::tstring& steKeyName);
	//bool GetKeyDown(const Types::tstring& steKeyName);


private:
	void UpdateKeyDown();
	void KeyProcess();


private:
	std::vector<KeyInfo>	m_keyInfoList;

};