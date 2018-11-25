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
	virtual void Update(double dDeltaTime) override;
	virtual void Render(const HDC& hDC) override;
	

public:
	std::weak_ptr<CPlayer> GetPlayerPtr();


private:
	bool BuildUI();
	bool BuildWorld();


private:
	void GameUpdate(double dDeltaTime);
	virtual void ResetScene() override;


private:
	int															m_iCurScore;
	int															m_iCoinCount;
	int															m_iLife;
	int															m_iRemainTime;
	double													m_dTimeElapsed;


private:
	std::weak_ptr<CPlayer>								m_pPlayer;			
	class CObjectManager*								m_pObjectManager;
	class CScoreManager*								m_pScoreManager;


};