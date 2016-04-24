// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDemo.h"
#include "AttackComponent.h"


// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	LifeTime = 10.f;
	CurrentTime = 0.f;
	CurrentParticleSystem = NULL;
	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
	CurrentTime += DeltaTime;
	if (CurrentTime > LifeTime)
	{
		GetOwner()->Destroy();
	}
}

void UAttackComponent::OnRegister()
{
	Super::OnRegister();

	if (CurrentParticleSystem)
	{
		CurrentParticleSystem->DestroyComponent();
	}

	CurrentParticleSystem = UGameplayStatics::SpawnEmitterAttached(PSTemplate, this);
}

