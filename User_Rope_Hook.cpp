// Fill out your copyright notice in the Description page of Project Settings.


#include "User_Character.h"
#include "User_Rope_Hook.h"

// Sets default values
AUser_Rope_Hook::AUser_Rope_Hook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PROJECTILECOLLSION"));
	User_Rope_Hook_StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATICMESH"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));

	RootComponent = ProjectileCollision;
	User_Rope_Hook_StaticMeshComp->SetupAttachment(RootComponent);
	User_Rope_Hook_StaticMeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 2.0f;
	User_Rope_Hook_StaticMeshComp->BodyInstance.SetCollisionProfileName(TEXT("Rope_Hook"));
	User_Rope_Hook_StaticMeshComp->CanCharacterStepUpOn = ECB_No;
	User_Rope_Hook_StaticMeshComp->SetEnableGravity(false);

	ProjectileCollision->BodyInstance.SetCollisionProfileName(TEXT("Rope_Hook"));
	ProjectileCollision->CanCharacterStepUpOn = ECB_No;
	ProjectileCollision->SetEnableGravity(false);
	ProjectileMovement->ProjectileGravityScale = 0.0f;

//	ProjectileMovement->Bounciness = 0.3f;

	this->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
	// Find Static Mesh Root
	//StaticMesh'/Game/Import_SH/Mesh/220308_Jammin_Punch.220308_Jammin_Punch'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> User_Rope_Hook_StaticMeshComp_OF(TEXT("/Game/Import_SH/Mesh/220308_Jammin_Punch.220308_Jammin_Punch"));
	if (User_Rope_Hook_StaticMeshComp_OF.Succeeded())
	{
		User_Rope_Hook_StaticMeshComp->SetStaticMesh(User_Rope_Hook_StaticMeshComp_OF.Object);
	};
}

// Called when the game starts or when spawned
void AUser_Rope_Hook::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner() != NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Get Owner Name: %s"), *GetOwner()->GetName());
		Rope_Hook_Owner = GetOwner();
	}
}

// Called every frame
void AUser_Rope_Hook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetOwner() != NULL)
	{
		GetDistanceTo(Rope_Hook_Owner);
		UE_LOG(LogTemp, Error, TEXT("Get Owner to Distance: %f"),GetDistanceTo(Rope_Hook_Owner));
		UE_LOG(LogTemp, Error, TEXT("Get Owner Location: %s"), *GetOwner()->GetActorLocation().ToString());

		if (GetDistanceTo(Rope_Hook_Owner) >= 2000.0f)
		{
			ProjectileMovement->Velocity = FVector(GetOwner()->GetActorLocation() - GetActorLocation());
		}
	}
}
void AUser_Rope_Hook::NotifyHit // Hit to Attatch
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
	UE_LOG(LogTemp, Error, TEXT("Hook Hit"));
	if (GetOwner() != NULL)
	{
		AUser_Character* Owner_User;
		Owner_User = Cast<AUser_Character>(GetOwner());
		Owner_User->Rope_Launch(GetActorLocation());
	}

}
void AUser_Rope_Hook::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}
