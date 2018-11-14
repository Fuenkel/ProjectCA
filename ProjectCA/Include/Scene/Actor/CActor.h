#pragma once

/*
	NOTE:
		���� �� ��� Actor���� �⺻ Class ����.
		CWorld��ü������ ���������ϰ� ����.
*/

#include "..\..\..\stdafx.h"
#include "..\CObject.h"
//#include "..\"
//#include "CActorManager.h"


class CWorld;
class CGameScene;
class ComponentBase;

//typedef std::shared_ptr<ComponentBase> StrongComponentPtr;

class CActor : public CObject{
	////Layer, World Class�� Actor�� ����, �ı��� ������.
	//friend class CWorld;
	//friend class CLayer;
	
	//08:17 : ActorFactory������ ���� �����ϰ� �ٲ�.
	//�ı��� ��쿣 Actor ��ü�� Destroy �޼ҵ带 �̿��Ͽ� ���� ������Ʈ���� �����ϰԲ� ��.
	//friend class CActorFactory;
	//friend class�� ActorManager�� �ߴ��� ActorManager������ ���� �����ϰԲ� �Ϸ��� �ǵ�������,
	//����Ʈ������ ����� �� ����� ������ ������ ����ġ�ھ �� �����ڸ� Public���� Ǯ����..(09.15)
	friend class CActorManager;

public:
	CActor();
	virtual ~CActor();
	

public:
	virtual bool PostInit(const Types::ActorData&, CGameScene*);
	virtual void Init();
	virtual void Update(double dDeltaTime);
	virtual void Render(const HDC& hDC) = 0;
	virtual void LateUpdate(double dDeltaTime);
	virtual void Destroy();


public:
	void SetActorState(Types::ActorState state);
	void SetActorDirection(Types::Direction dir);
	void SetActorVerticalState(Types::VerticalState vertical);
	void SetActorHorizonalState(Types::HorizonalState horizonal);
	//void SetOwnerWorld(CWorld* pWorld);


public:
	Types::ActorType		GetActorType() const;
	Types::ActorState		GetActorState() const;
	Types::Direction		GetActorDirection() const;
	UINT						GetActorWidth() const;
	UINT						GetActorHeight() const;
	Types::ActorID			GetActorID() const;
	Types::VerticalState	GetActorVerticalState() const;
	Types::HorizonalState GetActorHorizonalState() const;
	//CWorld* const			GetOwnerWorld() const;


public:
	void FlipActorDirection();


private:
	virtual void ActorBehavior(double dDeltaTime) = 0;


protected:
	Types::ActorType			m_ActorType;
	Types::ActorState			m_ActorCurState;
	Types::VerticalState		m_ActorCurVerticalState;
	Types::HorizonalState		m_ActorHorizonalState;
	Types::Direction			m_Direction;
	Types::ActorID				m_ActorID;
	//CWorld*					m_pOwnerWorld;

	
};