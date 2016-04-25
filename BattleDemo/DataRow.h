#pragma once
#include "DataRow.generated.h"

USTRUCT(Blueprintable)
struct FLevelRow:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelTableData)
	FString NextMapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelTableData)
	FString CurrentMapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelTableData)
	FString GameModeShortName;
};