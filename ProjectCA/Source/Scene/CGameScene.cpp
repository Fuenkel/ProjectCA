#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CGameScene.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Core\CollisionDetector.h"
#include "..\..\Include\Core\Components\Collider.h"
#include "..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\Include\Core\Components\InputComponent.h"
#include "..\..\Include\Scene\Actor\CActorManager.h"
#include "..\..\Include\Scene\Actor\CActor.h"
#include "..\..\Include\Scene\Actor\CEnemy.h"
#include "..\..\Include\Scene\Actor\CPlayer.h"
//#include "..\..\Include\Scene\CWorld.h"



CGameScene::CGameScene(Types::SceneType type)
	:CScene(type), m_pActorManager(nullptr), m_pPlayer(nullptr),
	m_pCollisionDetector(nullptr)
{
	//�⺻ ���̾� ����.
	//ActorManager���� Actor�� ������ ��� �⺻������ default���̾ ���� �� ��.
	//Layer order 0�� UI�� �� ��.
	CreateLayer(TEXT("default"), 1);

}

CGameScene::~CGameScene()
{
	//SAFE_DELETE(m_pCurWorld)
	//SAFE_DELETE(m_pNextWorld)
	m_strongActorList.clear();
}

//Layer�켱���� 0���� ���� UI�� �� ������.
bool CGameScene::Init()
{
	if(m_pCollisionDetector == nullptr)
		m_pCollisionDetector = std::make_unique<CollisionDetector>();

	m_pActorManager = CActorManager::GetInstance();
	if (!m_pActorManager->Init())
		return false; 

	//if(m_pCurWorld == nullptr)
	//	m_pCurWorld = new CWorld;

	if (!CreateLayer(TEXT("Player"), 2))
		return false;

	//World�� �����Ͱ� ���� �ڸ��� �ӽ÷� nullptr�� ��ü��.(09.13)
	//m_pPlayer = m_pActorManager->CreateActor(Types::OT_PLAYER, Types::Point(0, 0),
	//	Types::DIR_IDLE, 100, 100, (this), TEXT("Player"));

	m_pPlayer = m_pActorManager->CreateActor<CPlayer>(100, 100, 0, 0, Types::OT_PLAYER, Types::OS_IDLE, 
		Types::DIR_IDLE, TEXT("Player"), this);

	m_strongActorList.emplace_back(m_pPlayer);

	if (m_pPlayer == nullptr)
		return false;

	FindLayer(TEXT("Player"))->AddActor(m_pPlayer);
	
	std::shared_ptr<CEnemy> pEnemy = m_pActorManager->CreateActor<CEnemy>(50, 50, 250, 250, Types::OT_ENEMY,
		Types::OS_IDLE, Types::DIR_DOWN, TEXT("Enemy"), this);

	if (pEnemy == nullptr)
		return false;

	m_strongActorList.emplace_back(pEnemy);

	if (!CreateLayer(TEXT("Enemy"), 3))
		return false;

	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);

	//StrongActorPtr pProb = m_pActorManager->CreateActor(Types::OT_PROBS, Types::Point(300, 300),
	//	Types::DIR_IDLE, 200, 200, (this), TEXT("Probs"));

	//StrongActorPtr pProb;

	//m_strongActorList.emplace_back(pProb);

	//FindLayer(TEXT("Probs"))->AddActor(pProb);

	//FindLayer(TEXT("Probs"))->AddObjectToLayer(new CProbs(100.f, 400.f, 150.f, 450.f));
	//FindLayer(TEXT("Probs"))->AddObjectToLayer(new CProbs(250.f, 300.f, 300.f, 350.f));
	//FindLayer(TEXT("Probs"))->AddObjectToLayer(new CProbs(300.f, 250.f, 350.f, 300.f));

	CScene::Init();


	return true;
}

void CGameScene::Update(float fDeltaTime)
{
	//1. �Է¿� ���� ���� Update
	// TODO(09.17) : ���� Input�� �޴� ���� Player�� �ִ� PlayerInputComponent���� �����ϰ� �ִµ�,
	//					   �� �κ��� GameScene Level���� ������ �� �ְԲ� ������ �ʿ䰡 �־��.
	//InputUpdate(fDeltaTime); -> �ϴ��� ���Ƿ� GameUpdate�� ������Ŵ.

	//2. �Է¿� ���� ���� ���� �� �浹 �˻� �� �׿� ���� Actor��� ���� ������Ʈ ���� Update
	GameUpdate(fDeltaTime);

	//Layer Update -> Rendering�� �����ϱ� �� expired�� ��ü�� �ִ��� �˻��ϱ� ����.
	CScene::Update(fDeltaTime);

}

void CGameScene::Render(const HDC& hDC)
{
	//Layer��ü�� �����ϴ� Actor���� Rendering
	CScene::Render(hDC);

	//m_pPlayer->Render(hDC);
	//InvalidateRect(NULL, NULL, TRUE);
}

//Player�� Enemy
//Player�� Probs
//Enemy�� Probs
//�浹���� �� �浹�� Object�� ���� ������ �Ѱ�����Ѵ�.
void CGameScene::CollisionDetect()
{
	////Scene���� ��� Actor�鿡 ���� �浹�˻� ����
	
	for (auto& first : m_strongActorList) {
		for (auto& second : m_strongActorList) {
			if (first == second)		
				continue;
			m_pCollisionDetector->Update(first, second);
		}
	}

}

void CGameScene::InputUpdate(float fDeltaTime)
{
	if (KEY_DOWN(VK_ESCAPE)) {
		//ESC�� ���� ��� �Ͻ���ġ �˾�â ���, ���� �Ͻ�����

	}
	else {
		//m_pCurWorld->Update(fDeltaTime);
		m_pPlayer->GetComponent(TEXT("InputComponent"))->Update(fDeltaTime);
	}
	


}

//�浹�˻� ���� �� ó��
void CGameScene::GameUpdate(float fDeltaTime)
{
	//Component Update
	for (auto& actor : m_strongActorList) {
		actor->Update(fDeltaTime);
	}

	//Collsion detect between Actors
	CollisionDetect();

	//Collision �� ó�� �κ�������, �׽�Ʈ������ �ϴ� Player�� ��ó���� �ϵ��ڵ�.(09.17)
	//		-> ���� �۵�
	//if (static_cast<Collider*>(m_pPlayer->GetComponent(TEXT("Collider")))->GetIsCollision()) {
	//	PhysicsComponent* pPhysics = static_cast<PhysicsComponent*>(m_pPlayer->GetComponent(TEXT("PhysicsComponent")));
	//	pPhysics->RestoreActorPoint();
	//}

}

//�ش� Scene�� ������ �� ȣ���ϴ� �޼ҵ�.

void CGameScene::ResetScene()
{
	//ResetŰ �˻�
	if (KEY_DOWN(VK_BACK)) {

		Init();
	}
}

