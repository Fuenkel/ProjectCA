#pragma once

/*
	NOTE:
		Scene���� ���� ī�װ��� Object(or Actor)���� �����ϱ� ���� Class.
		Object(or Actor)���� shared_ptr�� �����ϰ�, �ٸ� Class���� weak_ptr�� ��ȯ�ϵ��� ��.(08.17);
		->Layer Class�� ������ Rendering������ ����ϱ��(08.31)
*/

#include "..\..\stdafx.h"
#include "CScene.h"

class CActor;
class CObject;

class CLayer {
	//Scene Class������ Layer ����, �ı� ����.
	friend class CScene;
	friend class CGameScene;


private:
	//��� friend���� �޼ҵ带 ������ �ܺο����� ������ ���� ���� private���� ����
	//CLayer(int order, const Types::tstring& tag);
	CLayer();
	~CLayer();


public:
	bool Init(const Types::tstring& strTag, UINT iOrder);
	void Update(double fDeltaTime);
	void Render(const HDC& hDC);
	void Destroy();


public:
	void AddActor(std::shared_ptr<CObject> pActor);
	//Actor���� �޼ҵ�� 2������ �����ε� ���� ����.
	//bool DeleteActor(Types::ActorID actorID);
	bool DeleteActor(std::shared_ptr<CObject>& pActor);


public:
	//std::weak_ptr<CObject> FindObject(Types::ActorID actorID);
	std::weak_ptr<CObject> FindObject(const std::shared_ptr<CObject>& pActor);
	const std::list<std::weak_ptr<CObject>>& GetActorList() const;


public:
	inline const Types::tstring& GetLayerTag() const { return m_strLayerTag; }
	inline void SetLayerTag(const Types::tstring& tag) { m_strLayerTag = tag; }
	inline int GetLayerOrder() { return m_iOrder; }
	inline void SetLayerOrder(int order) { if (order >= 0) m_iOrder = order; }
	inline UINT GetLastActorNumber() const { return m_iActorNumber; }


private:
	int												m_iOrder;
	UINT											m_iActorNumber;	//�Ⱦ��Ե� �� ����.(08.14)
	Types::tstring								m_strLayerTag;
	std::list<std::weak_ptr<CObject>>		m_ObjectList;


};