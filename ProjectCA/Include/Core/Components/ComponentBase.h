#pragma once

/*
	NOTE:
		������Ʈ���� ��ӹ��� �ֻ��� �߻�Ŭ���� ����
*/

#include "..\..\..\stdafx.h"
#include "Message\ComponentMessage.h"

class CActor;

class ComponentBase {

public:
	ComponentBase() = default;
	virtual ~ComponentBase() { };

	
public:
	virtual void Init() = 0;
	virtual void Update(float fDeltaTime) = 0;
	//virtual void OnMessage(ComponentMessage msg);


public:
	inline CActor* GetOwner() { return m_pOwner; }
	inline void SetOwner(CActor* owner) { m_pOwner = owner; }
	inline const Types::tstring& GetComponentTag() const { return m_strComponentTag; }
	inline void SetComponentName(const Types::tstring& tag) { m_strComponentTag = tag; }


protected:
	//Types::Point				m_point;
	Types::tstring			m_strComponentTag;
	CActor*					m_pOwner;

};