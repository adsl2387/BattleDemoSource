// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEDEMO_API UAttackComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, Category = "Logic", meta = (DisplayName = "FlyEffect"))
	UParticleSystem* PSTemplate;

	UPROPERTY(EditAnywhere, Category = "Logic", meta = (DisplayName = "LifeTime"))
	float			LifeTime;
		
	virtual void OnRegister() override;


private:

	float			CurrentTime;
	UParticleSystemComponent*	CurrentParticleSystem;
};
