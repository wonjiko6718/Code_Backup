// Fill out your copyright notice in the Description page of Project Settings.


#include "Ah_My_Friend.h"
#include "Kismet/KismetMathLibrary.h"
#include "User_Character.h"
// Sets default values
AAh_My_Friend::AAh_My_Friend()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Friend_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FRIEND_MESH"));
	Friend_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("FRIEND_MOVEMENT"));
	Friend_Detect_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Detect_Box"));
	Friend_Spawn_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FRIEND_SPAWN_PARTICLE"));
	Friend_Hit_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FRIEND_HIT_PARTICLE"));

	RootComponent = Friend_Mesh;
	Friend_Detect_Box->SetupAttachment(RootComponent);
	Friend_Detect_Box->SetRelativeLocation(this->GetActorForwardVector() * 100.0f);

	Friend_Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Friend_Detect_Box->SetCollisionProfileName(TEXT("OverlapAll"));

	Friend_Spawn_Particle->bAutoActivate = false;
	Friend_Hit_Particle->bAutoActivate = false;

	Friend_LifeTime = 3.0f;
	InitialLifeSpan = Friend_LifeTime;


	Friend_Movement->InitialSpeed = 3000.0f;
	Friend_Movement->MaxSpeed = 3000.0f;
	Friend_Movement->bRotationFollowsVelocity = false;
	Friend_Movement->bShouldBounce = false;
	Friend_Movement->ProjectileGravityScale = 0.0f;

	Friend_Activate = false;
	Friend_Movement->bSimulationEnabled = false;
	Friend_Mesh->SetHiddenInGame(true);

	Friend_GetBack = false;

	Friend_String = TEXT("Car");

	//this->SetLifeSpan(3.0f);

	//StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Friend_Mesh_OF(TEXT("/Game/StarterContent/Props/MaterialSphere.MaterialSphere"));
	if (Friend_Mesh_OF.Succeeded())
	{
		Friend_Mesh->SetStaticMesh(Friend_Mesh_OF.Object);
	}


}

// Called when the game starts or when spawned
void AAh_My_Friend::BeginPlay()
{
	Super::BeginPlay();
	//FRotator Friend_LookAt = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Friend_Detect_Box->GetRelativeLocation());
	//this->SetActorRotation(Friend_LookAt);
}
// Called every frame
void AAh_My_Friend::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Friend_Activate == false)
	{
		SetLifeSpan(Friend_LifeTime);
	}
	if (GetLifeSpan() <= Friend_LifeTime / 2 && Friend_GetBack == true)
	{
		//this->AddActorLocalRotation(FRotator(0.0f, 180.0f, 0.0f));
		Friend_GetBack = false;
		UE_LOG(LogTemp, Error, TEXT("GetBack"));
		Friend_Movement->Velocity = -(Friend_Movement->Velocity);

	}

}
void AAh_My_Friend::Friend_Shoot()
{
	Friend_Mesh->SetCollisionProfileName(TEXT("Projectile_Turret"));
	Friend_Movement->bSimulationEnabled = true;
	Friend_Mesh->SetHiddenInGame(false);
	Friend_Spawn_Particle->Activate(true);
	
}

void AAh_My_Friend::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA<AUser_Character>())
	{
		Friend_Activate = true;
		Friend_Shoot();
	}
}

void AAh_My_Friend::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Other->IsA<AUser_Character>())
	{
		AUser_Character* DetectOther = Cast<AUser_Character>(Other);
		DetectOther->Player_Dead_Cause = Friend_String;
		DetectOther->User_Die();
		if (Friend_Hit_Particle != nullptr)
		{
			Friend_Hit_Particle->SetWorldLocation(HitLocation);
			Friend_Hit_Particle->Activate(true);
		}
	}
}

