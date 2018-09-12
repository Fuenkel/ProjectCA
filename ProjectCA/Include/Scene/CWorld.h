#pragma once

/*
	NOTE:
		GameScene�� ����Ǵ� ���� �÷����ϰ� �� Stage�� ������ �����ϴ� Class.
		GameScene������ ���� �����ϰ� ����
		World�� Actor���� Layer��ü���� list�� �̿��Ͽ� ������.
	->�ش� Ŭ������ Actor���� �����ϴ� ���ұ��� �ð� �� ������, �ƴϸ� World���� Actor�� ��ȣ�ۿ뿡 ���ؼ���
		������ �ϰ� �� ������ ����غ� �ʿ䰡 ����.(08.14)
	-> World���� ��� Actor���� �����Ϳ� �����ϰ�, �������� ��ȣ�ۿ뿡 ���ؼ��� ����� �����ϰԲ� ����.(08.16)
	-> �̺κк��� �ٽ� �غ���
	
*/

#include "..\..\stdafx.h"


class CActor;

class CWorld {
	friend class CGameScene;

private:
	CWorld();
	virtual ~CWorld();


public:
	bool Init();
	void Update(float fDeltaTime);


public:
	void AddActor(std::shared_ptr<CActor> pActor);
	std::weak_ptr<CActor> GetActor(Types::ActorID actorID);
	bool DeleteActor(Types::ActorID actorID);
	bool DeleteActor(std::weak_ptr<CActor> pActor);
	bool CollisionUpdate();


public:
	//std::weak_ptr<CActor> GetTarget(ActorID id);	// �ϴ� ���߿� �ۼ�




private:
	void ResolveCollision();
	void SimulWorld();

	
private:
	std::list<std::weak_ptr<CActor>>				m_actorList;
	std::unique_ptr<class CollisionDetector>		m_pCollisionDetector;

};