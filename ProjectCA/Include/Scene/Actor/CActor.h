#pragma once

/*
	NOTE:
		���� �� ��� Actor���� �⺻ Class ����.
		CWorld��ü������ ���������ϰ� ����.
*/

#include "..\..\..\stdafx.h"

typedef unsigned long ActorID;

class CWorld;
class CGameScene;

class CActor {
	////Layer, World Class�� Actor�� ����, �ı��� ������.
	//friend class CWorld;
	//friend class CLayer;
	
	//08:17 : ActorFactory������ ���� �����ϰ� �ٲ�.
	//�ı��� ��쿣 Actor ��ü�� Destroy �޼ҵ带 �̿��Ͽ� ��ü�� �ı��� �����ϰ� ����.
	//friend class CActorFactory;
	friend class CActorManager;

private:
	CActor();
	virtual ~CActor();
	

public:
	virtual bool Init(const Types::ObjectData&);
	virtual void Update(float fDeltaTime);
	virtual void Render(const HDC& hDC);
	virtual void LateUpdate(float fDeltaTime);
	virtual void Destroy();


public:
	inline bool IsActive() const { return m_bActive; }
	inline void SetActive(bool bActive) { m_bActive = bActive; }
	Types::ObjectType	GetActorType() const { return m_actorType; }
	Types::ObjectState GetActorState() const { return m_actorState; }
	void SetActorState(Types::ObjectState state) { m_actorState = state; }
	Types::Direction GetActorDirection() const { return m_direction; }
	void SetActorDirection(Types::Direction dir) { m_direction = dir; }
	const CWorld* const GetOwnerWorld() const { return m_pOwnerWorld; }
	void SetOwnerWorld(CWorld* pWorld) { m_pOwnerWorld = pWorld; }
	const CGameScene* const GetOwnerScene() const { return m_pOwnerScene; }
	void SetOwnerScene(CGameScene* pScene) { m_pOwnerScene = pScene; }
	inline ActorID GetActorID() const { return m_actorID; }
	

private:
	//Actor, World, LayerŬ���� ���� �պ���, Git���ٰ� ���ο� �귣ġ�� ���� Push����.


protected:
	bool						m_bActive;
	UINT						m_iActorWidth;
	UINT						m_iActorHeight;
	Types::Point				m_fActorPoint;
	Types::ObjectType		m_actorType;
	Types::ObjectState		m_actorState;
	Types::Direction		m_direction;
	ActorID					m_actorID;
	CWorld*					m_pOwnerWorld;
	CGameScene*			m_pOwnerScene;


protected:
	typedef std::unordered_map<Types::tstring, class ComponentBase*> ComponentTable;
	ComponentTable		m_componentTable;


};