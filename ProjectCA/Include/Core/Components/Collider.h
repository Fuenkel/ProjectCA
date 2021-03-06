#pragma once

#include "..\..\..\stdafx.h"
#include "ComponentBase.h"

//NOTE: 객체간의 충돌을 감지하기 위한 Component
//			객체에 Collider를 추가할 경우 Collider에 충돌이 일어났을 경우 실행되는 Callback메소드를 지정해줘야함.

class CObject;

class Collider : public ComponentBase {

public:
	enum ColliderType { CT_BOX, CT_CIRCLE, CT_BOX_TRIGGER, CT_CIRCLE_TRIGGER };
	enum CollisionType {
		COLLISION_IDLE, COLLISION_TOP,
		COLLISION_BOT, COLLISION_RIGHT, COLLISION_LEFT
	};

	using Callback = std::function<void(CObject*, CollisionType type, float fIntersectLength)>;


public:
	Collider(ColliderType);
	virtual ~Collider();


public:
	virtual bool PostInit(CEntity* pOwner, const Types::tstring& strTag = TEXT("Collider"));
	virtual void Update(double dDeltaTime) = 0;
	virtual void LateUpdate() override;
	virtual void ResolveCollision(CObject* pOther, float fintersectLength);
	virtual void DrawCollider(const HDC& hDC) = 0;


public:
	void SetColliderType(ColliderType type);
	void SetCollisionType(CollisionType type);
	void SetIsCollision(bool bCollision);
	void SetColliderPoint(POSITION position);
	void SetColliderPoint(float fx, float fy);
	void SetUseTriggered(bool bUseTrigger);
	void SetDelegate(Callback pDelegate);
	void SetOnCollision(Callback pCollision);
	void SetOnTrigerr(Callback pTrigger);


public:
	ColliderType			GetColliderType() const;
	CollisionType			GetCollisionType() const;
	bool						IsCollision() const;
	bool						IsTriggered() const;
	const Types::Point&	GetColliderPoint() const;
	

private:
	virtual void OnCollision(CObject* pOther, float fintersectLength);
	virtual void OnTriggered(CObject* pOther, float fintersectLength);


protected:
	ColliderType				m_ColliderType;
	CollisionType				m_CollisionType;
	POSITION					m_ColliderPoint;
	POSITION					m_CurColliderPoint;
	bool							m_bCollision;
	bool							m_bUseTrigger;


private:
	Callback						m_pOnCollision;
	Callback						m_pOnTrigger;


};