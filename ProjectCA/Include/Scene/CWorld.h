#pragma once

/*
	NOTE:
		GameScene�� ����Ǵ� ���� �÷����ϰ� �� Stage�� ������ �����ϴ� Class.
		GameScene������ ���� �����ϰ� ����
		World�� Actor���� Layer��ü���� list�� �̿��Ͽ� ������.
	->�ش� Ŭ������ Actor���� �����ϴ� ���ұ��� �ð� �� ������, �ƴϸ� World���� Actor�� ��ȣ�ۿ뿡 ���ؼ���
		������ �ϰ� �� ������ ����غ� �ʿ䰡 ����.(08.14)
*/

#include "..\..\stdafx.h"
#include "Actor\CActor.h"

class CLayer;

class CWorld {
	friend class CGameScene;

private:
	CWorld();
	virtual ~CWorld() { };


public:
	bool Init();
	void Update(float fDeltaTime);
	void Render(const HDC& hDC);


public:
	bool CreateLayer(const Types::tstring& layerTag);
	bool DeleteLayer(const Types::tstring& layerTag);
	CLayer * FindLayer(const Types::tstring& layerTag);


public:
	bool CreateActor(const Types::tstring& layerTag, Types::ObjectData data);
	CActor* GetActor(ActorID actorID);
	CActor* GetActor(const Types::tstring& layerName, ActorID actorID);
	bool DeleteActor(ActorID actorID);
	bool DeleteActor(CActor* pActor);
	bool DeleteActor(const Types::tstring& layerName, ActorID actorID);
	ActorID GetLastActorID() const { return m_lastActorID; }


private:
	inline void IncreaseLastActorID() { ++m_lastActorID; }
	inline bool DecreaseLastActorID() { if (m_lastActorID < 1) return false; --m_lastActorID; return true; }

	
private:
	ActorID						m_lastActorID;
	std::list<class CLayer*>	m_layerList;
	


};