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

class CGameScene :public CScene {

public:
	CGameScene(Types::SceneType);
	virtual ~CGameScene();


public:
	virtual bool Init() override;
	virtual void Update(double fDeltaTime) override;
	virtual void Render(const HDC& hDC) override;
	

private:
	void CollisionDetect();
	void InputUpdate(double fDeltaTime);
	void GameUpdate(double fDeltaTime);
	//bool IsWorldChange();
	//void ChangeWorld();


public:
	void ResetScene();		


private:
	UINT													m_iCurScore;
	UINT													m_iHighScore;


private:
	std::shared_ptr<CActor>								m_pPlayer;			//���߿� weak_ptr�� �ٲ� ������ ����.
	//class CActorFactory*								m_pActorFactory;
	class CActorManager*								m_pActorManager;
	std::unique_ptr<class CollisionDetector>			m_pCollisionDetector;


private:
	typedef std::list<std::shared_ptr<CActor>>	StrongPtrActorList;
	StrongPtrActorList										m_strongActorList;
	//CWorld*												m_pCurWorld;
	//CWorld*												m_pNextWorld;

};