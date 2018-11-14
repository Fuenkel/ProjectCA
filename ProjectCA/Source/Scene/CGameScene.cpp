#include "..\..\stdafx.h"
#include "..\..\Include\Scene\CGameScene.h"
#include "..\..\Include\Scene\CLayer.h"
#include "..\..\Include\Core\CCollisionManager.h"
#include "..\..\Include\Scene\Actor\CActorManager.h"
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
//#include "..\..\Include\Scene\CWorld.h"



CGameScene::CGameScene(Types::SceneType type)
	:CScene(type), m_pActorManager(nullptr), m_pPlayer(nullptr)
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
	//m_pActorManager->Destroy();
	//m_ObjectPtrList.clear();
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
	m_pPlayer = m_pActorManager->CreateActor<CPlayer>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 0, 0, Types::AT_PLAYER,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_RIGHT, TEXT("Player"), this);

	m_ObjectPtrList.emplace_back(m_pPlayer);

	if (m_pPlayer == nullptr)
		return false;

	StrongCameraPtr pCamera = CCameraManager::GetInstance()->CreateCamera(m_pPlayer, MAX_WIDTH, MAX_HEIGHT).lock();
	if (pCamera == nullptr)
	{
		return false;
	}
	pCamera->SetCameraMode(CCamera::CM_SCROLL_HOR);
	//ī�޶� ����
	m_pPlayer->AttachCamera(pCamera);

	if (!CreateLayer(TEXT("Player"), 2))
		return false;

	FindLayer(TEXT("Player"))->AddActor(m_pPlayer);
	

	//Enemy ����
	std::shared_ptr<CKoopa> pEnemy = m_pActorManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 250.f, 250.f, Types::AT_ENEMY,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
	if (pEnemy == nullptr)
		return false;

	m_ObjectPtrList.emplace_back(pEnemy);
	if (!CreateLayer(TEXT("Enemy"), 3))
		return false;
	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);


	pEnemy = m_pActorManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 200.f, 250.f, Types::AT_ENEMY,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
	if (pEnemy == nullptr)
		return false;

	m_ObjectPtrList.emplace_back(pEnemy);
	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);


	pEnemy = m_pActorManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 150.f, 250.f, Types::AT_ENEMY,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
	if (pEnemy == nullptr)
		return false;

	m_ObjectPtrList.emplace_back(pEnemy);
	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);


	pEnemy = m_pActorManager->CreateActor<CKoopa>(SPRITE_WIDTH*2.5, SPRITE_HEIGHT*2.5, 300.f, 250.f, Types::AT_ENEMY,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_RUN, Types::DIR_LEFT, TEXT("KoopaGreen"), this);
	if (pEnemy == nullptr)
		return false;

	m_ObjectPtrList.emplace_back(pEnemy);
	FindLayer(TEXT("Enemy"))->AddActor(pEnemy);



	//Prob ����
	if (!CreateLayer(TEXT("Prob"), 4))
		return false;

	std::shared_ptr<CGround> pGround = m_pActorManager->CreateActor<CGround>(8192, 256, 400.f, 700.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pActorManager->CreateActor<CGround>(256, 160, 400.f, 350.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround== nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pActorManager->CreateActor<CGround>(256, 160, 800.f, 350.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pActorManager->CreateActor<CGround>(256, 160, 1200.f, 350.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pActorManager->CreateActor<CGround>(256, 160, 0.f, 350.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);

	pGround = m_pActorManager->CreateActor<CGround>(256, 160, -400.f, 350.f, Types::AT_PROB,
		Types::AS_IDLE, Types::VS_IDLE, Types::HS_IDLE, Types::DIR_IDLE, TEXT("Prob"), this);
	if (pGround == nullptr)
		return false;
	m_ObjectPtrList.push_back(pGround);
	FindLayer(TEXT("Prob"))->AddActor(pGround);


	//Backgorund ����
	std::shared_ptr<CBackground> pBack = m_pActorManager->CreateObject<CBackground>(MAX_WIDTH, MAX_HEIGHT, 0.f, 0.f, TEXT("Background"), this);

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

	CCollisionManager::GetInstance()->CheckCollision();

}

void CGameScene::InputUpdate(double fDeltaTime)
{



}

void CGameScene::GameUpdate(double dDeltaTime)
{	
	//Actor Update
	for (const auto& actor : m_ObjectPtrList) {
		if (actor->IsActive())
		{
			actor->Update(dDeltaTime);
		}
	}

	//Collsion detect between Actors
	CollisionDetect();
	CCameraManager::GetInstance()->GetMainCamera().lock()->Update(dDeltaTime);
	//std::cout << "Address : " << CCameraManager::GetInstance() << "\n";
	//Adjust Position on Screen 
	for (const auto& actor : m_ObjectPtrList)
	{
		//if (actor->GetActorType() != Types::AT_BACKGROUND)
		{
			if (actor->IsActive())
			{
				actor->GetComponent<TransformComponent>().lock()->AdjustScreenPosition();
			}
		}
	}

}



