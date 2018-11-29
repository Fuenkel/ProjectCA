#pragma once

/*
	NOTE:
		���� �� ��� Scene���� �⺻ ���۵��� �����س��� Class.
		Layer��ü���� List�� ������.
		Scene�� ��ü���� ������ �� Class�� ����� �� ���� �����ؾ���.
*/

//TODO(09.15) : Layer ���� ���ֹ����� �ϴ� ������� �ǰԲ� ������.
#include "..\..\stdafx.h"

class CObject;
class CCamera;
class CLayer;

typedef std::shared_ptr<CObject> ObjectPtr;
typedef std::weak_ptr<CObject> WeakObjPtr;

class CScene {

public:
	CScene(Types::SceneType);
	virtual ~CScene();


public:
	void			StartScene();
	virtual bool Init();
	virtual void Update(double dDeltaTime);
	virtual void Render(const HDC& hDC);
	

public:
	bool		CreateLayer(const Types::tstring& tag, int order);	//Layer������ ������ ������ �޼ҵ�
	bool		DeleteLayer(const Types::tstring& tag);
	CLayer*	FindLayer(const TSTRING& strTag);


public:
	void				AddObjectToScene(CObject* pObject);
	void				AddObjectToScene(std::shared_ptr<CObject> pObject);
	bool				DeleteObjectFromScene(CObject* pObject);
	bool				DeleteObjectFromScene(UINT iObjectID);
	WeakObjPtr		FindObjectFromScene(CObject* pObject);
	WeakObjPtr		FindObjectFromScene(const TSTRING& strObjectName);
	WeakObjPtr		FindObjectFromScene(UINT iObjectID);
	WeakObjPtr		FindInactiveObjectFromScene(CObject* pObject);
	WeakObjPtr		FindInactiveObjectFromScene(const TSTRING& strObjectName);


public:
	void SetSceneMainCamera(std::shared_ptr<CCamera> pCamera);
	

public:
	virtual void ResetScene();


private:
	static bool CompareLayer(CLayer* first, CLayer* second);
	void SortLayer() { m_LayerList.sort(CompareLayer); }


protected:
	bool									m_bActive;
	Types::SceneType					m_SceneType;
	std::list<CLayer*>					m_LayerList;
	std::list<CLayer*>::iterator		m_it;
	std::weak_ptr<CCamera>		m_pMainCameraPtr;


protected:
	typedef std::list<ObjectPtr>	StrongObjecPtrList;
	StrongObjecPtrList				m_ObjectPtrList;

};
