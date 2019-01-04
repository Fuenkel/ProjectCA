#pragma once

/*
	NOTE:
		Scene���� ����, ��ü, �ı��� ����ϴ� Manager Class.
*/


#include "..\..\stdafx.h"
#include "..\Singleton.hpp"


class CScene;

class CSceneManager : public Singleton<CSceneManager> {

	DECLARE_SINGLETON(CSceneManager)

public:
	bool Init(Types::SceneType type);
	void Update(double fDeltaTime);
	void Render(const HDC& hDC);


public:
	bool CreateScene(Types::SceneType type);
	bool CreateNextScene(Types::SceneType type);
	bool ChangeScene();
	

public:
	void SetReadyToChangeScene(bool bReady);



public:
	CScene * GetCurScene();


private:



private:
	bool			m_bReadyToChageScene;
	CScene *		m_pScene;
	CScene*		m_pNextScene;



};