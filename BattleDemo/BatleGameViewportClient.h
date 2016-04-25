// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "BatleGameViewportClient.generated.h"


struct FBattleLoadingScreenBrush :public FSlateDynamicImageBrush, public FGCObject
{
	FBattleLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		:FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		ResourceObject = LoadObject<UObject>(NULL, *InTextureName.ToString());
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (ResourceObject)
		{
			Collector.AddReferencedObject(ResourceObject);
		}
	}
};

class SBattleLoadingScreen2 : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBattleLoadingScreen2) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	EVisibility GetLoadIndicatorVisibility() const
	{
		return EVisibility::Visible;
	}

	/** loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

/**
 * 
 */
UCLASS()
class BATTLEDEMO_API UBatleGameViewportClient : public UGameViewportClient
{
	GENERATED_UCLASS_BODY()
public:
	virtual void AddViewportWidgetContent(TSharedRef<class SWidget> ViewportContent, const int32 ZOrder  = 0 ) override;

	virtual void RemoveViewportWidgetContent(TSharedRef<class SWidget> ViewportContent) override;

	virtual void Tick(float DeltaTime) override;

	void ShowLoadingScreen();

	void HideLoadingScreen();

protected:

	void HideExistingWidgets();

	void ShowExistingWidgets();
	
	TArray<TSharedRef<class SWidget>>			ViewportContentStack;
	TArray<TSharedRef<class SWidget>>			HiddenViewportContentStack;

	TSharedPtr<class SWidget>					OldFocusWidget;

	TSharedPtr<SBattleLoadingScreen2>			LoadingScreenWidget;
	
};
