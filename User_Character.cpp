// Fill out your copyright notice in the Description page of Project Settings.


#include "User_Character.h"
#include "User_Character_AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
// Sets default values
AUser_Character::AUser_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject <USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject <UCameraComponent>(TEXT("Camera"));
	User_Detect_Capsule = CreateDefaultSubobject <UCapsuleComponent>(TEXT("USER_DETECT_CAPSULE"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	User_Detect_Capsule->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	this->bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 900.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 800.0f;
	// Capsules Setting
	GetCapsuleComponent()->SetCapsuleSize(30.0f, 90.0f);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AUser_Character::OnHit);

	User_Detect_Capsule->SetCapsuleHalfHeight(95.0f);
	User_Detect_Capsule->SetCapsuleRadius(35.0f);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//User Normal Var
	PlayerSpeed = 1.0f;
	WallTouch = false;
	Air_Dash_Now = false;
	WallRun_Now = false;
	//Set Design of Character
	/// File : Game/GhostLady_S4/Meshes/Characters/Combines/SK_GLS4_B.SK_GLS4_B
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> User_Character_SkelMesh_OF(TEXT("/Game/GhostLady_S4/Meshes/Characters/Combines/SK_GLS4_B.SK_GLS4_B"));
	if (User_Character_SkelMesh_OF.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(User_Character_SkelMesh_OF.Object);
	}
	// File : AnimBlueprint'/Game/Self_Anim_BP/User_Anim_BP.User_Anim_BP'
	static ConstructorHelpers::FClassFinder<UAnimInstance> User_Character_AnimInstance_OF(TEXT("/Game/Self_Anim_BP/User_Anim_BP.User_Anim_BP_C"));
	if (User_Character_AnimInstance_OF.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(User_Character_AnimInstance_OF.Class);
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

	if (GetCharacterMovement()->IsFalling())
	{
		GetController()->SetIgnoreMoveInput(true);
	}
	else
	{
		GetController()->ResetIgnoreMoveInput();
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
}
void AUser_Character::End_Montage_Trail(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Error, TEXT("Trail Montage is Ended"));
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
	UE_LOG(LogTemp, Error, TEXT("Notify_Hit_Actor : %s"),*Other->GetName());
	UE_LOG(LogTemp, Error, TEXT("Notify Hit Location : %s"), *(HitLocation-GetActorLocation()).ToString());
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

void AUser_Character::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*
	if (OtherActor->ActorHasTag("Floor"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Hit Acting : %s"), *OtherActor->GetName());
		WallTouch = false;
		this->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));

	}
	if (OtherActor->ActorHasTag("Wall") && WallTouch == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Hit Acting : %s"), *OtherActor->GetName());
		WallTouch = true;
		this->SetActorRotation(FRotator(0.0f, 0.0f, 30.0f));
	}
	*/
}