#pragma once

	/*
		NOTE:
			���� ������ ��Ÿ���� ���� ����ϴ� Vector Ŭ����
	
	*/

#include "..\..\..\stdafx.h"

namespace CVector {

	class Vector2d {
	
	public:
		Vector2d(float fx = 0.f, float fy = 0.f);
		~Vector2d();


	public:
		Vector2d operator +(const Vector2d& other);
		Vector2d operator - (const Vector2d& other);
		//Vector2d operator * (const Vector2d& other);
		Vector2d& operator = (const Vector2d& other);
		bool operator == (const Vector2d& other);


	public:
		void SetVector(float fx, float fy);
		void Normalize();
		float GetVectorScale();
		Vector2d GetNormalVector();


	public:
		Types::Point GetVector() { return Types::Point(m_fX, m_fY); }
		
		
	public:
		static float DotProduct(const Vector2d&, const Vector2d&);	//�� ���� ��ǥ�� ��
		static float DotProduct(float, float, float);							//�� ������ ũ��, cos�� ��
		//static float CrossProduct(const Vector2d&, const Vector2d&);


	private:
		


	private:
		float m_fX;
		float m_fY;

	};


	class Vector3d {


	};



}