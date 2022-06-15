// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Random_Spawner.generated.h"

UCLASS()
class CODE_SAMPLE_API ARandom_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandom_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* Other) override;
	virtual void NotifyActorEndOverlap(AActor* Other) override;

	void Random_Spawn_Method();

	FTimerHandle Random_Spawner_TimerHandle;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Random_Spawner_Detect_Box;
	UPROPERTY(EditAnywhere)
		UBoxComponent* Random_Spanwer_Spawn_Box;
	UPROPERTY(EditAnywhere)
		UStaticMesh* Random_Spawned_Actor_Mesh;
	UPROPERTY(EditAnywhere)
		FVector Random_Spawned_Actor_Scale;
	UPROPERTY(EditAnywhere)
		FString Random_Dead_Cause_String;
	UPROPERTY(EditAnywhere)
		FVector Random_Spawned_Actor_Particle_Scale;
	UPROPERTY(EditAnywhere)
		UParticleSystem* Random_Spawned_Actor_Particle;
	UPROPERTY(EditAnywhere)
		float Random_Spawn_Delay;
	UPROPERTY(VisibleAnywhere)
		bool Can_Random_Spawn;
	UPROPERTY(EditAnywhere)
		int Random_Spawn_Count_MAX;
	UPROPERTY(VisibleAnywhere)
		int Random_Spawn_Count_NOW;

};
