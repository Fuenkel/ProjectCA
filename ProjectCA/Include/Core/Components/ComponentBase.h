#pragma once

/*
	NOTE:
		������Ʈ���� ��ӹ��� �ֻ��� �߻�Ŭ���� ����
*/

#include "..\..\..\stdafx.h"
#include "Message\ComponentMessage.h"

class CObject;

class ComponentBase {

public:
	ComponentBase() = default;
	virtual ~ComponentBase() { };

	
public:
	//virtual bool Init(CActor* pOwner, const Types::tstring& strTag) = 0;
	virtual void Init() = 0;
	virtual void Update(double dDeltaTime) = 0;
	//virtual void OnMessage(ComponentMessage msg);
	virtual void LateUpdate(double dDeltaTime) = 0;

public:
	CObject* const GetOwner() { return m_pOwner; }
	void SetOwner(CObject* pOwner) { m_pOwner = pOwner; }
	const Types::tstring& GetComponentTag() const { return m_strComponentTag; }
	void SetComponentName(const Types::tstring& tag) { m_strComponentTag = tag; }


protected:
	Types::tstring		m_strComponentTag;
	CObject*				m_pOwner;

};