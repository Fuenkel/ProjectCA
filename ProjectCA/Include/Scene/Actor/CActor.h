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
	//virtual bool Init(const Types::ActorData&);
	virtual bool Init() = 0;
	virtual void Update(double fDeltaTime);
	virtual void Render(const HDC& hDC) = 0;
	//virtual void LateUpdate(float fDeltaTime);
	virtual void Destroy();
	virtual void ActorBehavior() { };


public:
	ComponentBase * GetComponent(const Types::tstring& strTag);
	bool AddComponent(ComponentBase* pComponent, const Types::tstring& strTag);
	bool DeleteComponent(const Types::tstring& strTag);


public:
	inline bool IsActive() const { return m_bActive; }
	inline void SetActive(bool bActive) { m_bActive = bActive; }
	Types::ObjectType	GetActorType() const { return m_actorType; }
	Types::ObjectState GetActorState() const { return m_actorCurState; }
	void SetActorState(Types::ObjectState state) { m_actorCurState = state; }
	Types::ObjectState GetActorPreState() const { return m_actorPreState; }
	Types::Direction GetActorDirection() const { return m_direction; }
	Types::Point GetActorVector() const { return m_actorVector; }
	bool SetActorVector(float fx, float fy) {		//�������� ���� �ڵ� -> ���� Vector2d class �ۼ��ϸ� 
															//�ش� class�� ��ü�ϸ鼭 �ٽ� �ٲܰ���.(09.25)
		m_actorVector.x = fx;
		m_actorVector.y = fy;

		return true;
	}
	void SetActorDirection(Types::Direction dir) { m_direction = dir; }
	UINT GetActorWidth() const { return m_iActorWidth; }
	void SetActorWidth(UINT iWidth) { m_iActorWidth = iWidth; }
	UINT GetActorHeight() const { return m_iActorHeight; }
	void SetActorHeight(UINT iHeight) { m_iActorHeight = iHeight; }
	Types::Point GetActorPoint() const { return m_actorPoint; }
	bool SetActorPoint(float fx, float fy) {
		if (fx < 0 || fy < 0)
			return false;
	
		if (fx > MAX_WIDTH || fy > MAX_HEIGHT)
			return false;

		m_actorPoint.x = fx;
		m_actorPoint.y = fy;
		
		return true;
	}
	const Types::tstring& GetActorTag() const { return m_strActorTag; }
	void SetActorTag(const Types::tstring& strTag) { m_strActorTag == strTag; }
	inline Types::ActorID GetActorID() const { return m_actorID; }	
	Types::JumpState GetActorJumpState() const { return m_actorJumpState; }
	void SetActorJumpState(Types::JumpState jump) { m_actorJumpState = jump; }
	Types::JumpState GetActorPreJumpState() const { return m_actorPreJumpState; }
	//CWorld* const GetOwnerWorld() const;
	//void SetOwnerWorld(CWorld* pWorld);
	CGameScene* const GetOwnerScene() const;
	void SetOwnerScene(CGameScene* pScene);
	bool SetLayer(const Types::tstring& strLayerTag);
	void FlipVector();


protected:
	UINT						m_iActorWidth;
	UINT						m_iActorHeight;
	Types::Point				m_actorPoint;
	Types::Point				m_spawnPoint;
	Types::ObjectType		m_actorType;
	Types::ObjectState		m_actorCurState;
	Types::ObjectState		m_actorPreState;
	Types::JumpState		m_actorPreJumpState;
	Types::JumpState		m_actorJumpState;
	Types::Direction		m_direction;
	Types::Point				m_actorVector;
	Types::ActorID			m_actorID;
	Types::tstring			m_strActorTag;		 
	//CWorld*					m_pOwnerWorld;
	CGameScene*			m_pOwnerScene;
	bool						m_bActive;


protected:
	typedef std::unordered_map<Types::tstring, class ComponentBase*> ComponentTable;
	ComponentTable		m_componentTable;

	
};