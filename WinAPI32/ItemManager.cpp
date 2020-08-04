#include "stdafx.h"
#include "ItemManager.h"


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

HRESULT ItemManager::init()
{
	m_Speed = 200.0f;
	return S_OK;
}

void ItemManager::release()
{
}

void ItemManager::update()
{
	//m_Pos.x -= (m_Speed * g_ETime);
	m_Pos.y += (m_Speed * g_ETime);

	m_Item = RectMakeCenter(m_Pos.x, m_Pos.y, 20, 20);
}

void ItemManager::render()
{
	switch (m_Type)
	{
	case PowerItem:
		IMGMANAGER->frameRender("Item", g_MemDC, 0, 0, m_Item.left, m_Item.top, 20, 20);
		break;
	case ScoreItem:
		IMGMANAGER->frameRender("Item", g_MemDC, 1, 0, m_Item.left, m_Item.top, 20, 20);
		break;
	}
}

bool ItemManager::OnDisplay()
{
	if (m_Pos.x - (m_Speed * g_ETime) < m_stage.left)
	{
		return true;
	}
	if (m_Pos.x + (m_Speed * g_ETime) > m_stage.right)
	{
		return true;
	}
	if (m_Pos.y - (m_Speed * g_ETime) < m_stage.top)
	{
		return true;
	}
	if (m_Pos.y + (m_Speed * g_ETime) > m_stage.bottom)
	{
		return true;
	}
	return false;
}

FRECT ItemManager::GetRect()
{
	return m_Item;
}

void ItemManager::SettingItem(Vecter Pos, ItemType Type)
{
	m_Pos = Pos;
	m_Type = Type;
	m_Item = RectMakeCenter(m_Pos.x, m_Pos.y, 20, 20);
}

void ItemManager::SetStage(FRECT stage)
{
	m_stage = stage;
}

bool ItemManager::PlayerItemEat(FRECT rc)
{
	if (IntersectRect(m_Item, rc))
	{
		return true;
	}
	return false;
}

ItemType ItemManager::GetType()
{
	return m_Type;
}
