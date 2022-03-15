// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "User_Character.generated.h"

UCLASS()
class CODE_SAMPLE_API AUser_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUser_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called PostInitailize Components Method for Montage or Setting AnimInstance
	virtual void PostInitializeComponents() override;
	// Called to bind functionality to input
	// add Override Methods
	
	//Add Notify Method
	virtual void NotifyActorBeginOverlap(AActor* Other) override;
	virtual void NotifyActorEndOverlap(AActor* Other) override;
	virtual void NotifyHit
	(
		class UPrimitiveComponent* MyComp,
		AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;
public:
	//Components
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* User_Detect_Capsule;
	UPROPERTY()
		class UUser_Character_AnimInstance* User_Character_AnimInstance;
	//Properties
	UPROPERTY(VisibleAnywhere)
		float PlayerSpeed;
	UPROPERTY(VisibleAnywhere)
		bool WallTouch;
	UPROPERTY(VisibleAnywhere)
		int WallDir;
	UPROPERTY(VisibleAnywhere)
		bool Air_Dash_Now;
	UPROPERTY(VisibleAnywhere)
		bool WallRun_Now;
	UPROPERTY(VisibleAnywhere)
		bool Can_Rope_Action;

	//Add Another Function
	void Shoot_Rope();
	void Rope_Launch(FVector TargetLocation);
private:
	float Cal_Forward_Target_Degree(FVector TargetLocation);

	UFUNCTION()
		void End_Montage_Trail(UAnimMontage* Montage, bool bInterrupted);
};
