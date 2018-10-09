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
#include "..\..\Include\Scene\Actor\CProb.h"
#include "..\..\Include\Scene\Actor\CBackground.h"
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

	////if(m_pCurWorld == nullptr)
	////	m_pCurWorld = new CWorld;

	//Player ����
	m_pPlayer = m_pActorManager->CreateActor<CPlayer>(100, 100, 0, 0, Types::OT_PLAYER, Types::OS_IDLE, 
		Types::DIR_RIGHT, Types::Point(0.f, 0.f),TEXT("Player"), this);

	m_strongActorList.emplace_back(m_pPlayer);

	if (m_pPlayer == nullptr)
		return false;

	if (!CreateLayer(TEXT("Player"), 2))
		return false;

	FindLayer(TEXT("Player"))->AddActor(m_pPlayer);
	

	//Enemy ����
	//Windows ��ǥ�迡�� y���� �ݴ�����̹Ƿ� Vector�� ���� �ݴ�� ��������.
	////std::shared_ptr<CEnemy> pEnemy = m_pActorManager->CreateActor<CEnemy>(50, 50, 250, 250, Types::OT_ENEMY,
	////	Types::OS_IDLE, Types::DIR_DOWN, Types::Point(0.f, 1.0f), TEXT("Enemy"), this);

	////if (pEnemy == nullptr)
	////	return false;

	////m_strongActorList.emplace_back(pEnemy);

	////if (!CreateLayer(TEXT("Enemy"), 3))
	////	return false;

	////FindLayer(TEXT("Enemy"))->AddActor(pEnemy);

	//Prob ����
	std::shared_ptr<CProb> pProb = m_pActorManager->CreateActor<CProb>(800, 200, 0.f, 500.f, Types::OT_PROB,
		Types::OS_IDLE, Types::DIR_DOWN, Types::Point(0.f, 0.f), TEXT("Prob"), this);

	if (pProb == nullptr)
		return false;

	m_strongActorList.emplace_back(pProb);

	if (!CreateLayer(TEXT("Prob"), 4))
		return false;

	FindLayer(TEXT("Prob"))->AddActor(pProb);

	//Backgorund ����
	std::shared_ptr<CBackground> pBack = m_pActorManager->CreateActor<CBackground>(MAX_WIDTH, MAX_HEIGHT, 0.f, 0.f, Types::OT_BACKGROUND,
		Types::OS_IDLE, Types::DIR_IDLE, Types::Point(0.f, 0.f), TEXT("Background"), this);

	if (pBack == nullptr)
		return false;

	m_strongActorList.emplace_back(pBack);

	if (!CreateLayer(TEXT("Background"), 99))
		return false;

	FindLayer(TEXT("Background"))->AddActor(pBack);


	CScene::Init();


	return true;
}

void CGameScene::Update(double fDeltaTime)
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

	//�浹�˻縦 �ߴ� Actor���� �ٽ� �˻��ϰԵ�.
	//	-> ���ľ���.
	for (auto first = m_strongActorList.begin(); first != m_strongActorList.end(); ++first) {
		for (auto second = first; second != m_strongActorList.end(); ++second) {
			if (first == second)		
				continue;
			m_pCollisionDetector->Update((*first), (*second));
		}
	}

}

void CGameScene::InputUpdate(double fDeltaTime)
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
void CGameScene::GameUpdate(double fDeltaTime)
{
	//Collsion detect between Actors
	CollisionDetect();
	
	//Component Update
	for (auto& actor : m_strongActorList) {
		actor->Update(fDeltaTime);
	}

	
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
	////ResetŰ �˻�
	//if (KEY_DOWN(VK_BACK)) {

	//	Init();
	//}

	for (auto& actor : m_strongActorList) {
		actor->Init();
	}

}

