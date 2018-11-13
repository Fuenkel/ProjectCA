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

//typedef std::shared_ptr<ComponentBase> StrongComponentPtr;

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
	virtual void Update(double dDeltaTime);
	virtual void Render(const HDC& hDC) = 0;
	virtual void LateUpdate(double dDeltaTime);
	virtual void Destroy();


public:
	std::weak_ptr<ComponentBase>	GetComponent(const TSTRING& strTag);
	bool										AddComponent(std::shared_ptr<ComponentBase> pComponent, const TSTRING& strTag);
	bool										DeleteComponent(const TSTRING& strTag);
	template<typename T>
	std::weak_ptr<T>	GetComponent() const
	{
		const std::type_info& type = typeid(T);
		for (auto& it : m_componentTable)
		{
			if (typeid(*(it.second)) == type)
				return STATIC_POINTER_CAST(T, it.second);
		}

		return std::weak_ptr<T>();
	}

public:
	void SetActive(bool bActive);
	void SetActorState(Types::ActorState state);
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
	Types::Direction		GetActorDirection() const;
	UINT						GetActorWidth() const;
	UINT						GetActorHeight() const;
	Types::Point				GetActorPoint() const;
	const Types::Point		GetActorPivot() const;
	const Types::tstring& GetActorTag() const;
	Types::ActorID			GetActorID() const;
	Types::VerticalState	GetActorVerticalState() const;
	Types::HorizonalState GetActorHorizonalState() const;
	//CWorld* const			GetOwnerWorld() const;
	CGameScene* const	GetOwnerScene() const;


public:
	void FlipActorDirection();


private:
	virtual void ActorBehavior(double dDeltaTime) = 0;


protected:
	UINT							m_iActorWidth;
	UINT							m_iActorHeight;
	Types::ActorType			m_actorType;
	Types::ActorState			m_actorCurState;
	Types::VerticalState		m_actorCurVerticalState;
	Types::HorizonalState		m_actorHorizonalState;
	Types::Direction			m_direction;
	Types::ActorID				m_actorID;
	Types::tstring				m_strActorTag;		 
	//CWorld*					m_pOwnerWorld;
	CGameScene*				m_pOwnerScene;
	bool							m_bActive;


protected:
	typedef std::unordered_map<Types::tstring, std::shared_ptr<ComponentBase>> ComponentTable;
	ComponentTable		m_componentTable;

	
};