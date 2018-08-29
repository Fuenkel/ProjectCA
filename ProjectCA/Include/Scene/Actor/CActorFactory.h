#pragma once

/*
	NOTE:
		Actor�� �����ϱ� ���� ActorFactory �޼ҵ�
		Actor�� �����ϱ� ���ؼ��� �ݵ�� ActorFactory Class�� ����ؾ���
		Actor�� Component�� ������ ���
*/

#include "..\..\..\stdafx.h"
#include "CActor.h"
#include "..\..\Core\Components\ComponentBase.h"

typedef std::shared_ptr<CActor>				ActorPtr;
typedef std::shared_ptr<ComponentBase>	ComponentPtr;


class CActorFactory
{
	friend CActor;

public:
	CActorFactory();
	~CActorFactory();


public:
	static ActorPtr	CreateActor(Types::ObjectData&);
	template<typename ComponentType>
	ComponentPtr CreateComponent(const Types::tstring& strTag) {
		ComponentPtr pComponent = ComponentPtr();
		ComponentType pTemp = std::tr1::static_pointer_cast<ComponentType>
		

	}

private:
	static ActorID		m_iLastActorID;



};
