// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AttackActor.generated.h"

class UAttackComponent;
class ULinearMovement;
class UAttackCollsionComponent;

UCLASS(hidecategories = Object)
class BATTLEDEMO_API AAttackActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (DisplayName = "AttackCompenent"))
	UAttackComponent*	AttackComponent;

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (DisplayName = "Movement"))
	ULinearMovement*	LinearMovement;

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (Displayname = "Collision"))
	UAttackCollsionComponent*	CollisionComponent;

	UFUNCTION()
	void OnAttackHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
