#pragma once

/*
	NOTE:���� ���� �����̴� ��ü���� ��ӹް� �� �⺻ Class ����.
			CObject�� ��ӹ޾Ƽ� �ۼ�.
			����, �������� ����, ����, ActionType ������ ���������� ����.
*/

#include "..\..\..\stdafx.h"
#include "..\CObject.h"

class CGameScene;

typedef std::shared_ptr<ComponentBase> StrongComponentPtr;

class CActor : public CObject
{	
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
	

public:
	void SetActorAct(ACT act);
	void SetActorDirection(DIRECTION dir);


public:
	ACT						GetActorAct() const;
	DIRECTION				GetActorDirection() const;
	UINT						GetActorWidth() const;
	UINT						GetActorHeight() const;


public:
	void FlipActorDirection();


private:
	virtual void ActorBehavior(double dDeltaTime) = 0;


protected:
	ACT							m_ActType;
	DIRECTION					m_Direction;

	
};