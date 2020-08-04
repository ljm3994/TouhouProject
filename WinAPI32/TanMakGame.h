#pragma once
#include "EnemyGroup.h"
#include "Player.h"
#include "SideScreen.h"
#include "ItemManager.h"

class TanMakGame : public GameNode
{
	EnemyGroup m_EnemyGroup;
	Player m_Player;
	SideScreen m_side;
	FRECT m_Stage;
	UINT m_Score;
	bool m_bFirst;
	bool m_GameClear;
	Vecter Frame;
	float m_DelayTime;
	bool m_EndingFirst;
	BYTE m_Alpha;
	list<ItemManager*> m_Item;
	list<ItemManager *>::iterator m_Itemit;
	int a;
public:
	TanMakGame();
	~TanMakGame();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void EnemyKill();
	void ItemEat(ItemManager Item);
};

