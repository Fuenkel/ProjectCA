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
	//virtual bool Init(CActor* pOwner, const Types::tstring& strTag) = 0;
	virtual void Update(double fDeltaTime) = 0;
	//virtual void OnMessage(ComponentMessage msg);


public:
	inline std::weak_ptr<CActor> GetOwner() { return m_pOwner; }
	inline void SetOwner(std::shared_ptr<CActor> owner) { m_pOwner = owner; }
	inline const Types::tstring& GetComponentTag() const { return m_strComponentTag; }
	inline void SetComponentName(const Types::tstring& tag) { m_strComponentTag = tag; }


protected:
	//Types::Point				m_point;
	Types::tstring						m_strComponentTag;
	std::shared_ptr<CActor>			m_pOwner;

};