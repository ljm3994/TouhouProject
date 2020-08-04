#pragma once
#include "ProduceOption.h"
#include "GameNode.h"
#include "EnemyBullet.h"

class EnemyManager : public GameNode
{
protected:
	list<EnemyBullet*> m_Bullet;                        // 총알을 담는 리스트
	list<EnemyBullet*>::iterator m_BulletIt;                 
	ProduceOption m_Option;                        // 적 옵션(체력, 총알 유형, 속도 등등 설정 가능)
	Flight_Data m_FData;                          // 비행 옵션(해당 옵션으로 비행 각도 및 속도 조절 가능)
	Vecter m_pos;                                      // 현재 적 위치
	FRECT m_rc;                                          // 렉트
	BULLET_TYPE m_Type;                       // 현재 총알 유형
	bool m_MoveEsc;                              //현재 움직일 수 있는지 여부
	bool m_IsFire;                                     // 현재 사격 가능한지 여부
	float m_UpdateDelayTime;                // update 딜레이 시간
	float m_DelayTime;                              // 다음 움직임까지 딜레이 시간
	float m_DelayReload;                         // 총알 재장전 딜레이 시간
	int m_MaxBulletCount;                       // 최대 총알 발사 횟수
	int m_CurrentBulletCount;                      // 현재 발사한 총할 횟수
	FRECT m_Stage;                                  // 현재 맵 크기
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

