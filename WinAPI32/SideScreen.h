#pragma once
#include "GameNode.h"
class SideScreen :public GameNode
{
	FRECT m_rc;
	UINT * m_Score;
public:
	SideScreen(UINT * m_Score);
	SideScreen();
	~SideScreen();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

