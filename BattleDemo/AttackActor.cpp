// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDemo.h"
#include "AttackActor.h"
#include "AttackComponent.h"
#include "LinearMovement.h"
#include "AttackCollsionComponent.h"
#include "BattleHitInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AAttackActor::AAttackActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackCompenet"));
	RootComponent = AttackComponent;

	LinearMovement = CreateDefaultSubobject<ULinearMovement>(TEXT("LinearMovement"));

	LinearMovement->SetUpdatedComponent(AttackComponent);

	CollisionComponent = CreateDefaultSubobject<UAttackCollsionComponent>(TEXT("CollisionComponent"));

	CollisionComponent->AttachTo(AttackComponent);

	
}

// Called when the game starts or when spawned
void AAttackActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAttackActor::OnAttackHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UKismetSystemLibrary::PrintString(this);
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UBattleHitInterface::StaticClass()))
	{
		//UKismetSystemLibrary::Callfu
		IBattleHitInterface* IActor = Cast<IBattleHitInterface>(OtherActor);
		IActor->TakeWeaponFire(11);
	}
	
}

