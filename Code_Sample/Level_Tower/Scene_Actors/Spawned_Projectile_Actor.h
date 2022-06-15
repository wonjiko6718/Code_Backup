// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Spawned_Projectile_Actor.generated.h"

UCLASS()
class CODE_SAMPLE_API ASpawned_Projectile_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawned_Projectile_Actor();

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

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Spawned_Projectile_Mesh;
	UPROPERTY(VisibleAnywhere)
		UMaterial* Spawned_Projectile_Material;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Spawned_Projectile_Particle;
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* Spawned_Projectile_Movement;
	UPROPERTY(VisibleAnywhere)
		FString Spawned_Projectile_String;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Spawned_Projectile_Hit_Particle;
};
