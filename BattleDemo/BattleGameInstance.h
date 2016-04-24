// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "BattleGameInstance.generated.h"

namespace BattleGameState
{
	extern const FName None;
	extern const FName WelcomScreen;
	extern const FName MainMenu;
	extern const FName Playing;
}

/**
 * 
 */
UCLASS(config=Game)
class BATTLEDEMO_API UBattleGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()
public:
	virtual void Init() override;
	
	virtual void StartGameInstance() override;

	virtual void Shutdown() override;

	void GoToState(FName NewState);

	bool Tick(float DeltaSeconds);

	void OnPreLoadMap();

	void OnPostLoadMap();

	void HandleSafeFrameChanged();

	FName GetInitialState();

	void GoToInitialState();

	void CheckStateChange();

	void EndCurrentState(FName NewState);

	void BeginNewState(FName NewState, FName OldState);

	void OnPostDemoPlay();

	bool StartGame(ULocalPlayer* LocalPlayer, const FString& GameType, const FString& InTravelURL);
protected:
	FName	CurrentState;
	FName	PendingState;

	FTickerDelegate TickDelegate;

	FDelegateHandle	TickDelegateHandle;

	FString TravelURL;

	void BeginMainMenuState();

	void EndMainMenuState();

	void BeginPlayingState();

	void EndPlayingState();

	void BeginWelcomeState();

	void EndWelcomeState();

	void ShowLoadingScreen();
};
