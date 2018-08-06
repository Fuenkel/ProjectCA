//Probs ��ü �����ϰ� Collision �׽����غ� ��.(05.30)

#include "..\..\..\stdafx.h"
#include "..\..\..\Include\Scene\Object\CProbs.h"
#include "..\..\..\Include\Core\Components\ColliderBox.h"



//ProbSize�κ��� ���� Offset�� �������� ���� ���¿��� �ʱ�ȭ��.
//���� Offset�� �����ϰ� �Ǹ� �ٽ� ������ ��.(5.31)
CProbs::CProbs()
	:CObject(Types::OT_PROBS)
{

}


CProbs::~CProbs()
{

}

bool CProbs::Init(Types::Point point, UINT iWidth, UINT iHeight,
	Types::ObjectState state, Types::Direction dir)
{
	bool ret;

	//m_ProbSize = new Types::Rect(point.x, point.y, point.x + iWidth, point.y + iHeight);
	//������Ʈ�� �߰�
	//Debug::MessageInfo(TEXT("Add Box!"));
	ret = AddComponent( TEXT("Collider"), new ColliderBox(this) );
	//TCHAR buf[1024];
	//wsprintf(buf, TEXT("width : %d, height : %d"), m_iWidth, m_iHeight);
	//Debug::MessageInfo(buf);

	//������Ʈ��, ������Ʈ �Ӽ� �ʱ�ȭ
	ret = CObject::Init(point, iWidth, iHeight, state, dir);

	return ret;
}

void CProbs::Update(float deltaTime)
{

	CObject::Update(deltaTime);

}

void CProbs::Render(const HDC & hDC)
{

	Rectangle(hDC, m_fObjectPoint.x, m_fObjectPoint.y, 
		m_fObjectPoint.x + m_iObjectWidth, m_fObjectPoint.y + m_iObjectHeight);

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
