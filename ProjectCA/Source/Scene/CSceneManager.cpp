#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CSceneManager.h"
#include "..\..\Include\Scene\CCameraManager.h"
#include "..\..\Include\Scene\Actor\CObjectManager.hpp"
#include "..\..\Include\Core\Sound\CSoundManager.h"
#include "..\..\Include\Scene\CScene.h"
#include "..\..\Include\Scene\CGameScene.h"
#include "..\..\Include\Scene\CGameOverScene.h"
#include "..\..\Include\Scene\CTitleScene.h"



CSceneManager::CSceneManager() :m_pScene(nullptr), m_pNextScene(nullptr) 
{ 
}

CSceneManager::~CSceneManager() {
	
	SAFE_DELETE(m_pScene)
	SAFE_DELETE(m_pNextScene);
	CObjectManager::GetInstance()->Destroy();
	CCameraManager::GetInstance()->Destroy();
	CSoundManager::GetInstance()->Destroy();

}

bool CSceneManager::Init(Types::SceneType type) 
{
	if (!CObjectManager::GetInstance()->Init())
		return false;

	if (!CCameraManager::GetInstance()->Init())
		return false;

	if (!CSoundManager::GetInstance()->Init())
		return false;

	if (!CreateScene(type))
		return false;
	
	m_bReadyToChageScene = false;

	return true;
}

void CSceneManager::Update(double fDeltaTime)
{
	if (m_bReadyToChageScene)
	{
		ChangeScene();
	}
	else
	{
		m_pScene->Update(fDeltaTime);
		CSoundManager::GetInstance()->Update();
	}

}

void CSceneManager::Render(const HDC& hDC)
{
	m_pScene->Render(hDC);
}

bool CSceneManager::CreateScene(Types::SceneType type)
{
	SAFE_DELETE(m_pScene);

	switch (type) {
	case Types::ST_TITLE:
		m_pScene = new CTitleScene();
		break;
	case Types::ST_GAME:
		m_pScene = new CGameScene(type);
		break;
	case Types::ST_GAMEOVER:
		m_pScene = new CGameOverScene();
		break;
	default:
		return false;
	}

	return m_pScene->Init();
}

bool CSceneManager::CreateNextScene(Types::SceneType type)
{
	SAFE_DELETE(m_pNextScene);

	switch (type) {
	case Types::ST_TITLE:
		m_pNextScene = new CTitleScene();
		break;
	case Types::ST_GAME:
		m_pNextScene = new CGameScene(type);
		break;
	case Types::ST_GAMEOVER:
		m_pNextScene = new CGameOverScene();
		break;
	default:
		return false;
	}
	
	return m_pNextScene->Init();
}

bool CSceneManager::ChangeScene()
{
	if (m_pNextScene == nullptr)
		return false;

	SAFE_DELETE(m_pScene)
	m_pScene = m_pNextScene;
	m_pNextScene = nullptr;

	m_bReadyToChageScene = false;
	m_pScene->StartScene();

	return true;
	//return CreateNextScene(nextSceneType);
}

void CSceneManager::SetReadyToChangeScene(bool bReady)
{
	m_bReadyToChageScene = bReady;
}

CScene * CSceneManager::GetCurScene()
{
	return m_pScene;
}
