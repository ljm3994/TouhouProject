#pragma once
#include "GameNode.h"
#include "Vecter.h"
enum ItemType
{
	ScoreItem,
	PowerItem
};
class ItemManager : public GameNode
{
	FRECT m_Item;
	Vecter m_Pos;
	float m_Speed;
	ItemType m_Type;
	FRECT m_stage;
public:
	ItemManager();
	~ItemManager();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	bool OnDisplay();
	FRECT GetRect();
	void SettingItem(Vecter Pos, ItemType Type);
	void SetStage(FRECT stage);
	bool PlayerItemEat(FRECT rc);
	ItemType GetType();
};

