// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyPlayAttack.generated.h"

class AAttackActor;

/**
 * 
 */
UCLASS(const, hidecategories = Object, collapsecategories, meta = (DisplayName = "Play Attack"))
class BATTLEDEMO_API UAnimNotifyPlayAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	UAnimNotifyPlayAttack();

	// Begin UObject interface
	virtual void PostLoad() override;

	// Location offset from the socket
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
		FVector LocationOffset;

	// Rotation offset from socket
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
		FRotator RotationOffset;

	// SocketName to attach to
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
		FName SocketName;

	UPROPERTY(EditAnywhere, Category = "AnimNotify")
		TSubclassOf<AAttackActor> AttackClass;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:
	// Cached version of the Rotation Offset already in Quat form
	FQuat RotationOffsetQuat;
	
};
