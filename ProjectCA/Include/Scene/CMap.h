#pragma once

/*
	NOTE:
		Stage Map���� ���� �� ����� ���� Class

*/

#include "..\..\stdafx.h"

typedef	std::vector<std::vector<Types::ObjectType>> MapVector;

struct TileInfo {

	

};


class CMap {

public:
	CMap();
	~CMap();


public:



private:



private:
	UINT						m_iMapWidth;
	UINT						m_iMapHeight;
	MapVector				m_mapState;


};