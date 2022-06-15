// Fill out your copyright notice in the Description page of Project Settings.


#include "User_Character_AnimInstance.h"
#include "User_Character.h"

UUser_Character_AnimInstance::UUser_Character_AnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;

	//AnimMontage'/Game/Self_Anim_BP/AirDash_Montage.AirDash_Montage'
	//AnimMontage'/Game/Retarget_Anim/Main_Char_Retarget/AirDash_Montage.AirDash_Montage'
	//AnimMontage'/Game/Import_SH/Character/0328/Anim_Retarget/AirDash_Montage.AirDash_Montage'
	//AnimMontage'/Game/Retarget_Anim/Main_Char_Retarget_Fixed/AirDash_Montage.AirDash_Montage'
	//AnimMontage'/Game/Retarget_Anim/Main_Char_Retarget_0603/AirDash_Montage.AirDash_Montage'
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AirDashMontage_OF(TEXT("/Game/Retarget_Anim/Main_Char_Retarget_0603/AirDash_Montage.AirDash_Montage"));
	if (AirDashMontage_OF.Succeeded())
	{
		AirDash_Montage = AirDashMontage_OF.Object;
	}
	//AnimMontage'/Game/Self_Anim_BP/WallRun_Anim_Montage.WallRun_Anim_Montage'
	//AnimMontage'/Game/Retarget_Anim/Main_Char_Retarget/WallRun_Anim_Montage.WallRun_Anim_Montage'
	//AnimMontage'/Game/Import_SH/Character/0328/Anim_Retarget/WallRun_Anim_Montage.WallRun_Anim_Montage'
	//AnimMontage'/Game/Retarget_Anim/Main_Char_Retarget_Fixed/WallRun_Anim_Montage.WallRun_Anim_Montage'
	//AnimMontage'/Game/Retarget_Anim/Main_Char_Retarget_0603/WallRun_Anim_Montage.WallRun_Anim_Montage'
	static ConstructorHelpers::FObjectFinder<UAnimMontage> WallRun_Montage_OF(TEXT("/Game/Retarget_Anim/Main_Char_Retarget_0603/WallRun_Anim_Montage.WallRun_Anim_Montage"));
	if(WallRun_Montage_OF.Succeeded())
	{
		WallRun_Montage = WallRun_Montage_OF.Object;
	}
	//
	//AnimMontage'/Game/Import_SH/Character/0328/Anim_Retarget/Hand_Swing_Montage.Hand_Swing_Montage'
	//AnimMontage'/Game/Retarget_Anim/Main_Char_Retarget_Fixed/Hand_Swing_Montage.Hand_Swing_Montage'
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RopeAction_Montage_OF(TEXT("AnimMontage'/Game/Retarget_Anim/Main_Char_Retarget_0603/Hand_Swing_Montage.Hand_Swing_Montage'"));
	if (RopeAction_Montage_OF.Succeeded())
	{
		RopeAction_Montage = RopeAction_Montage_OF.Object;
	}
}
void UUser_Character_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
			if (Character->GetVelocity().Z < 0)
			{
				StopAirDashMontage();
			}
		}
	}
}
void UUser_Character_AnimInstance::PlayAirDashMontage()
{
	Montage_Play(AirDash_Montage, 1.0f);
}
void UUser_Character_AnimInstance::StopAirDashMontage()
{
	Montage_Stop(0.35f, AirDash_Montage);
}
void UUser_Character_AnimInstance::PlayWallRun_L_Montage()
{
	Montage_Play(WallRun_Montage, 1.0f);
}
void UUser_Character_AnimInstance::PlayWallRun_R_Montage()
{
	Montage_Play(WallRun_Montage, 1.0f);
	Montage_JumpToSection(TEXT("WallRun_R"), WallRun_Montage);
}
void UUser_Character_AnimInstance::StopWallRun_Montage()
{
	Montage_Stop(0.35f, WallRun_Montage);
}
void UUser_Character_AnimInstance::PlayRopeAction_Montage()
{
	Montage_Play(RopeAction_Montage, 1.0f);
}
void UUser_Character_AnimInstance::AnimNotify_Spawn_Projectile()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn_Projectile_On"));
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		auto Character = Cast<AUser_Character>(Pawn);
		if(::IsValid(Character))
		{
			Character->Shoot_Rope();
		}
	}
}