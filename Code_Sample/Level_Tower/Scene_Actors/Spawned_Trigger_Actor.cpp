// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawned_Trigger_Actor.h"

// Sets default values
ASpawned_Trigger_Actor::ASpawned_Trigger_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'
	Spawned_Trigger_Actor_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Spawned_Trigger_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPAWNED_TRIGGER_PARTICLE"));

	RootComponent = Spawned_Trigger_Actor_Mesh;
	Spawned_Trigger_Particle->SetupAttachment(RootComponent);
	Spawned_Trigger_Particle->SetAutoActivate(false);

	Spawned_Trigger_Actor_Mesh->SetCollisionProfileName(TEXT("BlockAll"));
	Spawned_Trigger_Actor_Mesh->SetSimulatePhysics(true);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Spawned_Trigger_Actor_Mesh_OF(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (Spawned_Trigger_Actor_Mesh_OF.Succeeded())
	{
		Spawned_Trigger_Actor_Mesh->SetStaticMesh(Spawned_Trigger_Actor_Mesh_OF.Object);
	}

}

// Called when the game starts or when spawned
void ASpawned_Trigger_Actor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawned_Trigger_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASpawned_Trigger_Actor::NotifyHit
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
	if (Other->ActorHasTag("User_Character"))
	{
		UE_LOG(LogTemp, Error, TEXT("Spawned Hit"));
		Spawned_Trigger_Particle->SetWorldLocation(HitLocation);
		Spawned_Trigger_Particle->SetActive(true);
	}
}

