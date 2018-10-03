#include "..\..\stdafx.h"
#include "..\..\Include\Core\CResourceManager.h"
#include "..\..\Include\Core\Graphic\CSprite.h"


CResourceManager::CResourceManager() {

}

CResourceManager::~CResourceManager() {

	m_strongSpriteTable.clear();

}

bool CResourceManager::Init() {

	//if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_idle_left.bmp"), TEXT("PlayerIdleLeft")))
	//	return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Background/background_mountain1.bmp"), TEXT("BackgroundMountain")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Background/background_mountain2.bmp"), TEXT("BackgroundMountain2")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_idle_right.bmp"), TEXT("PlayerIdleRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_idle_left.bmp"), TEXT("PlayerIdleLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_move_right.bmp"), TEXT("PlayerMoveRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_move_left.bmp"), TEXT("PlayerMoveLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_lookup_right.bmp"), TEXT("PlayerLookupRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_lookup_left.bmp"), TEXT("PlayerLookupLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_sitdown_right.bmp"), TEXT("PlayerSitdownRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_sitdown_left.bmp"), TEXT("PlayerSitdownLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_run_right.bmp"), TEXT("PlayerRunRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/mario_big_run_left.bmp"), TEXT("PlayerRunLeft")))
		return false;


	return true;
}


WeakSpritePtr CResourceManager::GetWeakSprtiePtr(const Types::tstring & strName)
{
	//���� ��� nullptr ��ȯ
	if(m_strongSpriteTable.find(strName) == m_strongSpriteTable.end())
		return WeakSpritePtr();

	//�ִ� ��� �ش� Sprite�� ������ ��ȯ
	return m_strongSpriteTable[strName];
}

bool CResourceManager::AddSpritePtr(const Types::tstring & strName, CSprite * pSprite)
{
	if (pSprite == nullptr)
		return false;

	//�ش� Ű���� �����ϴ� sprite�� �̹� �����ϴ� ���
	if(m_strongSpriteTable.find(strName) != m_strongSpriteTable.end())
		return false;

	StrongSpritePtr pStrongSprite = std::shared_ptr<CSprite>(pSprite);
	m_strongSpriteTable.insert(std::make_pair(strName, pStrongSprite));
	
	return true;
}

bool CResourceManager::DeleteSpritePtr(const Types::tstring & strName)
{
	//�̹� ���̺� �������� �ʴ� ���
	if (m_strongSpriteTable.find(strName) == m_strongSpriteTable.end())
		return false;

	m_strongSpriteTable.erase(strName);

	return true;
}

bool CResourceManager::AddSpriteUsePath(const Types::tstring & strPath, const Types::tstring & strName)
{
	//�̹� �����ϴ� ���
	if (m_strongSpriteTable.find(strName) != m_strongSpriteTable.end())
		return false;

	StrongSpritePtr pSprite = StrongSpritePtr(new CSprite);

	if(!pSprite->Init(strPath))
		return false;
	
	m_strongSpriteTable.insert(std::make_pair(strName, pSprite));

	return true;

}
