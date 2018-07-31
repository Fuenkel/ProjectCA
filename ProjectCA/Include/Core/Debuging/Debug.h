//������ Ŭ����

#pragma once

#include "..\..\..\stdafx.h"
#include "..\..\Singleton.hpp"


class Debug : Singleton<Debug>{

	DECLARE_SINGLETON(Debug)

public:
	bool Init(UINT iPoolSize);
	bool Resize(UINT iPoolSize);
	void DrawingText(const Types::tstring& text, const HDC& hDC, int x, int y);


public:
	static void MessageInfo(const Types::tstring& text);
	static void MeesageError(const Types::tstring& text);
	

private:
	std::shared_ptr<BYTE>			m_pMemPool;	//ȭ�鿡 �ؽ�Ʈ ����� �� ����� �޸�Ǯ.
	const UINT							m_iMaxPoolSize;	//�޸�Ǯ �Ҵ�ũ�� �ִ�ġ ����(byte����)
	const UINT							m_iMaxLength;	//ȭ�鿡 ����� �ؽ�Ʈ�� �ִ� ���� ����.(byte����)


};