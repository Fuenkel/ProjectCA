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
	bool AddPath(const Types::tstring& pathTag, const Types::tstring& path);
	


private:



private:
	typedef std::unordered_map<Types::tstring, std::list<Types::tstring>>	ResourcePathTable;
	ResourcePathTable				m_pathTable;	


};