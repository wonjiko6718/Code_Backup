// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Scene_Actor_Base.h"
#include "Turret.generated.h"

UCLASS()
class CODE_SAMPLE_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* Other) override;
	virtual void NotifyActorEndOverlap(AActor* Other) override;


	bool Turret_Activated;
	AActor* Follow_Player;
	FTimerHandle Turret_TimerHandle;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Turret_Mesh;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* Turret_Detect_Sphere;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Turret_Activated_Particle;
	UFUNCTION()
		void Turret_Shoot();

};
