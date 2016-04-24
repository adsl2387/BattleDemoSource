// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDemo.h"
#include "AttackCollsionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BattleHitInterface.h"



void UAttackCollsionComponent::OnAttackHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//UKismetSystemLibrary::PrintString(this, TEXT("Hit"));
	if (OtherActor == GetOwner()->GetOwner())
	{
		return;
	}
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UBattleHitInterface::StaticClass()))
	{
		//UKismetSystemLibrary::PrintString(this, TEXT("Hit1"));
		//UKismetSystemLibrary::Callfu
		IBattleHitInterface::Execute_TakeWeaponFire(OtherActor, 11);

		if (PSTemplate)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PSTemplate, GetComponentTransform());
		}

		GetOwner()->Destroy();
	}


}

void UAttackCollsionComponent::OnRegister()
{
	Super::OnRegister();
	//UKismetSystemLibrary::PrintString(this, TEXT("OnRegister"));
	this->OnComponentBeginOverlap.AddDynamic(this, &UAttackCollsionComponent::OnAttackHit);
}

void UAttackCollsionComponent::OnUnregister()
{
	Super::OnUnregister();
	this->OnComponentBeginOverlap.RemoveDynamic(this, &UAttackCollsionComponent::OnAttackHit);
}
