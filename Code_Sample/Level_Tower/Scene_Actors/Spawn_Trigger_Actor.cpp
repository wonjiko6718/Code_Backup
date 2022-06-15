// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn_Trigger_Actor.h"
#include "Spawned_Trigger_Actor.h"

// Sets default values
ASpawn_Trigger_Actor::ASpawn_Trigger_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spawn_Trigger_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER_BOX"));
	Spawn_Target_Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPAWN_SPHERE"));
	Spawn_Trigger_Actor = CreateDefaultSubobject<AActor>(TEXT("SPAWN_ACTOR"));
	Spawned_Actor_Mesh = CreateDefaultSubobject<UStaticMesh>(TEXT("SPAWN_ACTOR_MESH"));
	Spawned_Particle_System = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPAWN_ACTOR_PARTICLE"));

	RootComponent = Spawn_Trigger_Box;
	Spawn_Target_Sphere->SetupAttachment(RootComponent);
	Spawned_Particle_System->SetupAttachment(Spawn_Target_Sphere);
	Spawned_Particle_System->bAutoActivate = false;

	Spawn_Target_Sphere->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	Spawn_Target_Sphere->SetGenerateOverlapEvents(false);
	
	Spawned_Actor_Scale = FVector(1.0f, 1.0f, 1.0f);
	Spawned_Obstacle_String	= "Awesome";
	SpawnTag = TEXT("Obstacle");
	DetectTag = TEXT("All");
	SpawnCount = 1;
	
}

// Called when the game starts or when spawned
void ASpawn_Trigger_Actor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawn_Trigger_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASpawn_Trigger_Actor::NotifyActorBeginOverlap(AActor* Other)
{
	UE_LOG(LogTemp, Warning, TEXT("Notify Trigger_Actor"));
	UE_LOG(LogTemp, Warning, TEXT("SpawnTrigger Actor Name : %s"), *Spawn_Trigger_Actor->GetName());

	if (Spawn_Trigger_Actor != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn_Overlap_Method_Activated"));

		if (DetectTag == "All")
		{
			Spawn_Method();
		}
		if (DetectTag != "All" && Other->ActorHasTag(DetectTag))
		{
			Spawn_Method();
		}
	}
}
void ASpawn_Trigger_Actor::Spawn_Method()
{
	if (Spawn_Actor_Bool)
	{

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		//this->GetActorLocation() + Spawn_Target_Sphere->GetRelativeLocation());
		FVector SpawnLocation = Spawn_Target_Sphere->GetComponentLocation();
		FRotator SpawnRotation = Spawn_Target_Sphere->GetRelativeRotation();
		UE_LOG(LogTemp, Error, TEXT("User_Player_Pressed_Character_Method"));
		ASpawned_Trigger_Actor* SpawnActor = GetWorld()->SpawnActor<ASpawned_Trigger_Actor>(ASpawned_Trigger_Actor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		SpawnActor->Spawned_Trigger_Actor_Mesh->SetStaticMesh(Spawned_Actor_Mesh);
		SpawnActor->Spawned_Trigger_Actor_Mesh->SetWorldScale3D(Spawned_Actor_Scale);
		SpawnActor->Tags.Add(SpawnTag);
		SpawnActor->Tags.Add(TEXT("Destroy"));
		SpawnActor->Obstacle_String = Spawned_Obstacle_String;
		if (Spawned_Particle_System != nullptr)
		{
			SpawnActor->Spawned_Trigger_Particle->SetTemplate(Spawned_Particle_System->Template);
		}
		Destroy();
	}
	if (Spawn_Particle_Bool)
	{
		if (Spawned_Particle_System != nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Spawn_Particle_Activated"));
			Spawned_Particle_System->SetActive(true);
		}
	}
}