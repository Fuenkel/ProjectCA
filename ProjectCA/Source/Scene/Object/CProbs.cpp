//Probs ��ü �����ϰ� Collision �׽����غ� ��.(05.30)

#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Scene\Object\CProbs.h"
#include "..\..\..\Include\Core\Components\ColliderBox.h"



//ProbSize�κ��� ���� Offset�� �������� ���� ���¿��� �ʱ�ȭ��.
//���� Offset�� �����ϰ� �Ǹ� �ٽ� ������ ��.(5.31)
CProbs::CProbs(UINT width, UINT height) :
	CObject(Types::OT_PROBS, Types::Point(0, 300), width, height),
	m_ProbSize(Types::Rect(m_fObjectPoint.x, m_fObjectPoint.y,
		m_fObjectPoint.x+(float)m_iObjectWidth, m_fObjectPoint.y+(float)m_iObjectHeight))
{

}


CProbs::CProbs(float left, float top, float right, float bottom) :
	CObject(Types::OT_PROBS, Types::Point(left, top), right - left, bottom - top),
	m_ProbSize( {left, top, right, bottom} )
{
	//Debug::MessageInfo(TEXT("Probs init"));

}

CProbs::~CProbs()
{

}

bool CProbs::Init()
{
	//������Ʈ�� �߰�
	//Debug::MessageInfo(TEXT("Add Box!"));
	AddComponent( TEXT("Collider"), new ColliderBox( (this), m_ProbSize ) );
	//TCHAR buf[1024];
	//wsprintf(buf, TEXT("width : %d, height : %d"), m_iWidth, m_iHeight);
	//Debug::MessageInfo(buf);

	//������Ʈ�� �ʱ�ȭ
	CObject::Init();

	return true;
}

void CProbs::Update(float deltaTime)
{

	CObject::Update(deltaTime);

}

void CProbs::Render(const HDC & hDC)
{

	Rectangle(hDC, m_ProbSize.left, m_ProbSize.top, 
		m_ProbSize.right, m_ProbSize.bottom);

	TCHAR temp[1024];
	ColliderBox* box = static_cast<ColliderBox*>(GetComponent(TEXT("Collider")));
	Types::Rect rect = box->GetBoxSize();

	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

	wsprintf(temp, TEXT("Box : (%3ld, %3ld, %3ld, %3ld)"), (LONG)rect.left, (LONG)rect.top, (LONG)rect.right, (LONG)rect.bottom);
	TextOut(hDC, 0, 60, temp, lstrlen(temp));

}

//void CProbs::LateUpdate(float fDeltaTime)
//{
//
//
//}
