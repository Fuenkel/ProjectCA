#pragma once

/*
	NOTE:
		GameScene�� ���� ��ɵ��� ����.
		CScene Class�� ��ӹ���.
		Player�� Ȱ���ϰ� �� World�� ������.
*/


#include "..\..\stdafx.h"
#include "CScene.h"

class CPlayer;

class CGameScene :public CScene {

public:
	CGameScene(Types::SceneType);
	virtual ~CGameScene();


public:
	virtual bool Init() override;
	virtual void Update(double dDeltaTime) override;
	

public:
	void SetIsGameClear();


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
	int															m_iTimeScore;
	double													m_dTimeElapsed;
	

private:
	bool														m_bClear;
	std::weak_ptr<CPlayer>								m_pPlayer;			
	class CObjectManager*								m_pObjectManager;
	class CScoreManager*								m_pScoreManager;


};