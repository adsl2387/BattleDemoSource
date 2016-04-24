#pragma once
#include "ModuleInterface.h"

class IBattleLoadingScreenModule : public IModuleInterface
{
public:
	virtual void StartInGameLoadingScreen() = 0;
};