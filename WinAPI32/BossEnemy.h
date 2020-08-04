#pragma once
#include "Manager.h"
class BossEnemy : public EnemyManager
{
	bool m_bMove;
	BYTE m_Alpha;
	FRECT m_HPBar;
	float m_Percent;
	float m_MaxHp;
public:
	BossEnemy(float Xpos, float Ypos, float Width, float Height, int m_MaxBulletCount);
	BossEnemy();
	void GradientRender();
	~BossEnemy();
	void SetHPPercent(float Damage);
	HRESULT init() override;
	void release() override;
	void update() override;
	void SetDirect() override;
	void render() override;
	bool OnDisplay() override;
	void RandomPartern();
	bool BossDie();
	void SetInit(float Xpos, float Ypos, float Width, float Height, int m_MaxBulletCount);
};

