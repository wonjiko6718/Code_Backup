// Fill out your copyright notice in the Description page of Project Settings.


#include "User_Character.h"
#include "User_Character_AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Code_SampleGameMode.h"
#include "User_Rope_Hook.h"
#include "Spawned_Projectile_Actor.h"
#include "Spawned_Trigger_Actor.h"
// Sets default values
AUser_Character::AUser_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject <USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject <UCameraComponent>(TEXT("Camera"));
	User_Detect_Capsule = CreateDefaultSubobject <UCapsuleComponent>(TEXT("USER_DETECT_CAPSULE"));
	Weapon = CreateDefaultSubobject<UStaticMesh>(TEXT("WEAPON_MESH"));
	Half_Weapon = CreateDefaultSubobject<UStaticMesh>(TEXT("HALF_WEAPON_MESH"));
	In_Socket_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IN_SOCKET_WEAPON"));
	Re_Armed_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RE_ARMED_PARTICLE"));


	SpringArm->SetupAttachment(GetCapsuleComponent());
	User_Detect_Capsule->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	Re_Armed_Particle->SetupAttachment(In_Socket_Weapon);

	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	this->bUseControllerRotationYaw = false;
	this->Tags.Add(TEXT("User_Character"));
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 900.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 800.0f;
	// Capsules Setting
	GetCapsuleComponent()->SetCapsuleSize(30.0f, 90.0f);

	User_Detect_Capsule->SetCapsuleHalfHeight(95.0f);
	User_Detect_Capsule->SetCapsuleRadius(35.0f);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	Re_Armed_Particle->SetRelativeScale3D(FVector(0.2f));
	Re_Armed_Particle->SetRelativeRotation(FRotator(0.0f, 0.0f, -110.0f));

	FName Weapon_Socket_Name (TEXT("Sword_Socket"));
	//User Normal Var
	PlayerSpeed = 1.0f;
	WallTouch = false;
	Air_Dash_Now = false;
	WallRun_Now = false;
	Can_Rope_Action = true;
	Player_Dead_Cause = "None_Dead";
	//Set Design of Character
	// File : Game/GhostLady_S4/Meshes/Characters/Combines/SK_GLS4_B.SK_GLS4_B
	// File : SkeletalMesh'/Game/Import_SH/Character/0316/21.21'
	// File : SkeletalMesh'/Game/Import_SH/Character/0328/Mesh/Main_Character_Male_0328.Main_Character_Male_0328'
	// File : SkeletalMesh'/Game/Import_SH/Character/0517/Male_Char.Male_Char'
	// File : SkeletalMesh'/Game/Import_SH/Character/0603/220603_Male.220603_Male'
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> User_Character_SkelMesh_OF(TEXT("/Game/Import_SH/Character/0603/220603_Male.220603_Male"));
	if (User_Character_SkelMesh_OF.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(User_Character_SkelMesh_OF.Object);
	}
	// File : AnimBlueprint'/Game/Self_Anim_BP/User_Anim_BP.User_Anim_BP'
	// File : AnimBlueprint'/Game/Retarget_Anim/Main_Char_Retarget/User_Anim_BP.User_Anim_BP'
	// File : AnimBlueprint'/Game/Import_SH/Character/0328/Anim_Retarget/User_Anim_BP.User_Anim_BP'
	// File : AnimBlueprint'/Game/Retarget_Anim/Main_Char_Retarget_Fixed/User_Anim_BP.User_Anim_BP'
	// File : AnimBlueprint'/Game/Retarget_Anim/Main_Char_Retarget_0603/User_Anim_BP.User_Anim_BP'
	static ConstructorHelpers::FClassFinder<UAnimInstance> User_Character_AnimInstance_OF(TEXT("/Game/Retarget_Anim/Main_Char_Retarget_0603/User_Anim_BP.User_Anim_BP_C"));
	if (User_Character_AnimInstance_OF.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(User_Character_AnimInstance_OF.Class);
	}
	//StaticMesh'/Game/Import_SH/Mesh/Hair_Sword/5_Sword_part3.5_Sword_part3'
	//StaticMesh'/Game/Import_SH/Mesh/Hair_Sword/6_Sword_part1.6_Sword_part1'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Half_Weapon_OF(TEXT("/Game/Import_SH/Mesh/Hair_Sword/6_Sword_part1.6_Sword_part1"));
	if (Half_Weapon_OF.Succeeded())
	{
		Half_Weapon = Half_Weapon_OF.Object;
	}
	//StaticMesh'/Game/Import_SH/Mesh/Hair_Sword/6-1.6-1'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cons_Weapon(TEXT("/Game/Import_SH/Mesh/Hair_Sword/6-1.6-1"));
	if (Cons_Weapon.Succeeded())
	{
		Weapon = Cons_Weapon.Object;
	}
	if (GetMesh()->DoesSocketExist(Weapon_Socket_Name))
	{
		In_Socket_Weapon->SetStaticMesh(Weapon);
		In_Socket_Weapon->SetupAttachment(GetMesh(), Weapon_Socket_Name);
	}
	//ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_burst.P_ky_burst'
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Re_Armed_Particle_OF(TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_burst.P_ky_burst"));
	if (Re_Armed_Particle_OF.Succeeded())
	{
		Re_Armed_Particle->SetTemplate(Re_Armed_Particle_OF.Object);
		Re_Armed_Particle->SetAutoActivate(false);
	}

}

// Called when the game starts or when spawned

void AUser_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//Link User AnimInstace for Something Call
	User_Character_AnimInstance = Cast<UUser_Character_AnimInstance>(GetMesh()->GetAnimInstance());
	User_Character_AnimInstance->OnMontageEnded.AddDynamic(this, &AUser_Character::End_Montage_Trail);
}
void AUser_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUser_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Player_Dead_Cause == "None_Dead")
	{
		/*
		if (GetCharacterMovement()->IsFalling())
		{
			GetController()->SetIgnoreMoveInput(true);
		}
		else
		{
			GetController()->ResetIgnoreMoveInput();
		}
		*/
	}
	else
	{
		GetController()->SetIgnoreMoveInput(true);
		GetController()->SetIgnoreLookInput(true);
		GetCharacterMovement()->StopMovementImmediately();
		/*
		FRotator CamRot = UKismetMathLibrary::FindLookAtRotation(Camera->GetRelativeLocation(), GetMesh()->GetRelativeLocation());
		CamRot = FRotator(CamRot.Pitch, CamRot.Yaw, 0.0f);
		Camera->SetRelativeRotation(CamRot);
		*/
	}
	//TraceCode
	FHitResult OutHit;
	FVector LT_Start_Vec = GetActorLocation();
	FVector LT_End_Vec = GetActorUpVector() * 50.0f;
	FCollisionQueryParams CollisionParams(NAME_None,false,this);
	GetWorld()->SweepSingleByChannel(OutHit, LT_Start_Vec, LT_End_Vec, FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeSphere(50.0f), CollisionParams);
	//DrawDebugCapsule(GetWorld(), LT_Start_Vec+LT_End_Vec*0.5f,100.0f*0.5f+50.0,50.0f,FRotationMatrix::MakeFromZ(LT_End_Vec).ToQuat(),OutHit.bBlockingHit? FColor::Green : FColor::Red,false,0.1f);
	//If You Need Debug Drawing, Delete Slash Lines of UnderLine
	if (OutHit.bBlockingHit && WallTouch == true)
	{
		float degree = Cal_Forward_Target_Degree(OutHit.ImpactPoint);
		GetCharacterMovement()->Velocity = FVector(GetActorForwardVector() * 800.0f);
		//UE_LOG(LogTemp, Warning, TEXT("Lay_Trace:HittingActor Location : %f"), degree);
		if (degree > 1.0f)
		{
			if (degree > 90.0f)
			{
				degree = 90.0f;
			}
			//UE_LOG(LogTemp, Error, TEXT("Wall On Right"));
			AddActorLocalRotation((FRotator(0.0f, -(90 - degree), 0.0f)));
			//SetActorRotation((FRotator(0.0f, -(90 - degree), 0.0f)));
		}
		else if (degree < -1.0f)
		{
			if (degree < -90.0f)
			{
				degree = -90.0f;
			}
			//UE_LOG(LogTemp, Error, TEXT("Wall On Left"));
			AddActorLocalRotation((FRotator(0.0f, -(-90 - degree), 0.0f)));
			//SetActorRotation((FRotator(0.0f, -(-90 - degree), 0.0f)));

		}
	}
	if (OutHit.bBlockingHit)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Lay_Trace:HittingActor Location : %s"),*OutHit.Actor->GetName());
	}

}
void AUser_Character::End_Montage_Trail(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Error, TEXT("Montage is Ended"));
	GetController()->ResetIgnoreMoveInput();

}
void AUser_Character::NotifyActorBeginOverlap(AActor* Other)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Overlap Acting : %s"), *Other->GetName());
	if (Other->ActorHasTag("Floor")) // Floor Overlap Setting, OnGrounded
	{
		User_Character_AnimInstance->StopAllMontages(0.35f);
	}
	if (Other->ActorHasTag("Wall") && GetCharacterMovement()->IsFalling()) // Wall Launch Details
	{
		GetCharacterMovement()->GravityScale = 0.75f;

	}
}
void AUser_Character::NotifyActorEndOverlap(AActor* Other)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Overlap Ending Target : %s"), *Other->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Notify End Overlap"));
	if (Other->ActorHasTag(TEXT("Wall")))
	{
		WallTouch = false;
		UE_LOG(LogTemp, Warning, TEXT("Wall Touch : False"));
		User_Character_AnimInstance->StopWallRun_Montage();
		GetCharacterMovement()->GravityScale = 1.0f;
	}
}
void AUser_Character::NotifyHit
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
	//UE_LOG(LogTemp, Error, TEXT("Notify_Hit_Actor : %s"),*Other->GetName());
	//UE_LOG(LogTemp, Error, TEXT("Notify Hit Location : %s"), *(HitLocation-GetActorLocation()).ToString());
	float degree = Cal_Forward_Target_Degree(HitLocation);
	if (Other->ActorHasTag(TEXT("Wall")) && GetCharacterMovement()->IsFalling() &&WallTouch == false)
	{	
		WallTouch = true;
		UE_LOG(LogTemp, Error, TEXT("Wall Dir By Character : %f"), degree);
		GetController()->SetIgnoreMoveInput(true);
		//SetActorRotation((FRotator(0.0f, (-90 - degree), 0.0f)));
		//AddActorLocalRotation((FRotator(0.0f, (90-degree), 0.0f)));
		if (degree > 1.0f)
		{
			if (degree > 90.0f)
			{
				degree = 90.0f;
			}
			UE_LOG(LogTemp, Error, TEXT("Wall On Right"));
			User_Character_AnimInstance->PlayWallRun_R_Montage();
			//LaunchCharacter((GetActorForwardVector() + FVector(0.0f, 0.0f, 0.2f)) * 500.0f, false, false);

			WallDir = 1;
			//SetActorRotation((FRotator(0.0f, -(90 - degree), 0.0f)));
		}
		else if (degree < -1.0f)
		{
			if (degree < -90.0f)
			{
				degree = -90.0f;
			}
			UE_LOG(LogTemp, Error, TEXT("Wall On Left"));
			User_Character_AnimInstance->PlayWallRun_L_Montage();

			WallDir = -1;
			//SetActorRotation((FRotator(0.0f, -(-90 - degree), 0.0f)));

		}
	}
	if (Other->ActorHasTag(TEXT("Floor")))
	{
		WallTouch = false;
		WallDir = 0;
	}
	if (Other->ActorHasTag(TEXT("Obstacle")))
	{
		//LaunchCharacter(FVector(GetActorLocation() - Other->GetActorLocation().Normalize() * 1000.0f),false,false);
		if (Other->IsA<ASpawned_Trigger_Actor>())
		{
			UE_LOG(LogTemp, Error, TEXT("Detect Obstacle"));
			ASpawned_Trigger_Actor* Player_Obstacle_Actor = Cast<ASpawned_Trigger_Actor>(Other);
			Player_Dead_Cause = Player_Obstacle_Actor->Obstacle_String;
			User_Die();

		}
		if (Other->IsA<ASpawned_Projectile_Actor>())
		{
			UE_LOG(LogTemp, Error, TEXT("Detect Obstacle"));
			ASpawned_Projectile_Actor* Player_Obstacle_Actor = Cast<ASpawned_Projectile_Actor>(Other);
			Player_Dead_Cause = Player_Obstacle_Actor->Spawned_Projectile_String;
			User_Die();
		}
	}
}
float AUser_Character::Cal_Forward_Target_Degree(FVector TargetLocation)
{
	FVector OwnerLocation = GetActorLocation();
	FVector ToTargetVec = (TargetLocation - OwnerLocation);
	ToTargetVec *= FVector(1.f, 1.f, 0.f);
	ToTargetVec.Normalize();

	FVector OwnerForwardVec = GetActorForwardVector();
	float InnerProduct = FVector::DotProduct(OwnerForwardVec, ToTargetVec);
	float TargetDegree = UKismetMathLibrary::DegAcos(InnerProduct);
	
	FVector OutterProduct = FVector::CrossProduct(OwnerForwardVec, ToTargetVec);
	float DegSign = UKismetMathLibrary::SignOfFloat(OutterProduct.Z);

	float Result = TargetDegree * DegSign;
	//float degree = (Other->GetActorLocation() - this->GetActorLocation()).Rotation().Yaw;


	return Result;
}
// User Another Function

void AUser_Character::Character_Play_RopeAction() // Play AnimMontage and Check Notify
{
	if (Can_Rope_Action)
	{
		SetActorRotation(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
		User_Character_AnimInstance->PlayRopeAction_Montage();
		UE_LOG(LogTemp, Error, TEXT("Character_Play_RopeAction"));
		GetController()->SetIgnoreMoveInput(true);
	}
}

void AUser_Character::Shoot_Rope() //Spawn Rope Hook, Launch When Montage Notify Activated
{
	if (Can_Rope_Action)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FVector SpawnLocation = this->GetActorLocation() + GetActorForwardVector() * 100.0f;
		UE_LOG(LogTemp, Error, TEXT("User_Player_Pressed_Character_Method"));
		AUser_Rope_Hook* Rope_Hook = GetWorld()->SpawnActor<AUser_Rope_Hook>(AUser_Rope_Hook::StaticClass(), SpawnLocation, GetControlRotation(), SpawnParams);
		Can_Rope_Action = false;
		In_Socket_Weapon->SetStaticMesh(Half_Weapon);
		//StaticMesh'/Game/Import_SH/Mesh/Hair_Sword/5_Sword_part3.5_Sword_part3'
	}
}
void AUser_Character::Rope_Launch(FVector TargetLocation)
{
	GetCharacterMovement()->StopMovementImmediately();
	FVector LaunchDir = TargetLocation - GetActorLocation();
	LaunchDir.Normalize(); // Direction to Target
	LaunchCharacter(LaunchDir * 1500.0f, false, false);
}
void AUser_Character::User_Stop_All_Montage()
{
	User_Character_AnimInstance->StopAllMontages(0.35f);
}
void AUser_Character::User_Die()
{
	UE_LOG(LogTemp, Error, TEXT("User_Player_IsDead"));
	GetCharacterMovement()->StopMovementImmediately();
	ACode_SampleGameMode* Character_Get_Gamemode = (ACode_SampleGameMode*)GetWorld()->GetAuthGameMode();
	Character_Get_Gamemode->Player_Dead_Cause = Player_Dead_Cause;
	//GetCapsuleComponent()->SetMobility(EComponentMobility::Static);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	GetCharacterMovement()->StopMovementImmediately();


	User_Character_AnimInstance->StopAllMontages(0.1f);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
	GetWorldSettings()->SetTimeDilation(0.3f);
	Character_Get_Gamemode->GameMode_GameOver();
}