#pragma once

/*
	NOTE:
		Actor�� ����, ��ȣ�ۿ� ���� ����� ����ϴ� Manager Class
*/

#include "..\..\..\stdafx.h"
#include "..\..\Singleton.hpp"

class CActor;
class CWorld;
class CGameScene;

typedef std::weak_ptr<CActor> WeakActorPtr;
typedef std::shared_ptr<CActor> StrongActorPtr;

using GenerateActor = std::function<StrongActorPtr(Types::ObjectType)>;

class CActorManager : public Singleton<CActorManager> {

	DECLARE_SINGLETON(CActorManager)

public:
	bool Init();
	//void Update();



public:
	//StrongActorPtr CreateActor(const Types::ActorData& data);
	//StrongActorPtr CreateActor(Types::ObjectType type, Types::Point point, Types::Direction dir, 
	//	UINT iWidth, UINT iHeight, CGameScene* pScene, const Types::tstring& strTag,
	//	Types::ObjectState state = Types::OS_IDLE);
	WeakActorPtr GetTarget(Types::ActorID id);
	WeakActorPtr GetTarger(const Types::tstring& strTag);
	
public:
	template<typename T>
	std::shared_ptr<T> CreateActor(const Types::ActorData& data) {

		std::shared_ptr<T> pActor = std::make_shared<T>();
		
		if (!pActor->PostInit(data))
			return std::shared_ptr<T>();
		

		return pActor;
	}

	//�����ε�����
	template<typename T>
	std::shared_ptr<T> CreateActor(UINT iWidth, UINT iHeight, float fx, float fy, Types::ObjectType type, 
		Types::ObjectState state, Types::Direction dir, Types::Point _vector, const Types::tstring& strTag,
		CGameScene* pScene, bool _bActive = true) {

		std::shared_ptr<T> pActor = std::make_shared<T>();

		Types::ActorData data(iWidth, iHeight, Types::Point(fx, fy), type, state,
			dir, _vector, m_lastActorID++,strTag, _bActive);

		if (!pActor->PostInit(data, pScene))
			return std::shared_ptr<T>();


		return pActor;
	}


private:



private:
	GenerateActor					m_genrateActor;
	std::list<StrongActorPtr>		m_strongActorPtrList;
	static Types::ActorID			m_lastActorID;
	
};

