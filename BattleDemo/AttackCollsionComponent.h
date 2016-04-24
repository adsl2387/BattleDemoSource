// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "AttackCollsionComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEDEMO_API UAttackCollsionComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnAttackHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void OnRegister() override;

	virtual void OnUnregister() override;

	UPROPERTY(EditAnywhere, Category = "Logic", meta = (DisplayName = "HitEffect"))
	UParticleSystem* PSTemplate;
};
