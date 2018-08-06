#pragma once
/*
	NOTE:
		Resource���� ��θ� �����ϱ� ���� Manager Class.
		Singleton Class�� �ۼ�
*/

#include "..\..\stdafx.h"
#include "..\Singleton.hpp"


class CResourceManager : public Singleton<CResourceManager> {

	DECLARE_SINGLETON(CResourceManager)

public:



public:
	const Types::tstring& FindPath(const Types::tstring& path);
	bool AddPath(const Types::tstring& path);
	


private:



private:
	std::list<Types::tstring>			m_PathList;


};