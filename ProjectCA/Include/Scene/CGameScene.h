#pragma once

/*
	NOTE:
		GameScene�� ���� ��ɵ��� ����.
		CScene Class�� ��ӹ���.
		Player�� Ȱ���ϰ� �� World�� ������.
*/


#include "..\..\stdafx.h"
#include "CScene.h"

//NOTE(06.10) : ���� ���� ���������鿡 ���� Ȱ���� �����ϴ� Stage Class�� �ʿ��ϴٰ� ������.

//Stage���� �θ� Ŭ���� ���� ����.
//���� ��������(06.10)
//class CWorld;
class CActor;
class CObject;
class CPlayer;

class CGameScene :public CScene {

public:
	CGameScene(Types::SceneType);
	virtual ~CGameScene();


public:
	virtual bool Init() override;
	virtual void Update(double fDeltaTime) override;
	virtual void Render(const HDC& hDC) override;
	

public:
	std::weak_ptr<CPlayer> GetPlayerPtr();


private:
	bool BuildUI();
	bool BuildWorld();


private:
	void CollisionDetect();
	void InputUpdate(double dDeltaTime);
	void GameUpdate(double dDeltaTime);
	//bool IsWorldChange();
	//void ChangeWorld();


private:
	int															m_iCurScore;
	int															m_iCoinCount;


private:
	std::shared_ptr<CPlayer>							m_pPlayer;			//���߿� weak_ptr�� �ٲ� ������ ����.
	//class CActorFactory*								m_pActorFactory;
	class CObjectManager*								m_pObjectManager;
	//std::unique_ptr<class CollisionDetector>			m_pCollisionDetector;


private:
	//CWorld*												m_pCurWorld;
	//CWorld*												m_pNextWorld;

};