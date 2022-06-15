// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable_Actors.h"

// Sets default values
ABreakable_Actors::ABreakable_Actors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//StaticMesh'/Game/Cave/Meshes/SM_BridgePart01.SM_BridgePart01'
	Break_Actor_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BREAK_MESH"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Break_Actor_Mesh_OF(TEXT("/Game/Cave/Meshes/SM_BridgePart01.SM_BridgePart01"));
	if (Break_Actor_Mesh_OF.Succeeded())
	{
		Break_Actor_Mesh->SetStaticMesh(Break_Actor_Mesh_OF.Object);
	}

}

// Called when the game starts or when spawned
void ABreakable_Actors::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakable_Actors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABreakable_Actors::NotifyHit
(
	class UPrimitiveComponent* MyComp,
	AActor* Other,
	class UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	if (Other->ActorHasTag(TEXT("Destroy")))
	{
		UE_LOG(LogTemp, Error, TEXT("Tag Hit"));
		Break_Actor_Mesh->SetSimulatePhysics(true);
	}
}
