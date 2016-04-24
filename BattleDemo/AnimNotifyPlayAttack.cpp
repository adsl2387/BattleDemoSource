// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDemo.h"
#include "AnimNotifyPlayAttack.h"
#include "attackactor.h"


UAnimNotifyPlayAttack::UAnimNotifyPlayAttack()
{
	//Attached = true;

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(192, 255, 99, 255);
#endif // WITH_EDITORONLY_DATA

	RotationOffsetQuat = FQuat(RotationOffset);
}

void UAnimNotifyPlayAttack::PostLoad()
{
	Super::PostLoad();

	RotationOffsetQuat = FQuat(RotationOffset);
}

#if WITH_EDITOR
void UAnimNotifyPlayAttack::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.MemberProperty && PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UAnimNotifyPlayAttack, RotationOffset))
	{
		RotationOffsetQuat = FQuat(RotationOffset);
	}
}
#endif

void UAnimNotifyPlayAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AttackClass)
	{
		const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(MeshTransform.TransformPosition(LocationOffset));
		SpawnTransform.SetRotation(MeshTransform.GetRotation() * RotationOffsetQuat);
		//UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), PSTemplate, SpawnTransform);
		FActorSpawnParameters param;
		param.Owner = MeshComp->GetOwner();
		AAttackActor* attack = Cast<AAttackActor>(MeshComp->GetWorld()->SpawnActor(AttackClass, &SpawnTransform, param));
		if (attack)
		{
			if (MeshComp->GetOwner())
			{
				attack->SetActorRotation(MeshComp->GetOwner()->GetActorQuat() * RotationOffsetQuat);
			}
			else
				attack->SetActorRotation(FVector(0, 1, 0).ToOrientationQuat()* RotationOffsetQuat);
		}
	}
	
}