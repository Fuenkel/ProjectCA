#pragma once

/*
	NOTE:
		���� �� ��� Scene���� �⺻ ���۵��� �����س��� Class.
		Layer��ü���� List�� ������.
		Scene�� ��ü���� ������ �� Class�� ����� �� ���� �����ؾ���.
*/

//TODO(09.15) : Layer ���� ���ֹ����� �ϴ� ������� �ǰԲ� ������.
#include "..\..\stdafx.h"

class CLayer;

class CScene {

public:
	CScene(Types::SceneType);
	virtual ~CScene();


public:
	virtual bool Init();
	virtual void Update(double deltaTime);
	virtual void Render(const HDC& hDC);


public:
	bool CreateLayer(const Types::tstring& tag, int order);	//Layer������ ������ ������ �޼ҵ�
	bool DeleteLayer(const Types::tstring& tag);
	CLayer* FindLayer(const Types::tstring& tag);


private:
	static bool CompareLayer(CLayer* first, CLayer* second);
	void SortLayer() { m_LayerList.sort(CompareLayer); }


protected:
	Types::SceneType					m_SceneType;
	std::list<CLayer*>					m_LayerList;
	std::list<CLayer*>::iterator		m_it;


};
