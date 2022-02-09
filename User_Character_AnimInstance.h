// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "User_Character_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CODE_SAMPLE_API UUser_Character_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UUser_Character_AnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAirDashMontage();
	void StopAirDashMontage();
	void PlayWallRun_R_Montage();
	void PlayWallRun_L_Montage();
	void StopWallRun_Montage();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		bool InAirDash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AirDash_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		UAnimMontage* WallRun_Montage;
};
