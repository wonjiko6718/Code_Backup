// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawned_Projectile_Actor.h"

// Sets default values
ASpawned_Projectile_Actor::ASpawned_Projectile_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spawned_Projectile_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SPAWNED_PROJECTILE_MESH"));
	Spawned_Projectile_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPAWNED_PROJECTILE_PARTICLE"));
	Spawned_Projectile_Hit_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPAWNED_PROJECTILE_HIT_PARTICLE"));
	Spawned_Projectile_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("SPAWNED_PROJECTILE_MOVEMENT"));
	Spawned_Projectile_Material = CreateDefaultSubobject<UMaterial>(TEXT("SPAWNED_PROJECTILE_MATERIAL"));


	Spawned_Projectile_Mesh->SetRelativeRotation(FRotator(0.0f,0.0f,90.0f));
	Spawned_Projectile_Mesh->SetRelativeScale3D(FVector(5.0f,0.5f,0.25f));
	Spawned_Projectile_Mesh->SetEnableGravity(false);
	Spawned_Projectile_Mesh->SetCollisionProfileName(FName("Projectile_Turret"));
	RootComponent = Spawned_Projectile_Mesh;
	Spawned_Projectile_Particle->SetupAttachment(RootComponent);
	Spawned_Projectile_Particle->SetRelativeLocation(FVector(35.0f,0.0f,0.0f));
	
	Spawned_Projectile_String = "WA!";
	InitialLifeSpan = 3.0f;
	//StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Spawned_Projectile_Mesh_OF(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (Spawned_Projectile_Mesh_OF.Succeeded())
	{
		Spawned_Projectile_Mesh->SetStaticMesh(Spawned_Projectile_Mesh_OF.Object);
	}
	//MaterialInstanceConstant'/Game/AdvancedMagicFX13/Materials/MI_ky_primitiveColor.MI_ky_primitiveColor'
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Spawned_Projectile_Material_OF(TEXT("/Game/AdvancedMagicFX13/Materials/MI_ky_primitiveColor.MI_ky_primitiveColor"));
	if (Spawned_Projectile_Material_OF.Succeeded())
	{
		Spawned_Projectile_Mesh->SetMaterial(0, Spawned_Projectile_Material_OF.Object);
	}
	//ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_flash2.P_ky_flash2'
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Spawned_Projectile_Particle_OF(TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_flash2.P_ky_flash2"));
	if (Spawned_Projectile_Particle_OF.Succeeded())
	{
		Spawned_Projectile_Particle->SetTemplate(Spawned_Projectile_Particle_OF.Object);
	}
	//ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_shine.P_ky_hit_shine'
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Spawned_Projectile_Hit_Particle_OF(TEXT("/Game/AdvancedMagicFX12/particles/P_ky_hit_shine.P_ky_hit_shine"));
	if(Spawned_Projectile_Hit_Particle_OF.Succeeded())
	{
		Spawned_Projectile_Hit_Particle->SetTemplate(Spawned_Projectile_Hit_Particle_OF.Object);
	}
	Spawned_Projectile_Movement->InitialSpeed = 2000.0f;
	Spawned_Projectile_Movement->ProjectileGravityScale = 0.0f;

	Spawned_Projectile_Hit_Particle->bAutoActivate = false;

}

// Called when the game starts or when spawned
void ASpawned_Projectile_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawned_Projectile_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawned_Projectile_Actor::NotifyHit
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
	if (Other->IsA<APawn>())
	{
		Spawned_Projectile_Hit_Particle->SetWorldLocation(Other->GetActorLocation());
		Spawned_Projectile_Hit_Particle->SetActive(true);
	}
}

