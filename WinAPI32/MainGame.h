#pragma once
#include "MainScreen.h"
#include "GameNode.h"
class MainGame : public GameNode
{
private:
	MainScreen temp;
public:
	MainGame();
	~MainGame() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

