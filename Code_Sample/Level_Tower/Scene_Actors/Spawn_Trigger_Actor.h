// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Scene_Actor_Base.h"
#include "Spawn_Trigger_Actor.generated.h"

UCLASS()
class CODE_SAMPLE_API ASpawn_Trigger_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawn_Trigger_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* Other) override;

	void Spawn_Method();

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* Spawn_Trigger_Box;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* Spawn_Target_Sphere;
	UPROPERTY(EditAnywhere)
		AActor* Spawn_Trigger_Actor;
	UPROPERTY(EditAnywhere)
		UStaticMesh* Spawned_Actor_Mesh;
	UPROPERTY(EditAnywhere)
		FVector Spawned_Actor_Scale;
	UPROPERTY(EditAnywhere)
		FName SpawnTag;
	UPROPERTY(EditAnywhere)
		FName DetectTag;
	UPROPERTY(EditAnywhere)
		FString Spawned_Obstacle_String;
	UPROPERTY(EditAnywhere)
		bool Spawn_Actor_Bool;
	UPROPERTY(EditAnywhere)
		bool Spawn_Particle_Bool;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Spawned_Particle_System;
	UPROPERTY(EditAnywhere)
		int SpawnCount;
};
