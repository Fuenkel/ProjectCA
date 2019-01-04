#pragma once

#include "..\..\stdafx.h"
#include "..\Singleton.hpp"

//NOTE: Collider�� ���� �浹�� ����, �����ϱ� ���� Manager Class

class Collider;
class ColliderBox;
class ColliderCircle;
class CActor;

class CCollisionManager : public Singleton<CCollisionManager> {
	
	DECLARE_SINGLETON(CCollisionManager)

public:
	bool Init();
	void Update();
	void CheckCollision();


public:
	void AddCollider(Collider* pCollider);
	void DeleteCollider(Collider* pCollider);
	void Clear();


private:
	void CheckCollisionType(Collider* pCollider, Collider* pOther);
	bool BoxAndBox(ColliderBox* pCollider, ColliderBox* pOther);


private:
	typedef std::list<Collider*> ColliderList;
	ColliderList	m_ColliderList;

};