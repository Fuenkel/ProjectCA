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
#include "..\..\Include\Scene\Actor\CGoomba.h"
#include "..\..\Include\Scene\Actor\CPlayer.h"
#include "..\..\Include\Scene\Actor\CProb.h"
#include "..\..\Include\Scene\Actor\CGround.h"
#include "..\..\Include\Scene\Actor\CBlock.h"
#include "..\..\Include\Scene\Actor\CCamera.h"
#include "..\..\Include\Scene\Actor\CBackground.h"
#include "..\..\Include\Scene\Actor\CPickup.h"
#include "..\..\Include\Scene\Actor\CMushroom.h"
#include "..\..\Include\Scene\Actor\CFlower.h"
#include "..\..\Include\Scene\Actor\CCoin.h"
#include "..\..\Include\Scene\UI\CItemInfo.h"
#include "..\..\Include\Scene\UI\CNumberInterface.h"
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
	m_pPlayer = m_pObjectManager->CreateActor<CPlayer>(SPRITE_WIDTH*2.5f, SPRITE_HEIGHT*2.5f, 0, 0, Types::OT_PLAYER,
		Types::DIR_RIGHT, TEXT("Player"), this);
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

	m_ObjectPtrList.emplace_back(m_pPlayer);
	if (!CreateLayer(TEXT("Player"), 2))
		return false;

	FindLayer(TEXT("Player"))->AddActor(m_pPlayer);
	
	if (!BuildUI())
		return false;

	if (!BuildWorld())
		return false;

	//For test
	m_iCurScore = 52312;
	m_iCoinCount = 76;

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

std::weak_ptr<CPlayer> CGameScene::GetPlayerPtr()
{
	return m_pPlayer;
}

bool CGameScene::BuildUI()
{
	if (!CreateLayer(TEXT("UI"), 0))
		return false;
	
	//���� ����
	{
		auto pFont = m_pObjectManager->CreateObject<CInterface>(SPRITE_WIDTH * 5.f, SPRITE_HEIGHT * 2.5, MAX_WIDTH / 4.f, 45.f, Types::OT_UI, TEXT("FontMario"), this);
		if (pFont == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pFont);
		if (!pFont->SetImage(TEXT("UIMario")))
			return false;
		FindLayer(TEXT("UI"))->AddActor(pFont);

		pFont = m_pObjectManager->CreateObject<CInterface>(SPRITE_WIDTH * 2.5f, SPRITE_HEIGHT * 2.5f, MAX_WIDTH / 1.7f, 45.f, Types::OT_UI, TEXT("FontTime"), this);
		if (pFont == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pFont);
		if (!pFont->SetImage(TEXT("UITime")))
			return false;
		FindLayer(TEXT("UI"))->AddActor(pFont);

		pFont = m_pObjectManager->CreateObject<CInterface>(SPRITE_WIDTH * 2.5f, SPRITE_HEIGHT * 2.5f, MAX_WIDTH / 1.7f, 45.f, Types::OT_UI, TEXT("FontTime"), this);
		if (pFont == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pFont);
		if (!pFont->SetImage(TEXT("UITime")))
			return false;
		FindLayer(TEXT("UI"))->AddActor(pFont);
	}

	//8bitũ�� �׸�
	{
		auto pInterface = m_pObjectManager->CreateObject<CInterface>(SPRITE_WIDTH / 2.f, SPRITE_HEIGHT / 2.f, MAX_WIDTH / 4.4f, 65.f, Types::OT_UI, TEXT("FontX"), this);
		if (pInterface== nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pInterface);
		if (!pInterface->SetImage(TEXT("UIX")))
			return false;
		FindLayer(TEXT("UI"))->AddActor(pInterface);

		pInterface = m_pObjectManager->CreateObject<CInterface>(SPRITE_WIDTH / 2.f, SPRITE_HEIGHT / 2.f, MAX_WIDTH / 1.5f, 45.f, Types::OT_UI, TEXT("ImageCoin"), this);
		if (pInterface == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pInterface);
		if (!pInterface->SetImage(TEXT("UICoin")))
			return false;
		FindLayer(TEXT("UI"))->AddActor(pInterface);
		
		pInterface = m_pObjectManager->CreateObject<CInterface>(SPRITE_WIDTH / 2.f, SPRITE_HEIGHT / 2.f, MAX_WIDTH / 1.465f, 45.f, Types::OT_UI, TEXT("FontX"), this);
		if (pInterface == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pInterface);
		if (!pInterface->SetImage(TEXT("UIX")))
			return false;
		FindLayer(TEXT("UI"))->AddActor(pInterface);
	}

	//NumberInterface ����
	{
		//auto pNumberInterface = m_pObjectManager->CreateObject<CNumberInterface>(SPRITE_WIDTH / 2.f, SPRITE_HEIGHT / 2.f, MAX_WIDTH / 3.9f, 65.f, Types::OT_UI, TEXT("NumberLife"), this);
		//if (pNumberInterface == nullptr)
		//	return false;
		//pNumberInterface->SetDigit(2);
		//m_ObjectPtrList.emplace_back(pNumberInterface);
		//FindLayer(TEXT("UI"))->AddActor(pNumberInterface);

		//pNumberInterface = m_pObjectManager->CreateObject<CNumberInterface>(SPRITE_WIDTH / 2.f, SPRITE_HEIGHT / 2.f, MAX_WIDTH / 1.675f, 65.f, Types::OT_UI, TEXT("NumberTime"), this);
		//if (pNumberInterface == nullptr)
		//	return false;
		//pNumberInterface->SetDigit(3);
		//m_ObjectPtrList.emplace_back(pNumberInterface);
		//FindLayer(TEXT("UI"))->AddActor(pNumberInterface);

		auto pNumberInterface = m_pObjectManager->CreateObject<CNumberInterface>(SPRITE_WIDTH / 2.f, SPRITE_HEIGHT / 2.f, MAX_WIDTH / 1.375f, 45.f, Types::OT_UI, TEXT("NumberCoin"), this);
		if (pNumberInterface == nullptr)
			return false;
		pNumberInterface->SetDigit(2);
		pNumberInterface->LinkValuePtr(&m_iCoinCount);
		m_ObjectPtrList.emplace_back(pNumberInterface);
		FindLayer(TEXT("UI"))->AddActor(pNumberInterface);

		pNumberInterface = m_pObjectManager->CreateObject<CNumberInterface>(SPRITE_WIDTH / 2.f, SPRITE_HEIGHT / 2.f, MAX_WIDTH / 1.375f, 65.f, Types::OT_UI, TEXT("NumberScore"), this);
		if (pNumberInterface == nullptr)
			return false;
		pNumberInterface->SetDigit(6);
		pNumberInterface->LinkValuePtr(&m_iCurScore);
		m_ObjectPtrList.emplace_back(pNumberInterface);
		FindLayer(TEXT("UI"))->AddActor(pNumberInterface);
	}

	//ItemInfo ����
	{
		auto pInfo = m_pObjectManager->CreateObject<CItemInfo>(SPRITE_WIDTH * 2.5, SPRITE_HEIGHT * 2.5, MAX_WIDTH / 2.f, 60.f, Types::OT_UI, TEXT("ItemInfo"), this);
		if (pInfo == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pInfo);
		FindLayer(TEXT("UI"))->AddActor(pInfo);
	}


	return true;
}

bool CGameScene::BuildWorld()
{
	//Enemy ����
	{
		if (!CreateLayer(TEXT("Enemy"), 4))
			return false;

		std::shared_ptr<CEnemy> pEnemy = m_pObjectManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 250.f, 250.f, Types::OT_ENEMY,
			Types::OS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
		if (pEnemy == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pEnemy);
		FindLayer(TEXT("Enemy"))->AddActor(pEnemy);

		pEnemy = m_pObjectManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 200.f, 250.f, Types::OT_ENEMY,
			Types::OS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
		if (pEnemy == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pEnemy);
		FindLayer(TEXT("Enemy"))->AddActor(pEnemy);

		pEnemy = m_pObjectManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 150.f, 250.f, Types::OT_ENEMY,
			Types::OS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
		if (pEnemy == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pEnemy);
		FindLayer(TEXT("Enemy"))->AddActor(pEnemy);

		pEnemy = m_pObjectManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 300.f, 250.f, Types::OT_ENEMY,
			Types::OS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
		if (pEnemy == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pEnemy);
		FindLayer(TEXT("Enemy"))->AddActor(pEnemy);

		pEnemy = m_pObjectManager->CreateActor<CGoomba>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 350.f, 250.f, Types::OT_ENEMY,
			Types::OS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("Goomba"), this);
		if (pEnemy == nullptr)
			return false;
		m_ObjectPtrList.emplace_back(pEnemy);
		FindLayer(TEXT("Enemy"))->AddActor(pEnemy);
	}

	//Pickup ����
	{
		if (!CreateLayer(TEXT("Pickup"), 3))
			return false;

		//�׽�Ʈ�� Mushroom ����
		std::shared_ptr<CPickup> pPickup = m_pObjectManager->CreateActor<CMushroom>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 300.f, 150.f, Types::OT_PICKUP,
			Types::OS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_RIGHT, TEXT("Mushroom"), this);
		if (pPickup == nullptr)
			return false;
		FindLayer(TEXT("Pickup"))->AddActor(pPickup);
		m_ObjectPtrList.emplace_back(pPickup);

		//�׽�Ʈ�� Flower ����
		pPickup = m_pObjectManager->CreateActor<CFlower>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 300.f, 150.f, Types::OT_PICKUP, Types::DIR_RIGHT, TEXT("Flower"), this);
		if (pPickup == nullptr)
			return false;
		FindLayer(TEXT("Pickup"))->AddActor(pPickup);
		m_ObjectPtrList.emplace_back(pPickup);

		//�׽�Ʈ�� Coin ����
		pPickup = m_pObjectManager->CreateActor<CCoin>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 330.f, 150.f, Types::OT_PICKUP, Types::DIR_RIGHT, TEXT("Coin"), this);
		if (pPickup == nullptr)
			return false;
		FindLayer(TEXT("Pickup"))->AddActor(pPickup);
		m_ObjectPtrList.emplace_back(pPickup);
	}
	
	//Prob ����
	{
		if (!CreateLayer(TEXT("Prob"), 10))
			return false;

		auto pGround = m_pObjectManager->CreateObject<CGround>(8192, 256, 400.f, 700.f, Types::OT_PROB, TEXT("Prob"), this);
		if (pGround == nullptr)
			return false;
		m_ObjectPtrList.push_back(pGround);
		FindLayer(TEXT("Prob"))->AddActor(pGround);

		pGround = m_pObjectManager->CreateObject<CGround>(256, 160, -400.f, 500.f, Types::OT_PROB, TEXT("Prob"), this);
		if (pGround == nullptr)
			return false;
		m_ObjectPtrList.push_back(pGround);
		FindLayer(TEXT("Prob"))->AddActor(pGround);

		pGround = m_pObjectManager->CreateObject<CGround>(256, 160, 0.f, 350.f, Types::OT_PROB, TEXT("Prob"), this);
		if (pGround == nullptr)
			return false;
		m_ObjectPtrList.push_back(pGround);
		FindLayer(TEXT("Prob"))->AddActor(pGround);

		//pGround = m_pObjectManager->CreateObject<CGround>(256, 160, 400.f, 350.f, Types::OT_PROB, TEXT("Prob"), this);
		//if (pGround== nullptr)
		//	return false;
		//m_ObjectPtrList.push_back(pGround);
		//FindLayer(TEXT("Prob"))->AddActor(pGround);

		pGround = m_pObjectManager->CreateObject<CGround>(256, 160, 800.f, 350.f, Types::OT_PROB, TEXT("Prob"), this);
		if (pGround == nullptr)
			return false;
		m_ObjectPtrList.push_back(pGround);
		FindLayer(TEXT("Prob"))->AddActor(pGround);

		pGround = m_pObjectManager->CreateObject<CGround>(256, 160, 1200.f, 500.f, Types::OT_PROB, TEXT("Prob"), this);
		if (pGround == nullptr)
			return false;
		m_ObjectPtrList.push_back(pGround);
		FindLayer(TEXT("Prob"))->AddActor(pGround);
	}

	//Block ����
	{
		if (!CreateLayer(TEXT("Block"), 9))
			return false;

		auto pBlock = m_pObjectManager->CreateObject<CBlock>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 400.f, 350.f, Types::OT_PROB, TEXT("Block"), this);
		if (pBlock == nullptr)
			return false;
		//Block�� ������ѳ��� Pickup ����
		std::shared_ptr<CPickup> pPickup = m_pObjectManager->CreateActor<CMushroom>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5,
			pBlock->GetObjectPosition().x, pBlock->GetObjectPosition().y - pBlock->GetObjectHeight() / 2.f, Types::OT_PICKUP, Types::OS_IDLE, Types::VS_IDLE, Types::HS_RUN,
			Types::DIR_RIGHT, TEXT("Mushroom"), this);
		FindLayer(TEXT("Pickup"))->AddActor(pPickup);
		m_ObjectPtrList.emplace_back(pPickup);
		if (pPickup == nullptr)
			return false;
		//Pickup set
		pBlock->SetStoredPickup(pPickup);
		m_ObjectPtrList.push_back(pBlock);
		FindLayer(TEXT("Block"))->AddActor(pBlock);
	}
	
	//Backgorund ����
	{
		if (!CreateLayer(TEXT("Background"), 99))
			return false;

		auto pBack = m_pObjectManager->CreateObject<CBackground>(MAX_WIDTH, MAX_HEIGHT, 0.f, 0.f, Types::OT_BACKGROUND, TEXT("Background"), this);
		if (pBack == nullptr)
			return false;
		pBack->SetBackgroundImage(TEXT("BackgroundMountain2"));
		m_ObjectPtrList.emplace_back(pBack);
		FindLayer(TEXT("Background"))->AddActor(pBack);
	}


	return true;
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
	for (auto it = m_ObjectPtrList.cbegin(); it != m_ObjectPtrList.cend(); ++it)
	{
		//if (actor->GetActorType() != Types::AT_BACKGROUND)
		{
			if ((*it)->IsActive())
			{
				(*it)->LateUpdate();
				//++it;
				//object->GetComponent<TransformComponent>().lock()->AdjustScreenPosition();
			}
			//else
			//{
			//	it = m_ObjectPtrList.erase(it);
			//}
		}
	}

	//if (KEY_ONCE_PRESS(VK_ESCAPE))
	//{
	//	puts("reset");
	//	ResetScene();
	//}

}



