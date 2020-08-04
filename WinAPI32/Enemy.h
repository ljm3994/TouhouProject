#pragma once
#include "GameNode.h"
#include "ProduceOption.h"
#include "Manager.h"
class Enemy : public EnemyManager
{
	float DelayMove;
public:
	Enemy(float Xpos, float Ypos, float Width, float Height, int m_MaxBulletCount);
	Enemy();
	~Enemy();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void SetInit(float Xpos, float Ypos, float Width, float Height, int m_MaxBulletCount);
};

