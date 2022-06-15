// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Scene_Actor_Base.h"
#include "Dead_Area.generated.h"

UCLASS()
class CODE_SAMPLE_API ADead_Area : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADead_Area();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* Other) override;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* Dead_Zone;
	UPROPERTY(EditAnywhere)
		FString Dead_Cause;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Dead_Particle;

};
