// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Spring_Board.generated.h"

UCLASS()
class CODE_SAMPLE_API ASpring_Board : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpring_Board();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* Other) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Spring_Board_Mesh;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* Spring_Board_Box;
	UPROPERTY(VisibleAnywhere)
		bool Spring_Activate;
	UPROPERTY(VisibleAnywhere)
		FRotator Board_Rotation;
	UPROPERTY(EditAnywhere)
		float Board_Up_Speed;
	UPROPERTY(EditAnywhere)
		float Board_Up_Angle;
};
