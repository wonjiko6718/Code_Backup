// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "User_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Spawned_Projectile_Actor.h"
// Sets default values
ATurret::ATurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Turret_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TURRET_MESH"));
	Turret_Detect_Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("TURRET_DETECT_SPHERE"));
	Turret_Activated_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TURRET_ACTIVATED_PARTICLE"));

	RootComponent = Turret_Mesh;
	Turret_Detect_Sphere->SetupAttachment(RootComponent);
	Turret_Activated_Particle->SetupAttachment(RootComponent);

	Turret_Activated = false;

	//StaticMesh'/Game/Import_SH/Mesh/Head/220512_KidHead.220512_KidHead'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Turret_Mesh_OF(TEXT("/Game/Import_SH/Mesh/Head/220512_KidHead.220512_KidHead"));
	if (Turret_Mesh_OF.Succeeded())
	{
		Turret_Mesh->SetStaticMesh(Turret_Mesh_OF.Object);
	}
	//ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_cutter1.P_ky_cutter1'
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Turret_Activated_Particle_OF(TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_cutter1.P_ky_cutter1"));
	if (Turret_Activated_Particle_OF.Succeeded())
	{
		Turret_Activated_Particle->SetTemplate(Turret_Activated_Particle_OF.Object);
	}
	Turret_Mesh->SetWorldScale3D(FVector(2.0f));
	Turret_Mesh->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));

	Turret_Detect_Sphere->SetRelativeScale3D(FVector(20.0f));
	Turret_Detect_Sphere->SetRelativeLocation(FVector(0.0f,0.0f,60.0f));

	Turret_Activated_Particle->SetRelativeScale3D(FVector(0.1f));
	Turret_Activated_Particle->SetRelativeLocation(FVector(70.0f,-35.0f,70.0f));
	Turret_Activated_Particle->SetRelativeRotation((FRotator(90.0f,0.0f,0.0f)));
	Turret_Activated_Particle->SetAutoActivate(false);

	Turret_Mesh->SetGenerateOverlapEvents(false);
	Turret_Detect_Sphere->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Turret_Activated && Follow_Player != nullptr)
	{
		FRotator Detect_Rotation = FRotator
		(
			UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Follow_Player->GetActorLocation())
		);
		SetActorRotation(Detect_Rotation);
	}
}
void ATurret::NotifyActorBeginOverlap(AActor* Other)
{
	if (Other->IsA<AUser_Character>())
	{
		UE_LOG(LogTemp, Error, TEXT("TurretDetected_Start"));
		Turret_Activated = true;
		Follow_Player = Other;
		Turret_Activated_Particle->SetActive(true);
		GetWorldTimerManager().SetTimer(Turret_TimerHandle, this, &ATurret::Turret_Shoot, 0.5f, true);

	}

}
void ATurret::NotifyActorEndOverlap(AActor* Other)
{
	if (Other->IsA<AUser_Character>())
	{
		UE_LOG(LogTemp, Error, TEXT("TurretDetected_End"));
		Turret_Activated = false;
		Follow_Player = this;
		Turret_Activated_Particle->SetActive(false);
		GetWorldTimerManager().ClearTimer(Turret_TimerHandle);
	}
}

void ATurret::Turret_Shoot()
{
	UE_LOG(LogTemp, Error, TEXT("Turret_Timer"));
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FVector SpawnLocation = this->GetActorLocation() + Turret_Activated_Particle->GetRelativeLocation() + FVector(0.0f,0.0f,50.0f);
	UE_LOG(LogTemp, Error, TEXT("User_Player_Pressed_Character_Method"));
	ASpawned_Projectile_Actor* Spawned_Projectile_Actor = GetWorld()->SpawnActor<ASpawned_Projectile_Actor>(ASpawned_Projectile_Actor::StaticClass(), SpawnLocation, this->GetActorRotation()+FRotator(-5.0f,0.0f,0.0f), SpawnParams);
	Spawned_Projectile_Actor->Tags.Add(TEXT("Obstacle"));
}
