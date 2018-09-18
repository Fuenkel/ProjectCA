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
	CActor() = default;
	virtual ~CActor();
	

public:
	virtual bool PostInit();
	virtual bool Init(const Types::ActorData&);
	virtual void Update(float fDeltaTime);
	virtual void Render(const HDC& hDC);
	//virtual void LateUpdate(float fDeltaTime);
	virtual void Destroy();
	//virtual void ActorBehavior() = 0;


public:
	ComponentBase * GetComponent(const Types::tstring& strTag);
	bool AddComponent(ComponentBase* pComponent, const Types::tstring& strTag);
	bool DeleteComponent(const Types::tstring& strTag);


public:
	inline bool IsActive() const { return m_bActive; }
	inline void SetActive(bool bActive) { m_bActive = bActive; }
	Types::ObjectType	GetActorType() const { return m_actorType; }
	Types::ObjectState GetActorState() const { return m_actorState; }
	void SetActorState(Types::ObjectState state) { m_actorState = state; }
	Types::Direction GetActorDirection() const { return m_direction; }
	void SetActorDirection(Types::Direction dir) { m_direction = dir; }
	UINT GetActorWidth() const { return m_iActorWidth; }
	void SetActorWidth(UINT iWidth) { m_iActorWidth = iWidth; }
	UINT GetActorHeight() const { return m_iActorHeight; }
	void SetActorHeight(UINT iHeight) { m_iActorHeight = iHeight; }
	Types::Point GetActorPoint() const { return m_fActorPoint; }
	bool SetActorPoint(float fx, float fy) {
		if (fx < 0 || fy < 0)
			return false;
	
		m_fActorPoint.x = fx;
		m_fActorPoint.y = fy;
		
		return true;
	}
	const Types::tstring& GetActorTag() const { return m_strActorTag; }
	void SetActorTag(const Types::tstring& strTag) { m_strActorTag == strTag; }
	inline Types::ActorID GetActorID() const { return m_actorID; }	
	//CWorld* const GetOwnerWorld() const;
	//void SetOwnerWorld(CWorld* pWorld);
	CGameScene* const GetOwnerScene() const;
	void SetOwnerScene(CGameScene* pScene);
	bool SetLayer(const Types::tstring& strLayerTag);


protected:
	bool						m_bActive;
	UINT						m_iActorWidth;
	UINT						m_iActorHeight;
	Types::Point				m_fActorPoint;
	Types::ObjectType		m_actorType;
	Types::ObjectState		m_actorState;
	Types::Direction		m_direction;
	Types::ActorID			m_actorID;
	Types::tstring			m_strActorTag;		 
	//CWorld*					m_pOwnerWorld;
	CGameScene*			m_pOwnerScene;


protected:
	typedef std::unordered_map<Types::tstring, class ComponentBase*> ComponentTable;
	ComponentTable		m_componentTable;


};