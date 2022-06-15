// Fill out your copyright notice in the Description page of Project Settings.

#include "User_Character.h"
#include "Destroy_Building.h"

// Sets default values
ADestroy_Building::ADestroy_Building()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Destroy_Building_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DESTROY_BUILDING_MESH"));
	Destroy_Building_Detect = CreateDefaultSubobject<UBoxComponent>(TEXT("DESTROY_BUILDING_DETECT"));
	Destroy_Building_Particle_NG_Comp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DESTROY_BUILDING_PARTICLE_NG_COMP"));
	RootComponent = Destroy_Building_Mesh;

	Destroy_Building_Particle_NG_Comp->SetupAttachment(RootComponent);
	Destroy_Building_Detect->SetupAttachment(RootComponent);

	Destroy_Building_Mesh->SetGenerateOverlapEvents(false);
	Destroy_Building_Mesh->SetNotifyRigidBodyCollision(true);
	Destroy_Building_Mesh->BodyInstance.bLockTranslation = true;
	Destroy_Building_Mesh->BodyInstance.bLockXRotation = true;
	Destroy_Building_Mesh->BodyInstance.bLockZRotation = true;
	Destroy_Building_Mesh->SetSimulatePhysics(false);

	Destroy_Building_HitStack = 0;
	Destroy_Building_CanKill = true;
	Destroy_Building_String = TEXT("SSSSSSSS");
	Destroy_Building_Particle_NG_Comp->SetRelativeScale3D(FVector(4.0f));
	Destroy_Building_Particle_NG_Comp->SetAutoActivate(false);


	//StaticMesh'/Game/Medieval_Environment/Medieval_Castle_Vol1/Meshes/Merged/SM_Tower_Round_03_Exterior.SM_Tower_Round_03_Exterior'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Destroy_Building_Mesh_OF(TEXT("/Game/Medieval_Environment/Medieval_Castle_Vol1/Meshes/Merged/SM_Tower_Round_03_Exterior.SM_Tower_Round_03_Exterior"));
	if (Destroy_Building_Mesh_OF.Succeeded())
	{
		Destroy_Building_Mesh->SetStaticMesh(Destroy_Building_Mesh_OF.Object);
	}
	//NiagaraSystem'/Game/Import_SH/Particle/Bust/Break_Building.Break_Building'
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Destroy_Building_Particle_NG_OF(TEXT("/Game/Import_SH/Particle/Bust/Break_Building.Break_Building"));
	if (Destroy_Building_Particle_NG_OF.Succeeded())
	{
		Destroy_Building_Particle_NG_Comp->SetAsset(Destroy_Building_Particle_NG_OF.Object);
	}

}

// Called when the game starts or when spawned
void ADestroy_Building::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroy_Building::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroy_Building::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Other->ActorHasTag("Destroy_Hit") && Destroy_Building_HitStack < 2)
	{
		UE_LOG(LogTemp, Error, TEXT("NOTIFY_DESTROY_BUILD"));
		Destroy_Building_Particle_NG_Comp->SetWorldLocation(HitLocation);
		Destroy_Building_Particle_NG_Comp->SetActive(true);
		Destroy_Building_HitStack++;
		Destroy_Building_CanKill = false;

	}
	if (Other->ActorHasTag("User_Character") && Destroy_Building_CanKill)
	{
		Destroy_Building_Particle_NG_Comp->SetWorldLocation(HitLocation);
		Destroy_Building_Particle_NG_Comp->SetActive(true);
		Destroy_Building_HitStack++;
		AUser_Character* HitOther = Cast<AUser_Character>(Other);
		HitOther->Player_Dead_Cause = Destroy_Building_String;
		HitOther->User_Die();
	}
}

void ADestroy_Building::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("User_Character"))
	{
		Destroy_Building_Mesh->SetSimulatePhysics(true);
	}
}

