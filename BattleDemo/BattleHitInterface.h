#pragma once
#include "Interface.h"
#include "BattleHitInterface.generated.h"

UINTERFACE(BlueprintType)
class BATTLEDEMO_API UBattleHitInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class BATTLEDEMO_API IBattleHitInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Hit", meta = (CallInEditor = "true"))
	bool TakeWeaponFire(int32 HitId);
};
