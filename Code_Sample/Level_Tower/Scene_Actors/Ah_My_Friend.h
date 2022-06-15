// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ah_My_Friend.generated.h"

UCLASS()
class CODE_SAMPLE_API AAh_My_Friend : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAh_My_Friend();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
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
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UBoxComponent* Friend_Detect_Box;
	UPROPERTY(VisibleAnywhere)
		bool Friend_Activate;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Friend_Mesh;
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* Friend_Movement;
	UPROPERTY(EditAnywhere)
		FString Friend_String;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Friend_Hit_Particle;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Friend_Spawn_Particle;
	UPROPERTY(EditAnywhere)
		bool Friend_GetBack;
	UPROPERTY(EditAnywhere)
		float Friend_LifeTime;

	void Friend_Shoot();
};
