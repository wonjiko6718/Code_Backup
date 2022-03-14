// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "User_Rope_Hook.generated.h"

UCLASS()
class CODE_SAMPLE_API AUser_Rope_Hook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUser_Rope_Hook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
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
	void FireInDirection(const FVector& ShootDirection);

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* User_Rope_Hook_StaticMeshComp;
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* ProjectileCollision;
	UPROPERTY(VisibleAnywhere)
		AActor* Rope_Hook_Owner;
	UPROPERTY(VisibleAnywhere)
		bool Rope_Hook_Return;
};
