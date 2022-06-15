// Fill out your copyright notice in the Description page of Project Settings.


#include "Random_Spawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Spawned_Trigger_Actor.h"

// Sets default values
ARandom_Spawner::ARandom_Spawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Random_Spanwer_Spawn_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("RANDOM_SPAWN_BOX"));
	Random_Spawner_Detect_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("RANDOM_SPAWN_DETECT_BOX"));
	Random_Spawned_Actor_Mesh = CreateDefaultSubobject<UStaticMesh>(TEXT("RANDOM_SPAWNED_MESH"));
	Random_Spawned_Actor_Particle = CreateDefaultSubobject<UParticleSystem>(TEXT("RANDOM_SPAWNED_PARTICLE"));

	RootComponent = Random_Spawner_Detect_Box;
	Random_Spanwer_Spawn_Box->SetupAttachment(RootComponent);
	Random_Spawned_Actor_Scale = FVector(1.0f);
	Random_Spawned_Actor_Particle_Scale = FVector(1.0f);
	Can_Random_Spawn = false;
	Random_Spawn_Delay = 0.5f;
	Random_Dead_Cause_String = TEXT("RANDOM_OBS");
	Random_Spawn_Count_MAX= 10;
	Random_Spawn_Count_NOW = 0;
}

// Called when the game starts or when spawned
void ARandom_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARandom_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARandom_Spawner::NotifyActorBeginOverlap(AActor* Other)
{
	if (Other->IsA<APawn>())
	{
		Can_Random_Spawn = true;
		GetWorldTimerManager().SetTimer(Random_Spawner_TimerHandle, this, &ARandom_Spawner::Random_Spawn_Method, Random_Spawn_Delay, true);

	}
}

void ARandom_Spawner::NotifyActorEndOverlap(AActor* Other)
{
	if (Other->IsA<APawn>())
	{
		Can_Random_Spawn = false;
		GetWorldTimerManager().ClearTimer(Random_Spawner_TimerHandle);
	}
}

void ARandom_Spawner::Random_Spawn_Method()
{
	if (Random_Spawn_Count_NOW >= Random_Spawn_Count_MAX) return;

	FVector Random_Vec;
	Random_Vec = UKismetMathLibrary::RandomPointInBoundingBox(this->GetActorLocation() + Random_Spanwer_Spawn_Box->GetRelativeLocation(), Random_Spanwer_Spawn_Box->GetScaledBoxExtent());
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FVector SpawnLocation = Random_Vec;
	ASpawned_Trigger_Actor* Spawned_Random_Actor = GetWorld()->SpawnActor<ASpawned_Trigger_Actor>(ASpawned_Trigger_Actor::StaticClass(), SpawnLocation, this->GetActorRotation(), SpawnParams);
	Spawned_Random_Actor->Tags.Add(TEXT("Obstacle"));
	Spawned_Random_Actor->Tags.Add(TEXT("Destroy"));

	Spawned_Random_Actor->Spawned_Trigger_Actor_Mesh->SetStaticMesh(Random_Spawned_Actor_Mesh);
	Spawned_Random_Actor->Spawned_Trigger_Actor_Mesh->SetWorldScale3D(Random_Spawned_Actor_Scale);
	Spawned_Random_Actor->Obstacle_String = Random_Dead_Cause_String;
	Spawned_Random_Actor->SetLifeSpan(20.0f);
	if (Random_Spawned_Actor_Particle != nullptr)
	{
		Spawned_Random_Actor->Spawned_Trigger_Particle->SetTemplate(Random_Spawned_Actor_Particle);
		Spawned_Random_Actor->Spawned_Trigger_Particle->SetRelativeScale3D(Random_Spawned_Actor_Particle_Scale);
	}
	Random_Spawn_Count_NOW++;
}

