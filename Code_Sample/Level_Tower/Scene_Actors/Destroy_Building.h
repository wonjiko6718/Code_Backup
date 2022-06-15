// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Destroy_Building.generated.h"

UCLASS()
class CODE_SAMPLE_API ADestroy_Building : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroy_Building();

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
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Destroy_Building_Mesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* Destroy_Building_Detect;
	UPROPERTY(EditAnywhere)
		UNiagaraComponent* Destroy_Building_Particle_NG_Comp;
	UPROPERTY(VisibleAnywhere)
		int Destroy_Building_HitStack;
	UPROPERTY(VisibleAnywhere)
		bool Destroy_Building_CanKill;
	UPROPERTY(EditAnywhere)
		FString Destroy_Building_String;


};
