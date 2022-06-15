// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Scene_Actor_Base.h"
#include "Spawned_Trigger_Actor.generated.h"

UCLASS()
class CODE_SAMPLE_API ASpawned_Trigger_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawned_Trigger_Actor();

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

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Spawned_Trigger_Actor_Mesh;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Spawned_Trigger_Particle;
	UPROPERTY(EditAnywhere)
		FString Obstacle_String;

};
