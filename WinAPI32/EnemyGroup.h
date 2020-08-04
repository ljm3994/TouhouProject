#pragma once
#include "Enemy.h"
#include "BossEnemy.h"
class EnemyGroup : public GameNode
{
	list<Enemy * > m_EnemyGroup;
	list<Enemy * >::iterator m_EnemyGroupit;
	BossEnemy * m_boss;
	FRECT m_Stage;
	int EnemyCount;
	float BossDelay;
	bool m_BossCreate;
	Vecter *m_playerpos;
public:
	EnemyGroup(FRECT Stage);
	EnemyGroup();
	~EnemyGroup();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	bool BossCreateis();
	void SetPlayerPos(Vecter *pos);
	void CreateEnemy();
	bool PlayerEnemyBulletColid(FRECT rc);
	bool PlayerBossEnemyBulletColid(FRECT rc);
	list<Enemy * > GetEnemy();
	BossEnemy * GetBoss();
};

