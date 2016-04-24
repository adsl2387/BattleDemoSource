// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/MovementComponent.h"
#include "LinearMovement.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEDEMO_API ULinearMovement : public UMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Logic", meta = (DisplayName = "Speed"))
	float	Speed;
	

	UPROPERTY(EditAnywhere, Category = "Logic", meta = (DisplayName = "Direction"))
	FRotator	Direction;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);
};
