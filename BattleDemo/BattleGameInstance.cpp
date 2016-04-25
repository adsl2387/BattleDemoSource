// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDemo.h"
#include "BattleGameInstance.h"
#include "BattleLoadingScreen.h"
#include "BatleGameViewportClient.h"
#include "DataRow.h"


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

	static ConstructorHelpers::FObjectFinder<UDataTable> LevelTableData(TEXT("DataTable'/Game/GameData/Level.Level'"));
	if (NULL != LevelTableData.Object)
	{
		LevelDataTable = LevelTableData.Object;
	}
	FLevelRow* InitLevelInfo = LevelDataTable->FindRow<FLevelRow>(FName(TEXT("StartMap")), FString(TEXT("")));

	CurrentURL = FString::Printf(TEXT("%s?game=%s"), *InitLevelInfo->CurrentMapName, *InitLevelInfo->GameModeShortName);
	//NextURL = InitLevelInfo->NextMapName;
	NextMap = InitLevelInfo->NextMapName;
	GameModeShortName = InitLevelInfo->GameModeShortName;
}

void UBattleGameInstance::StartGameInstance()
{
	//Super::StartGameInstance();
	GoToInitialState();
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
	UBatleGameViewportClient* BattleViewport = Cast<UBatleGameViewportClient>(GetGameViewportClient());
	if (BattleViewport)
	{
		BattleViewport->HideLoadingScreen();
	}
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

bool UBattleGameInstance::StartGame(const FString& InTravelURL)
{
	ShowLoadingScreen();
	GoToState(BattleGameState::Playing);
	TravelURL = InTravelURL;
	GetWorld()->ServerTravel(TravelURL);
	return true;
}

bool UBattleGameInstance::LoadFromEndMap(const FString& MapName)
{
	bool bSuccess = true;
	UWorld* const World = GetWorld();

	if (World)
	{
		FString CurrentMapName = *World->PersistentLevel->GetOutermost()->GetName();
		if (CurrentMapName == MapName)
		{
			return bSuccess;
		}
	}

	FString Error;
	EBrowseReturnVal::Type BrowseRet = EBrowseReturnVal::Failure;
	FURL URL(*FString::Printf(TEXT("%s"), *MapName));

	if (URL.Valid && !HasAnyFlags(RF_ClassDefaultObject))
	{
		BrowseRet = GetEngine()->Browse(*WorldContext, URL, Error);

		if (BrowseRet != EBrowseReturnVal::Success)
		{
			UE_LOG(LogLoad, Fatal, TEXT("%s"), *FString::Printf(TEXT("Failed to enter &s: %s. Please check the log for errors"), *MapName, *Error));
			bSuccess = false;
		}
	}
	return bSuccess;
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
	//StartGame(getlocalpl)
	//FURL URL(*FString::Printf(TEXT("%s"), *cur));
	StartGame(CurrentURL);
}

void UBattleGameInstance::EndWelcomeState()
{

}

void UBattleGameInstance::ShowLoadingScreen()
{
	IBattleLoadingScreenModule* const LoadingScreenModule = FModuleManager::LoadModulePtr<IBattleLoadingScreenModule>("BattleLoadingScreenModule");

	if (LoadingScreenModule != nullptr)
	{
		LoadingScreenModule->StartInGameLoadingScreen();
	}

	UBatleGameViewportClient* BattleViewport = Cast<UBatleGameViewportClient>(GetGameViewportClient());

	if (BattleViewport != NULL)
	{
		BattleViewport->ShowLoadingScreen();
	}
}
