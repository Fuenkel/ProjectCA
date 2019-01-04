#pragma once

#include "..\..\stdafx.h"
#include "..\Singleton.hpp"
#include "Actor\CCamera.h"

//NOTE: Camera��ü���� �����ϱ� ���� Manager Class
//			Camera�� ����, ����, MainCamera���� ���� �����.

class CEntity;

typedef std::shared_ptr<CCamera> StrongCameraPtr;
typedef std::weak_ptr<CCamera> WeakCameraPtr;
typedef std::list<StrongCameraPtr> StrongCameraList;

class CCameraManager : public Singleton<CCameraManager> {

	DECLARE_SINGLETON(CCameraManager)

public:
	bool Init();
	void Update(double dDeltaTime);


public:
	void					ResetCameraList();
	WeakCameraPtr	CreateCamera(std::shared_ptr<CEntity> pOwner, UINT iWidth, UINT iHeight);
	void					AddCamera(StrongCameraPtr pCamera);
	bool					DeleteCamera(StrongCameraPtr pCamera);
	void					ChangeMainCamera(StrongCameraPtr pCamera);
	void					ChangeMainCameraMode(CCamera::CameraMode mode);
	void					Clear();


public:
	WeakCameraPtr GetMainCamera();
	StrongCameraPtr GetCamera(CAMERA_ID);


private:



private:
	StrongCameraList	m_CameraList;
	WeakCameraPtr	m_pMainCamera;
	CAMERA_ID			m_LastCameraID;

};