#pragma once

/*
	NOTE:
		���� �� ��� Actor���� �⺻ Class ����.
		CWorld��ü������ ���������ϰ� ����.
*/

#include "..\..\..\stdafx.h"
//#include "..\"
//#include "CActorManager.h"


class CWorld;
class CGameScene;
class ComponentBase;


class CActor {
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
	virtual bool PostInit(const Types::ActorData&, CGameScene*) = 0;
	virtual bool Init() = 0;
	virtual void Update(double fDeltaTime);
	virtual void Render(const HDC& hDC) = 0;
	//virtual void LateUpdate(float fDeltaTime);
	virtual void Destroy();
	virtual void ActorBehavior(double dDeltaTime) = 0;


public:
	ComponentBase * GetComponent(const Types::tstring& strTag);
	bool					AddComponent(ComponentBase* pComponent, const Types::tstring& strTag);
	bool					DeleteComponent(const Types::tstring& strTag);
	template<typename T>
	T*	GetComponent() const
	{
		const std::type_info& type = typeid(T);
		for (auto& it : m_componentTable)
		{
			if (typeid(*(it.second)) == type)
				return static_cast<T*>(it.second);
		}

		return nullptr;
	}

public:
	void SetActive(bool bActive);
	void SetActorState(Types::ActorState state);
	void SetActorVector(float fx, float fy);
	void SetActorDirection(Types::Direction dir);
	void SetActorWidth(UINT iWidth);
	void SetActorHeight(UINT iHeight);
	void SetActorPoint(float fx, float fy);
	void SetActorTag(const Types::tstring& strTag);
	void SetActorVerticalState(Types::VerticalState vertical);
	void SetActorHorizonalState(Types::HorizonalState horizonal);
	void SetOwnerScene(CGameScene* pScene);
	//void SetOwnerWorld(CWorld* pWorld);
	bool SetLayer(const Types::tstring& strLayerTag);


public:
	bool						IsActive() const;
	Types::ActorType		GetActorType() const;
	Types::ActorState		GetActorState() const;
	Types::ActorState		GetActorPreState() const;
	Types::Direction		GetActorDirection() const;
	Types::Point				GetActorVector() const;
	UINT						GetActorWidth() const;
	UINT						GetActorHeight() const;
	Types::Point				GetActorPoint() const;
	const Types::Point		GetActorPivot() const;
	const Types::tstring& GetActorTag() const;
	Types::ActorID			GetActorID() const;
	Types::VerticalState	GetActorVerticalState() const;
	Types::VerticalState	GetActorPreVerticalState() const;
	Types::HorizonalState GetActorHorizonalState() const;
	//CWorld* const			GetOwnerWorld() const;
	CGameScene* const	GetOwnerScene() const;


public:
	void FlipVector();
	void FlipActorDirection();


protected:
	UINT							m_iActorWidth;
	UINT							m_iActorHeight;
	//POSITION					m_actorPoint;
	//POSITION					m_spawnPoint;
	//POSITION					m_actorPivot;
	Types::ActorType			m_actorType;
	Types::ActorState			m_actorCurState;
	Types::ActorState			m_actorPreState;
	Types::VerticalState		m_actorCurVerticalState;
	Types::VerticalState		m_actorPreVerticalState;
	Types::HorizonalState		m_actorHorizonalState;
	Types::Direction			m_direction;
	Types::Point					m_actorVector;
	Types::ActorID				m_actorID;
	Types::tstring				m_strActorTag;		 
	//CWorld*					m_pOwnerWorld;
	CGameScene*				m_pOwnerScene;
	bool							m_bActive;


protected:
	typedef std::unordered_map<Types::tstring, class ComponentBase*> ComponentTable;
	ComponentTable		m_componentTable;

	
};