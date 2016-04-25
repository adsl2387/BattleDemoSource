// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDemo.h"
#include "BatleGameViewportClient.h"
#include "GenericApplication.h"
#include "GenericApplicationMessageHandler.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

void SBattleLoadingScreen2::Construct(const FArguments& InArgs)
{
	static const FName LoadingScreenName(TEXT("/Game/UI/Menu/LoadingScreen.LoadingScreen"));

	//since we are not using game styles here, just load one image
	LoadingScreenBrush = MakeShareable(new FBattleLoadingScreenBrush(LoadingScreenName, FVector2D(1920, 1080)));

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.Image(LoadingScreenBrush.Get())
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SSafeZone)
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(10.0f)
			.IsTitleSafe(true)
			[
				SNew(SThrobber)
				.Visibility(this, &SBattleLoadingScreen2::GetLoadIndicatorVisibility)
			]
		]
	];
}

UBatleGameViewportClient::UBatleGameViewportClient(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UBatleGameViewportClient::AddViewportWidgetContent(TSharedRef<class SWidget> ViewportContent, const int32 ZOrder /* = 0 */)
{
	UE_LOG(LogPlayerManagement, Log, TEXT("UBattleGameViewportClient::AddViewportWidgetContent: %p"), &ViewportContent.Get());

	if (LoadingScreenWidget.IsValid() && ViewportContent != LoadingScreenWidget)
	{
		HiddenViewportContentStack.AddUnique(ViewportContent);
		return;
	}

	if (ViewportContentStack.Contains(ViewportContent))
	{
		return;
	}

	ViewportContentStack.AddUnique(ViewportContent);

	Super::AddViewportWidgetContent(ViewportContent, 0);
}

void UBatleGameViewportClient::RemoveViewportWidgetContent(TSharedRef<class SWidget> ViewportContent)
{
	UE_LOG(LogPlayerManagement, Log, TEXT("UBattleGameViewportClient::RemoveViewportWidgetContent: %p"), &ViewportContent.Get());

	ViewportContentStack.Remove(ViewportContent);

	HiddenViewportContentStack.Remove(ViewportContent);

	Super::RemoveViewportWidgetContent(ViewportContent);
}

void UBatleGameViewportClient::Tick(float DeltaTime)
{

}

void UBatleGameViewportClient::ShowLoadingScreen()
{
	if (LoadingScreenWidget.IsValid())
	{
		return;
	}

	HideExistingWidgets();

	LoadingScreenWidget = SNew(SBattleLoadingScreen2);

	AddViewportWidgetContent(LoadingScreenWidget.ToSharedRef());
}

void UBatleGameViewportClient::HideLoadingScreen()
{
	if (!LoadingScreenWidget.IsValid())
	{
		return;
	}
	RemoveViewportWidgetContent(LoadingScreenWidget.ToSharedRef());

	LoadingScreenWidget = NULL;

	ShowExistingWidgets();
}

void UBatleGameViewportClient::HideExistingWidgets()
{
	check(HiddenViewportContentStack.Num() == 0);
	TArray<TSharedRef<class SWidget>> CopyOfViewportfContentStack = ViewportContentStack;

	for (int32 i = ViewportContentStack.Num() - 1; i >= 0; --i)
	{
		RemoveViewportWidgetContent(ViewportContentStack[i]);
	}

	HiddenViewportContentStack = CopyOfViewportfContentStack;


}

void UBatleGameViewportClient::ShowExistingWidgets()
{
	check(ViewportContentStack.Num() == 0);

	for (int32 i = 0; i < HiddenViewportContentStack.Num(); ++i)
	{
		AddViewportWidgetContent(HiddenViewportContentStack[i]);
	}

	check(ViewportContentStack.Num() == HiddenViewportContentStack.Num());

	HiddenViewportContentStack.Empty();
}
