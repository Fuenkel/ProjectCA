#pragma once

/*
	NOTE:
		Phoenix Singleton�� Template Class���·� ������ ����.
		Singleton���� �ۼ��ϰ� ���� Class�� �� Class�� ��ӹް�,
		DECLARE_SINGLETON ��ũ�θ� �������� �� �ۼ��ϸ��.
*/

#include "..\stdafx.h"

//Singleton ���� ��ũ��. Singleton Template�� 
//��ӹ��� class�� friend�� ��������.
#define DECLARE_SINGLETON(CLASS) \
		friend class Singleton<CLASS>;\
		private:\
			CLASS();\
			CLASS(const CLASS&);\
			~CLASS();


//Singleton Ŭ�������� �����ϱ� ���� Singleton Template
template <class T>
class Singleton {
public:
	static T* GetInstance() {
		if (m_pInstance == nullptr)
			m_pInstance = new T;

		return m_pInstance;
	}
	static void Destroy() {
		if (m_pInstance != nullptr) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


protected:
	Singleton() { };
	virtual ~Singleton() { };


private:
	static T* m_pInstance;
	
};

template <class T> T* Singleton<T>::m_pInstance = nullptr;