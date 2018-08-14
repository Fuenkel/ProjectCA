#pragma once

/*
	NOTE:
		GameScene�� ���� ��ɵ��� ����.
		CScene Class�� ��ӹ���.
		Player�� Ȱ���ϰ� �� World�� ������.
*/


#include "../../stdafx.h"
#include "CScene.h"

//NOTE(06.10) : ���� ���� ���������鿡 ���� Ȱ���� �����ϴ� Stage Class�� �ʿ��ϴٰ� ������.

//Stage���� �θ� Ŭ���� ���� ����.
//���� ��������(06.10)
class CWorld;

class CGameScene :public CScene {

public:
	CGameScene(Types::SceneType);
	virtual ~CGameScene();


public:
	virtual bool Init() override;
	virtual void Update(float fDeltaTime) override;
	virtual void Render(const HDC& hDC) override;
	

public:
	void CollisionDetect();
	void GameUpdate(float fDeltaTime);
	bool IsWorldChange();
	void ChangeWorld();


private:
	void ResetScene();		


private:
	std::unique_ptr<class CollisionDetector>	m_pCollisionDetector;
	class CObjectManager*						m_pObjectManager;
	CWorld*											m_pCurWorld;
	CWorld*											m_pNextWorld;

};