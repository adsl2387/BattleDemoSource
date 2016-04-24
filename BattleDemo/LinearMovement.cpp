// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDemo.h"
#include "LinearMovement.h"

void ULinearMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	FQuat quat = UpdatedComponent->GetComponentQuat() * Direction.Quaternion();

	FVector delta = DeltaTime * FVector(Speed, 0, 0);

	FVector outdelta = quat * delta  ;

	MoveUpdatedComponent(outdelta, UpdatedComponent->GetComponentQuat(), true);

	UpdateComponentVelocity();
}
