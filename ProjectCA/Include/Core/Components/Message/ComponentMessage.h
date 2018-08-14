#pragma once

/*
	NOTE:
		������Ʈ�� ����� ���� Message��ü�� �������̽� ����.
		�� ������Ʈ Ư���� ���� �� Class�� ����� �� ���ο� Message Class �ۼ�.
*/

#include "..\..\..\..\stdafx.h"


class ComponentMessage {
public:
	enum MessageType { MT_COL, MT_PHYSICS, MT_INPUT };


public:
	ComponentMessage(MessageType type);
	virtual ~ComponentMessage() { };


public:
	virtual void GetComponentMessage() { };
	virtual void SetMessageType(MessageType msg) { m_msgType = msg; }


public:
	MessageType GetMessageType() const { return m_msgType; }


private:
	MessageType		m_msgType;


};