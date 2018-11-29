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
	//virtual void LateUpdate(double dDeltaTime);
	//virtual void Destroy();


public:
	void SetActorDirection(DIRECTION dir);
	void SetActorVerticalState(VER_STATE vertical);
	void SetActorHorizonalState(HOR_STATE horizonal);
	//void SetOwnerWorld(CWorld* pWorld);


public:
	VER_STATE				GetActorVerticalState() const;
	HOR_STATE				GetActorHorizonalState() const;
	DIRECTION				GetActorDirection() const;
	UINT						GetActorWidth() const;
	UINT						GetActorHeight() const;
	//CWorld* const			GetOwnerWorld() const;


public:
	void FlipActorDirection();


private:
	virtual void ActorBehavior(double dDeltaTime) = 0;


protected:
	VER_STATE					m_ActorCurVerticalState;
	HOR_STATE					m_ActorHorizonalState;
	DIRECTION					m_Direction;
	//CWorld*					m_pOwnerWorld;

	
};