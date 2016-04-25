#include "BattleLoadingScreen.h"
#include "GenericApplication.h"
#include "GenericApplicationMessageHandler.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"

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

class SBattleLoadingScreen :public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBattleLoadingScreen){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		static const FName LoadingScreenName(TEXT("/Game/UI/Menu/LoadingScreen.LoadingScreen"));

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
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SSafeZone)
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(10.f)
				.IsTitleSafe(true)
				[
					SNew(SThrobber)
					.Visibility(this, &SBattleLoadingScreen::GetLoadIndicatorVisibility)
				]
			]
		];
	}
private:

	EVisibility GetLoadIndicatorVisibility() const
	{
		return EVisibility::Visible;
	}

	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FBattleLoadingScreenModule :public IBattleLoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		LoadObject<UObject>(NULL, TEXT("/Game/UI/Menu/LoadingScreen.LoadingScreen"));

		if (IsMoviePlayerEnabled())
		{
			FLoadingScreenAttributes LoadingScreen;
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
			LoadingScreen.MoviePaths.Add(TEXT("LoadingScreen"));
			GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		}
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen() override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.WidgetLoadingScreen = SNew(SBattleLoadingScreen);
		

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
};

IMPLEMENT_GAME_MODULE(FBattleLoadingScreenModule, BattleLoadingScreen)