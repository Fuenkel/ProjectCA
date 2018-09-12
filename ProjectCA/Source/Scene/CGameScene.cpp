#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CGameScene.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Core\CollisionDetector.h"
#include "..\..\Include\Core\Components\Collider.h"
#include "..\..\Include\Scene\Actor\CActorManager.h"
#include "..\..\Include\Scene\CWorld.h"



CGameScene::CGameScene(Types::SceneType type)
	:CScene(type), m_pActorManager(nullptr), m_pCurWorld(nullptr),
	//m_pNextWorld(nullptr), m_pCollisionDetector(nullptr), m_pPlayer(nullptr)
	m_pNextWorld(nullptr), m_pPlayer(nullptr)
{
}

CGameScene::~CGameScene()
{
	SAFE_DELETE(m_pCurWorld)
	SAFE_DELETE(m_pNextWorld)
}

//Layer�켱���� 0���� ���� UI�� �� ������.
bool CGameScene::Init()
{
	//if(m_pCollisionDetector == nullptr)
	//	m_pCollisionDetector = std::make_unique<CollisionDetector>();
	m_pActorManager = CActorManager::GetInstance();
	m_pActorManager->Init();	// 

	if(m_pCurWorld == nullptr)
		m_pCurWorld = new CWorld;

	if (!CreateLayer(TEXT("Player"), 1))
		return false;

	StrongActorPtr pActor = m_pActorManager->CreateActor(Types::OT_PLAYER, Types::Point(0, 0),
		Types::DIR_IDLE, 100, 100, m_pCurWorld, this, TEXT("Player"));
	FindLayer()->AddActor(pActor);


	if (!CreateLayer(TEXT("Probs"), 3))
		return false;

	//FindLayer(TEXT("Probs"))->AddObjectToLayer(new CProbs(0.f, 500.f, 800.f, 600.f));
	//FindLayer(TEXT("Probs"))->AddObjectToLayer(new CProbs(100.f, 400.f, 150.f, 450.f));
	//FindLayer(TEXT("Probs"))->AddObjectToLayer(new CProbs(250.f, 300.f, 300.f, 350.f));
	//FindLayer(TEXT("Probs"))->AddObjectToLayer(new CProbs(300.f, 250.f, 350.f, 300.f));

	CScene::Init();


	return true;
}

void CGameScene::Update(float fDeltaTime)
{
	//1. �Է¿� ���� ���� Update
	InputUpdate(fDeltaTime);

	//m_pPlayer->GetComponent(TEXT("InputComponent"))->Update(fDeltaTime);

	//2. �Է¿� ���� ���� ���� �� �浹 �˻� �� �׿� ���� Actor��� ���� ������Ʈ ���� Update
	GameUpdate(fDeltaTime);

	//Layer Update -> Rendering�� �����ϱ� �� expired�� ��ü�� �ִ��� �˻��ϱ� ����.
	CScene::Update(fDeltaTime);

}

void CGameScene::Render(const HDC& hDC)
{
	CScene::Render(hDC);

	m_pPlayer->Render(hDC);
	//InvalidateRect(NULL, NULL, TRUE);
}

//Player�� Enemy
//Player�� Probs
//Enemy�� Probs
//�浹���� �� �浹�� Object�� ���� ������ �Ѱ�����Ѵ�.
//void CGameScene::CollisionDetect()
//{
//	////Player�� Background, UI�� ������ ��� Layer�� Object��� �浹 �˻�.
//	for (auto it = FindLayer(TEXT("Player"))->GetObjectList().begin();
//		it != FindLayer(TEXT("Player"))->GetObjectList().end(); ++it)
//	{		
//		for (m_it = m_LayerList.begin(); m_it != m_LayerList.end(); ++m_it) {
//			if ( ((*m_it)->GetLayerTag() == TEXT("Background")) || ((*m_it)->GetLayerTag() == TEXT("Player")) )
//				continue;
//
//			for ( auto& object : ((*m_it)->GetObjectList()) ) {
//				//m_pCollisionDetector->Update( static_cast<Collider*>(value->GetComponent(TEXT("Collider"))), 
//				//	static_cast<Collider*>( (*it)->GetComponent(TEXT("Collider")) ) );
//				m_pCollisionDetector->Update((*it), object); //it : player
//
//			}
//		}
//	}
//
//}

void CGameScene::InputUpdate(float fDeltaTime)
{
	if (KEY_DOWN(VK_ESCAPE)) {
		//ESC�� ���� ��� �Ͻ���ġ �˾�â ���, ���� �Ͻ�����

	}
	else {
		m_pCurWorld->Update(fDeltaTime);
	}
	


}

//�浹�˻� ���� �� ó��
void CGameScene::GameUpdate(float fDeltaTime)
{
	if (!m_LayerList.empty()) {
		for (auto& it : m_LayerList){
			it->LateUpdate(fDeltaTime);
		}

	}


}

//�ش� Scene�� ������ �� ȣ���ϴ� �޼ҵ�.

void CGameScene::ResetScene()
{
	//ResetŰ �˻�
	if (KEY_DOWN(VK_BACK)) {

		Init();
	}
}

