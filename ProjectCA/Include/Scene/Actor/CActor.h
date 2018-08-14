#pragma once

/*
	NOTE:
		���� �� ��� Actor���� �⺻ Class ����.
		CWorld��ü������ ���������ϰ� ����.
*/

#include "..\..\..\stdafx.h"


typedef unsigned long ActorID;

class CActor {
	//Layer, World Class�� Actor�� ����, �ı��� ������.
	friend class CWorld;
	friend class CLayer;

private:
	CActor();
	virtual ~CActor() { };
	

public:
	virtual bool Init(const Types::ObjectData&);
	virtual void Update(float fDeltaTime);
	virtual void Render(const HDC& hDC);
	

public:
	Types::ObjectType	GetActorType() const { return m_actorType; }
	Types::ObjectState GetActorState() const { return m_actorState; }
	inline void SetActorState(Types::ObjectState state) { m_actorState = state; }
	inline ActorID GetActorID() const { return m_actorID; }

private:
	//Actor, World, LayerŬ���� ���� �պ���, Git���ٰ� ���ο� �귣ġ�� ���� Push����.


protected:
	Types::Point				m_fActorPoint;
	Types::ObjectType		m_actorType;
	Types::ObjectState		m_actorState;
	ActorID					m_actorID;
	typedef std::unordered_map<Types::tstring, class ComponentBase*> ComponentTable;
	ComponentTable		m_componentTable;



};