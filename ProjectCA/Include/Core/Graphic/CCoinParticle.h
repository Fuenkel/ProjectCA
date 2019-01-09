#pragma once

#include "..\..\..\stdafx.h"
#include "CParticle.h"

//NOTE: CParticle�� ��ӹ��� Particle��ü
//			Coin�� �����ϰų� CoinBlock�� �ǵ���� �� �߻��ϴ� Particle

class CCoinParticle : public CParticle
{
public:
	CCoinParticle();
	virtual ~CCoinParticle();


public:
	virtual bool PostInit(const ENTITY_DATA& data, CScene* pScene) override;
	virtual void Init() override;
	virtual void Render(const HDC& hDC) override;


private:
	virtual void ParticleUpdate(double dDeltaTime) override;


};
