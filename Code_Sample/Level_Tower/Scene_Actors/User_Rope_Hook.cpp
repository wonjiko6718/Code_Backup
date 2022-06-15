// Fill out your copyright notice in the Description page of Project Settings.

#include "User_Rope_Hook.h"
#include "Kismet/GameplayStatics.h"
#include "User_Character.h"

// Sets default values
AUser_Rope_Hook::AUser_Rope_Hook()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PROJECTILECOLLSION"));
	User_Rope_Hook_StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATICMESH"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));
	Rope_Hook_CableComp = CreateDefaultSubobject<UCableComponent>(TEXT("CABLECOMPONENT"));
	Rope_On_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ON_PARTICLE"));
	Rope_Fail_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OFF_PARTICLE"));
	Rope_Air_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Air_PARTICLE"));
	Rope_Hit_Sound = CreateDefaultSubobject<USoundBase>(TEXT("HIT_AUDIO"));
	Rope_SoundAttenuation_Setting = CreateDefaultSubobject<USoundAttenuation>(TEXT("SOUND_ATTENUATION"));

	RootComponent = ProjectileCollision;
	User_Rope_Hook_StaticMeshComp->SetupAttachment(RootComponent);
	User_Rope_Hook_StaticMeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 1.6f;
	User_Rope_Hook_StaticMeshComp->BodyInstance.SetCollisionProfileName(TEXT("Rope_Hook"));
	User_Rope_Hook_StaticMeshComp->CanCharacterStepUpOn = ECB_No;
	User_Rope_Hook_StaticMeshComp->SetEnableGravity(false);

	ProjectileCollision->BodyInstance.SetCollisionProfileName(TEXT("Rope_Hook"));
	ProjectileCollision->CanCharacterStepUpOn = ECB_No;
	ProjectileCollision->SetEnableGravity(false);
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	Rope_Hook_CableComp->SetupAttachment(RootComponent);
	Rope_Hook_CableComp->SetRelativeScale3D(FVector(1.5f));

	Rope_On_Particle->SetupAttachment(RootComponent);
	Rope_Fail_Particle->SetupAttachment(RootComponent);
	Rope_Air_Particle->SetupAttachment(RootComponent);


	Rope_SoundAttenuation_Setting->Attenuation.FalloffDistance = 2400.0f;

	//	ProjectileMovement->Bounciness = 0.3f;

	this->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
	// Find Static Mesh Root
	//StaticMesh'/Game/Import_SH/Mesh/220308_Jammin_Punch.220308_Jammin_Punch'
	//StaticMesh'/Game/Import_SH/Mesh/Hair_Sword/5_Sword_part3.5_Sword_part3'
	//StaticMesh'/Game/Import_SH/Mesh/Hair_Sword/6_Sword_part3.6_Sword_part3'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> User_Rope_Hook_StaticMeshComp_OF(TEXT("/Game/Import_SH/Mesh/Hair_Sword/6_Sword_part3.6_Sword_part3"));
	if (User_Rope_Hook_StaticMeshComp_OF.Succeeded())
	{
		User_Rope_Hook_StaticMeshComp->SetStaticMesh(User_Rope_Hook_StaticMeshComp_OF.Object);
	};
	//ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_hit_slash.P_ky_hit_slash'
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Rope_On_Particle_OF(TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_hit_slash.P_ky_hit_slash"));
	if (Rope_On_Particle_OF.Succeeded())
	{
		Rope_On_Particle->SetTemplate(Rope_On_Particle_OF.Object);
		Rope_On_Particle->bAutoActivate = false;
	}
	//ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact'
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Rope_Fail_Particle_OF(TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact"));
	if (Rope_Fail_Particle_OF.Succeeded())
	{
		Rope_Fail_Particle->SetTemplate(Rope_Fail_Particle_OF.Object);
		Rope_Fail_Particle->bAutoActivate = false;
	}
	//ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_stabShot.P_ky_stabShot'
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Rope_Air_Particle_OF(TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_stabShot.P_ky_stabShot"));
	if (Rope_Air_Particle_OF.Succeeded())
	{
		Rope_Air_Particle->SetTemplate(Rope_Air_Particle_OF.Object);
		Rope_Air_Particle->bAutoActivate = true;
	}
	//SoundCue'/Game/Damage_Hit_Sound/Cue/Stone_Hit/Stone_Hit_34_Cue.Stone_Hit_34_Cue'
	static ConstructorHelpers::FObjectFinder<USoundBase> Rope_Hit_Sound_OF(TEXT("/Game/Damage_Hit_Sound/Cue/Stone_Hit/Stone_Hit_34_Cue.Stone_Hit_34_Cue"));
	if (Rope_Hit_Sound_OF.Succeeded())
	{
		Rope_Hit_Sound = Rope_Hit_Sound_OF.Object;
	}
	//Material'/Game/Import_SH/Mesh/Hair_Sword/HairSword.HairSword'
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Rope_Material_OF(TEXT("/Game/Import_SH/Mesh/Hair_Sword/HairSword.HairSword"));
	if (Rope_Material_OF.Succeeded())
	{
		Rope_Hook_CableComp->SetMaterial(0,Rope_Material_OF.Object);
	}

}

// Called when the game starts or when spawned
void AUser_Rope_Hook::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner() != NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Get Owner Name: %s"), *GetOwner()->GetName());
		Rope_Hook_Owner = GetOwner();
		Rope_Hook_CableComp->SetAttachEndTo(GetOwner(),FName(TEXT("Mesh")), FName(TEXT("Sword_Socket")));
		Rope_Hook_CableComp->SetRelativeLocation(FVector(0.0f,0.0f,0.0f));
		Rope_Hook_CableComp->EndLocation = FVector(0.0f, -5.0f, 0.0f);
	}
}

// Called every frame
void AUser_Rope_Hook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetOwner() != NULL)
	{
		GetDistanceTo(Rope_Hook_Owner);
		//UE_LOG(LogTemp, Error, TEXT("Get Owner to Distance: %f"),GetDistanceTo(Rope_Hook_Owner));
		//UE_LOG(LogTemp, Error, TEXT("Get Owner Location: %s"), *GetOwner()->GetActorLocation().ToString());

		if (GetDistanceTo(Rope_Hook_Owner) >= 2000.0f)
		{
			ProjectileMovement->Velocity = FVector(GetOwner()->GetActorLocation() - GetActorLocation());
		}
		if (GetLifeSpan() <= 0.02f)
		{
			AUser_Character* Owner_User;
			Owner_User = Cast<AUser_Character>(GetOwner());
			UE_LOG(LogTemp, Error, TEXT("GetLifeSpan On"));
			Owner_User->Can_Rope_Action = true;
			Owner_User->In_Socket_Weapon->SetStaticMesh(Owner_User->Weapon);
			Owner_User->Re_Armed_Particle->SetActive(true);
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
		Rope_Air_Particle->SetActive(false);
		UGameplayStatics::PlaySoundAtLocation(this,Rope_Hit_Sound,GetActorLocation(),1.0f,1.0f,0.0f,Rope_SoundAttenuation_Setting);
		if (Other->ActorHasTag("Stick"))
		{
			Rope_On_Particle->Activate(true);
			AUser_Character* Owner_User;
			Owner_User = Cast<AUser_Character>(GetOwner());
			Owner_User->Rope_Launch(GetActorLocation());
			Owner_User->User_Stop_All_Montage();
		}
		else
		{
			Rope_Fail_Particle->Activate(true);
		}
	}

}
void AUser_Rope_Hook::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}
