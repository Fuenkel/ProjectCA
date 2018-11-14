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

	if (!LoadPlayerSpriteInfo())
		return false;

	if (!LoadEnemySpriteInfo())
		return false;

	if (!LoadGroundTileImageInfo())
		return false;

	if (!LoadBackgroundImageInfo())
		return false;

	if (!LoadUIImageInfo())
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

bool CResourceManager::LoadPlayerSpriteInfo()
{
	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_idle_right.bmp"), TEXT("PlayerIdleRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_idle_left.bmp"), TEXT("PlayerIdleLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_walk_right.bmp"), TEXT("PlayerWalkRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_walk_left.bmp"), TEXT("PlayerWalkLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_lookup_right.bmp"), TEXT("PlayerLookupRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_lookup_left.bmp"), TEXT("PlayerLookupLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_sitdown_right.bmp"), TEXT("PlayerSitdownRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_sitdown_left.bmp"), TEXT("PlayerSitdownLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_run_right.bmp"), TEXT("PlayerRunRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_run_left.bmp"), TEXT("PlayerRunLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_jump_right.bmp"), TEXT("PlayerJumpRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_jump_left.bmp"), TEXT("PlayerJumpLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_falldown_right.bmp"), TEXT("PlayerFalldownRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_falldown_left.bmp"), TEXT("PlayerFalldownLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_run_jump_right.bmp"), TEXT("PlayerRunJumpRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_run_jump_left.bmp"), TEXT("PlayerRunJumpLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_turn_right.bmp"), TEXT("PlayerTurnRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Player/New/mario_big_turn_left.bmp"), TEXT("PlayerTurnLeft")))
		return false;


	return true;
}

bool CResourceManager::LoadEnemySpriteInfo()
{
	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Enemy/Koopa/koopa_green_walk_right.bmp"), TEXT("KoopaGreenWalkRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Enemy/Koopa/koopa_green_walk_left.bmp"), TEXT("KoopaGreenWalkLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Enemy/Koopa/koopa_green_damaged.bmp"), TEXT("KoopaGreenDamaged")))
		return false;

	return true;
}

bool CResourceManager::LoadGroundTileImageInfo()
{
	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_edge_left_bot.bmp"), TEXT("GroundEdgeLeftBot")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_edge_left_top.bmp"), TEXT("GroundEdgeLeftTop")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_edge_left_inner.bmp"), TEXT("GroundEdgeLeftInner")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_edge_right_bot.bmp"), TEXT("GroundEdgeRightBot")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_edge_right_top.bmp"), TEXT("GroundEdgeRightTop")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_edge_right_inner.bmp"), TEXT("GroundEdgeRightInner")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_line_bot.bmp"), TEXT("GroundLineBot")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_line_right.bmp"), TEXT("GroundLineRight")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_line_top.bmp"), TEXT("GroundLineTop")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_line_left.bmp"), TEXT("GroundLineLeft")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Tiles/ground_inner.bmp"), TEXT("GroundInner")))
		return false;


	return true;
}

bool CResourceManager::LoadBackgroundImageInfo()
{
	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Background/background_mountain1.bmp"), TEXT("BackgroundMountain1")))
		return false;

	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/Background/background_mountain2.bmp"), TEXT("BackgroundMountain2")))
		return false;

	return true;
}

bool CResourceManager::LoadUIImageInfo()
{
	if (!AddSpriteUsePath(TEXT("./Resources/Sprite/UI/Title/button.bmp"), TEXT("TestButton")))
		return false;

	return true;
}
