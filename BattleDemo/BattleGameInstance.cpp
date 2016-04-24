// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDemo.h"
#include "BattleGameInstance.h"


namespace BattleGameState
{
	const FName None			= FName(TEXT("None"));
	const FName WelcomScreen	= FName(TEXT("WelcomScreen"));
	const FName MainMenu		= FName(TEXT("MainMenu"));
	const FName Playing			= FName(TEXT("Playing"));
}

UBattleGameInstance::UBattleGameInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CurrentState = BattleGameState::None;
}

void UBattleGameInstance::Init()
{
	Super::Init();

	FCoreDelegates::OnSafeFrameChangedEvent.AddUObject(this, &UBattleGameInstance::HandleSafeFrameChanged);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UBattleGameInstance::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &UBattleGameInstance::OnPostLoadMap);

	TickDelegate = FTickerDelegate::CreateUObject(this, &UBattleGameInstance::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
}

void UBattleGameInstance::StartGameInstance()
{
	//Super::StartGameInstance();

}

void UBattleGameInstance::Shutdown()
{
	Super::Shutdown();
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

void UBattleGameInstance::GoToState(FName NewState)
{
	PendingState = NewState;
}

bool UBattleGameInstance::Tick(float DeltaSeconds)
{
	CheckStateChange();
	return true;
}

void UBattleGameInstance::OnPreLoadMap()
{

}

void UBattleGameInstance::OnPostLoadMap()
{

}

void UBattleGameInstance::HandleSafeFrameChanged()
{
	UCanvas::UpdateAllCanvasSafeZoneData();
}

FName UBattleGameInstance::GetInitialState()
{
	return BattleGameState::WelcomScreen;
}

void UBattleGameInstance::GoToInitialState()
{
	GoToState(GetInitialState());
}

void UBattleGameInstance::CheckStateChange()
{
	if (PendingState != CurrentState && PendingState != BattleGameState::None)
	{
		FName OldState = CurrentState;

		EndCurrentState(PendingState);

		BeginNewState(PendingState, OldState);

	}
}

void UBattleGameInstance::EndCurrentState(FName NewState)
{
	if (CurrentState == BattleGameState::MainMenu)
	{
		EndMainMenuState();
	}
	else if (CurrentState == BattleGameState::Playing)
	{
		EndPlayingState();
	}
	else if (CurrentState == BattleGameState::WelcomScreen)
	{
		EndWelcomeState();
	}
	CurrentState = BattleGameState::None;
}

void UBattleGameInstance::BeginNewState(FName NewState, FName OldState)
{
	if (NewState == BattleGameState::MainMenu)
	{
		BeginMainMenuState();
	}
	else if (NewState == BattleGameState::Playing)
	{
		BeginPlayingState();
	}
	else if (NewState == BattleGameState::WelcomScreen)
	{
		BeginWelcomeState();
	}

	CurrentState = NewState;
}

void UBattleGameInstance::OnPostDemoPlay()
{
	GoToState(BattleGameState::Playing);
}

bool UBattleGameInstance::StartGame(ULocalPlayer* LocalPlayer, const FString& GameType, const FString& InTravelURL)
{
	ShowLoadingScreen();
	GoToState(BattleGameState::Playing);
	TravelURL = InTravelURL;
	GetWorld()->ServerTravel(TravelURL);
	return true;
}

void UBattleGameInstance::BeginMainMenuState()
{

}

void UBattleGameInstance::EndMainMenuState()
{

}

void UBattleGameInstance::BeginPlayingState()
{

}

void UBattleGameInstance::EndPlayingState()
{

}

void UBattleGameInstance::BeginWelcomeState()
{

}

void UBattleGameInstance::EndWelcomeState()
{

}

void UBattleGameInstance::ShowLoadingScreen()
{

}
