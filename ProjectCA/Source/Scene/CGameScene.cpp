#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CGameScene.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Core\CCollisionManager.h"
#include "..\..\Include\Scene\Actor\CObjectManager.h"
#include "..\..\Include\Scene\CCameraManager.h"
#include "..\..\Include\Core\Components\Collider.h"
#include "..\..\Include\Core\Components\PhysicsComponent.h"
#include "..\..\Include\Core\Components\InputComponent.h"
#include "..\..\Include\Core\Components\TransformComponent.h"
#include "..\..\Include\Scene\CObject.h"
#include "..\..\Include\Scene\Actor\CActor.h"
#include "..\..\Include\Scene\Actor\CEnemy.h"
#include "..\..\Include\Scene\Actor\CKoopa.h"
#include "..\..\Include\Scene\Actor\CPlayer.h"
#include "..\..\Include\Scene\Actor\CProb.h"
#include "..\..\Include\Scene\Actor\CGround.h"
#include "..\..\Include\Scene\Actor\CCamera.h"
#include "..\..\Include\Scene\Actor\CBackground.h"
#include "..\..\Include\Scene\Actor\CMushroom.h"
#include "..\..\Include\Scene\Actor\CFlower.h"
//#include "..\..\Include\Scene\CWorld.h"



CGameScene::CGameScene(Types::SceneType type)
	:CScene(type), m_pObjectManager(nullptr), m_pPlayer(nullptr)
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
	//m_pObjectManager->Destroy();
	//m_ObjectPtrList.clear();
	puts("Destroy Game");
	CCollisionManager::GetInstance()->Destroy();
}

//Layer�켱���� 0���� ���� UI�� �� ������.
bool CGameScene::Init()
{
	if (!CCollisionManager::GetInstance()->Init())
		return false;

	////if(m_pCurWorld == nullptr)
	////	m_pCurWorld = new CWorld;

	//Player ����
	m_pPlayer = m_pObjectManager->CreateActor<CPlayer>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 0, 0, Types::AT_PLAYER,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_RIGHT, TEXT("Player"), this);

	m_ObjectPtrList.emplace_back(m_pPlayer);

	if (m_pPlayer == nullptr)
		return false;

	auto pCamera = CCameraManager::GetInstance()->CreateCamera(m_pPlayer, MAX_WIDTH, MAX_HEIGHT);
	if (pCamera.expired())
	{
		return false;
	}
	pCamera.lock()->SetCameraMode(CCamera::CM_SCROLL_HOR);
	//ī�޶� ����
	m_pPlayer->AttachCamera(pCamera.lock());
	SetSceneMainCamera(pCamera.lock());
	
	if (!CreateLayer(TEXT("Player"), 2))
		return false;

	FindLayer(TEXT("Player"))->AddActor(m_pPlayer);
	

	//Enemy ����
	std::shared_ptr<CKoopa> pEnemy = m_pObjectManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 250.f, 250.f, Types::AT_ENEMY,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
	if (pEnemy == nullptr)
		return false;

	m_ObjectPtrList.emplace_back(pEnemy);
	if (!CreateLayer(TEXT("Enemy"), 4))
		return false;
	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);


	pEnemy = m_pObjectManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 200.f, 250.f, Types::AT_ENEMY,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
	if (pEnemy == nullptr)
		return false;

	m_ObjectPtrList.emplace_back(pEnemy);
	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);


	pEnemy = m_pObjectManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 150.f, 250.f, Types::AT_ENEMY,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
	if (pEnemy == nullptr)
		return false;

	m_ObjectPtrList.emplace_back(pEnemy);
	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);


	pEnemy = m_pObjectManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 300.f, 250.f, Types::AT_ENEMY,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
	if (pEnemy == nullptr)
		return false;

	m_ObjectPtrList.emplace_back(pEnemy);
	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);


	//�׽�Ʈ�� Mushroom ����
	std::shared_ptr<CActor> pPickup = m_pObjectManager->CreateActor<CMushroom>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 300.f, 150.f, Types::AT_PICKUP,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_RIGHT, TEXT("Mushroom"), this);
	if (pPickup == nullptr)
		return false;
	if (!CreateLayer(TEXT("Pickup"), 3))
		return false;
	FindLayer(TEXT("Pickup"))->AddActor(pPickup);
	m_ObjectPtrList.emplace_back(pPickup);

	//�׽�Ʈ�� Flower ����
	pPickup = m_pObjectManager->CreateActor<CFlower>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 300.f, 150.f, Types::AT_PICKUP,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_RIGHT, TEXT("Flower"), this);
	if (pPickup == nullptr)
		return false;
	FindLayer(TEXT("Pickup"))->AddActor(pPickup);
	m_ObjectPtrList.emplace_back(pPickup);


	//Prob ����
	if (!CreateLayer(TEXT("Prob"), 10))
		return false;

	std::shared_ptr<CGround> pGround = m_pObjectManager->CreateActor<CGround>(8192, 256, 400.f, 700.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pObjectManager->CreateActor<CGround>(256, 160, -400.f, 500.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pObjectManager->CreateActor<CGround>(256, 160, 0.f, 350.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pObjectManager->CreateActor<CGround>(256, 160, 400.f, 350.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround== nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pObjectManager->CreateActor<CGround>(256, 160, 800.f, 350.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pObjectManager->CreateActor<CGround>(256, 160, 1200.f, 500.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);


	


	//Backgorund ����
	std::shared_ptr<CBackground> pBack = m_pObjectManager->CreateObject<CBackground>(MAX_WIDTH, MAX_HEIGHT, 0.f, 0.f, TEXT("Background"), this);

	if (pBack == nullptr)
		return false;
	
	pBack->SetBackgroundImage(TEXT("BackgroundMountain2"));
	m_ObjectPtrList.emplace_back(pBack);

	if (!CreateLayer(TEXT("Background"), 99))
		return false;

	FindLayer(TEXT("Background"))->AddActor(pBack);



	CScene::Init();

	return true;
}

void CGameScene::Update(double fDeltaTime)
{

	if (m_pPlayer->IsActive())
	{
		//1. �Է¿� ���� ���� ���� �� �浹 �˻� �� �׿� ���� Actor��� ���� ������Ʈ ���� Update
		GameUpdate(fDeltaTime);

		//Layer Update -> Rendering�� �����ϱ� �� expired�� ��ü�� �ִ��� �˻��ϱ� ����.
		CScene::Update(fDeltaTime);
	}
	if (KEY_ONCE_PRESS(VK_ESCAPE))
	{
		puts("reset");
		ResetScene();
	}
}

void CGameScene::Render(const HDC& hDC)
{
	//Layer��ü�� �����ϴ� Actor���� Rendering
	CScene::Render(hDC);

}

void CGameScene::CollisionDetect()
{
	//////Scene���� ��� Actor�鿡 ���� �浹�˻� ����
	//for (auto first = m_ObjectPtrList.begin(); first != m_ObjectPtrList.end(); ++first) {
	//	if ((*first)->IsActive())
	//	{
	//		for (auto second = first; second != m_ObjectPtrList.end(); ++second) {
	//			if (first == second)
	//			{
	//				continue;
	//			}
	//			if ((*second)->IsActive())
	//			{
	//				CCollisionManager::GetInstance()->CheckCollision((*first), (*second));
	//			}
	//		}
	//	}
	//}

	

}

void CGameScene::InputUpdate(double fDeltaTime)
{



}

void CGameScene::GameUpdate(double dDeltaTime)
{	
	if (!m_pPlayer->IsDead())
	{

		//Actor Update
		for (const auto& actor : m_ObjectPtrList) {
			if (actor->IsActive())
			{
				actor->Update(dDeltaTime);
			}
		}

		//Collsion detect between Actors
		//CollisionDetect();
		CCollisionManager::GetInstance()->CheckCollision();
		CCameraManager::GetInstance()->GetMainCamera().lock()->Update(dDeltaTime);
	}
	else
	{
		m_pPlayer->DeadProcess(dDeltaTime);
	}
	
	//Adjust Position on Screen 
	for (const auto& object : m_ObjectPtrList)
	{
		//if (actor->GetActorType() != Types::AT_BACKGROUND)
		{
			if (object->IsActive())
			{
				object->LateUpdate();
				//object->GetComponent<TransformComponent>().lock()->AdjustScreenPosition();
			}
		}
	}

	//if (KEY_ONCE_PRESS(VK_ESCAPE))
	//{
	//	puts("reset");
	//	ResetScene();
	//}

}



