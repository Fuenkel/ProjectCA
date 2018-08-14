#pragma once


#include "..\..\stdafx.h"
#include "CScene.h"
#include "Actor\CActor.h"

//class CObject;
//class CActor;

class CLayer {
	//Scene Class������ Layer ����, �ı� ����.
	friend class CScene;
	friend class CGameScene;

	//CWorld���� Layer���� �����ϰԲ� ���������� �� CWorld Class���� ������ �ı��� ��� �� �� �ֵ��� ����(08.14)
	friend class CWorld;
private:
	//��� friend���� �޼ҵ带 ������ �ܺο����� ������ ���� ���� private���� ����
	//CLayer(int order, const Types::tstring& tag);
	CLayer();
	~CLayer();


public:
	bool Init(const Types::tstring& strTag, UINT iOrder);
	void Update(float fDeltaTime);
	void Render(const HDC& hDC);
	void LateUpdate(float fDeltaTime);

public:
	void AddActor(CActor* pActor);
	//Actor���� �޼ҵ�� 2������ �����ε� ���� ����.
	bool DeleteActor(ActorID actorID);
	bool DeleteActor(CActor* pActor);


public:
	inline const std::list<CActor*>& GetObjectList() const { return m_actorList; }
	CActor* FindActor(ActorID actorID);
	CActor* FindActor(CActor* pActor);


	//Object�� Actor�� ��ü�ϸ� �Ⱦ��� �� �Լ���.(08.14)
//public:
	//void AddObjectToLayer(CObject* object);
	//bool DeleteObjectFromLayer(CObject * object);


public:
	//inline const std::list<CObject*>& GetObjectList() const { return m_ObjectList; }
	inline const Types::tstring& GetLayerTag() const { return m_strLayerTag; }
	inline void SetLayerTag(const Types::tstring& tag) { m_strLayerTag = tag; }
	inline int GetLayerOrder() { return m_iOrder; }
	inline void SetLayerOrder(int order) { if (order >= 0) m_iOrder = order; }
	inline UINT GetLastActorNumber() const { return m_iActorNumber; }

private:



private:
	int											m_iOrder;
	UINT										m_iActorNumber;	//�Ⱦ��Ե� �� ����.(08.14)
	Types::tstring							m_strLayerTag;
	std::list<CActor*>						m_actorList;

	//Actor�� ��ü�ϸ鼭 �ʿ������.(08.14)
//private:
//	std::list<CObject*>					m_ObjectList;
//	std::list<CObject*>::iterator			m_it;



};