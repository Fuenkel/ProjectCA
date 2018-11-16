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
class CTile;


class CWorld {
	friend class CGameScene;

private:
	CWorld();
	virtual ~CWorld();


public:
	bool PostInit(std::shared_ptr<CActor> pPlayer);
	bool Init();
	void Update(double dDeltaTime);
	void Render(const HDC& hDC);


public:
	void AddActor(std::shared_ptr<CActor> pActor);
	std::weak_ptr<CActor> GetActor(Types::ActorID actorID);
	bool DeleteActor(Types::ActorID actorID);
	bool DeleteActor(std::weak_ptr<CActor> pActor);
	bool CollisionUpdate();
	bool SetWolrdGravity(float fGravity);


public:
	//std::weak_ptr<CActor> GetTarget(ActorID id);	// �ϴ� ���߿� �ۼ�
	float GetWorldGravity();



private:
	bool BuildWorld();
	void ResolveCollision();
	void SimulWorld();
	bool CheckGrounded();

	
private:
	float													m_fWorldGravity;
	class CObjectManager*							m_pObjectManager;
	std::weak_ptr<CActor>							m_pPlayer;
	std::list<std::weak_ptr<CActor>>				m_ActorList;
	std::list<std::weak_ptr<CActor>>				m_GroundList;


};