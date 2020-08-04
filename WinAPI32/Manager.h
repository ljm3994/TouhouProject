#pragma once
#include "ProduceOption.h"
#include "GameNode.h"
#include "EnemyBullet.h"

class EnemyManager : public GameNode
{
protected:
	list<EnemyBullet*> m_Bullet;                        // �Ѿ��� ��� ����Ʈ
	list<EnemyBullet*>::iterator m_BulletIt;                 
	ProduceOption m_Option;                        // �� �ɼ�(ü��, �Ѿ� ����, �ӵ� ��� ���� ����)
	Flight_Data m_FData;                          // ���� �ɼ�(�ش� �ɼ����� ���� ���� �� �ӵ� ���� ����)
	Vecter m_pos;                                      // ���� �� ��ġ
	FRECT m_rc;                                          // ��Ʈ
	BULLET_TYPE m_Type;                       // ���� �Ѿ� ����
	bool m_MoveEsc;                              //���� ������ �� �ִ��� ����
	bool m_IsFire;                                     // ���� ��� �������� ����
	float m_UpdateDelayTime;                // update ������ �ð�
	float m_DelayTime;                              // ���� �����ӱ��� ������ �ð�
	float m_DelayReload;                         // �Ѿ� ������ ������ �ð�
	int m_MaxBulletCount;                       // �ִ� �Ѿ� �߻� Ƚ��
	int m_CurrentBulletCount;                      // ���� �߻��� ���� Ƚ��
	FRECT m_Stage;                                  // ���� �� ũ��
	Vecter * m_PlayerPos;
public:
	EnemyManager(float Xpos, float Ypos, float Width, float Height, int MaxBulletCount);
	EnemyManager();
	~EnemyManager();
	void SetProperty(ProduceOption Option);
	ProduceOption GetProperty();
	void LoadBullet(FIRE_TYPE type);
	void SetMoveEsc(bool Move);
	void EnemyMove(float Time);
	bool GetFire();
	void SetFire(bool Fire);
	void SetFlightData(Flight_Data data);
	Vecter GetPos();
	Flight_Data GetFlightData();
	int GetCurrentBullet();
	void SetCurrentBullet(int Count);
	void ShootUpdate(float Time);
	bool GetMoveEsc();
	void SetDie(bool Die);
	bool GetDie();
	void BulletUpdate();
	FRECT GetEnemy();
	virtual void SetDirect();
	bool isBulletAllRemove();
	bool isPlayerKill(FRECT m_Player);
	void SetPlayerPos(Vecter * pos);
	void DirectMove(ENEMY_DIRECT direct, float Time);
	void SetStage(FRECT Stage);
	virtual bool OnDisplay();
	virtual void SetInit(float Xpos, float Ypos, float Width, float Height, int m_MaxBulletCount) = 0;
};

