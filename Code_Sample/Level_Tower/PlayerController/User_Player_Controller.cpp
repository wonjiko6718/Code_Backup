// Fill out your copyright notice in the Description page of Project Settings.


#include "User_Player_Controller.h"

AUser_Player_Controller::AUser_Player_Controller() // Constructor
{
	PrimaryActorTick.bCanEverTick = true;
	// Possess to Pawn
	AController::Possess(GetPawn());

	//Properties Setting
	PlayerSpeed = 1.0f;
	Player_Aim_Now = false;
}
void AUser_Player_Controller::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
void AUser_Player_Controller::BeginPlay() // BeginPlay
{
	Super::BeginPlay();
	User_Pawn_Character = Cast<AUser_Character>(GetPawn());
	UE_LOG(LogTemp, Error, TEXT("User_Player_Controller Posses : %s"), *User_Pawn_Character->GetName());
	if (GetWorld()->GetName() == TEXT("MainMenu"))
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}
void AUser_Player_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	User_Aiming_Function(DeltaTime);
}
void AUser_Player_Controller::SetupInputComponent() // SetupInput
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("UpDown"), this, &AUser_Player_Controller::UpDown);
	InputComponent->BindAxis(TEXT("LeftRight"), this, &AUser_Player_Controller::LeftRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AUser_Player_Controller::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &AUser_Player_Controller::Turn);
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AUser_Player_Controller::User_Jump);
	InputComponent->BindAction(TEXT("Aimming"), EInputEvent::IE_Pressed, this, &AUser_Player_Controller::User_Aiming_Press);
	InputComponent->BindAction(TEXT("Aimming"), EInputEvent::IE_Released, this, &AUser_Player_Controller::User_Aiming_Release);
	InputComponent->BindAction(TEXT("Launch_Rope"), EInputEvent::IE_Pressed, this, &AUser_Player_Controller::User_Launch_Rope_Press);
	InputComponent->BindAction(TEXT("Restart"), EInputEvent::IE_Pressed, this, &AUser_Player_Controller::User_Restart);




}
void AUser_Player_Controller::UpDown(float NewAxisValue)
{
	FVector PlayerDir = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
	PlayerDir.Z = 0.0f;
	PlayerDir.Normalize();
	User_Pawn_Character->AddMovementInput(PlayerDir, NewAxisValue * PlayerSpeed);
}
void AUser_Player_Controller::LeftRight(float NewAxisValue)
{
	FVector PlayerDir = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);
	PlayerDir.Z = 0.0f;
	PlayerDir.Normalize();
	User_Pawn_Character->AddMovementInput(PlayerDir, NewAxisValue * PlayerSpeed);
}
void AUser_Player_Controller::LookUp(float NewAxisValue)
{
	User_Pawn_Character->AddControllerPitchInput(NewAxisValue);
}
void AUser_Player_Controller::Turn(float NewAxisValue)
{
	User_Pawn_Character->AddControllerYawInput(NewAxisValue);

}
void AUser_Player_Controller::User_Jump()
{
	if (User_Pawn_Character->GetCharacterMovement()->IsFalling() == false) //On Grounded - Normal Jump
	{
		User_Pawn_Character->LaunchCharacter(FVector(0.0f, 0.0f, 800.0f), false, false);
	}
	if (User_Pawn_Character->WallDir == 1 && User_Pawn_Character->WallTouch == true) // Right Wall Dir Jump
	{
		User_Pawn_Character->LaunchCharacter(GetPawn()->GetActorRightVector() * -500.0f + FVector(0.0f,0.0f,800.0f), false, false);
		User_Pawn_Character->AddActorLocalRotation(FRotator(0.0f, -75.0f, 0.0f));
		UE_LOG(LogTemp, Error, TEXT("Wall_Jump_On"));
	}
	if (User_Pawn_Character->WallDir == -1 && User_Pawn_Character->WallTouch == true) // Left Wall Dir Jump
	{
		User_Pawn_Character->LaunchCharacter(GetPawn()->GetActorRightVector() * 500.0f + FVector(0.0f, 0.0f, 800.0f), false, false);
		User_Pawn_Character->AddActorLocalRotation(FRotator(0.0f, 75.0f, 0.0f));

	}
}
void AUser_Player_Controller::User_Aiming_Press()
{
	UE_LOG(LogTemp, Error, TEXT("User_Player_Pressed"));
	Player_Aim_Now = true;
}
void AUser_Player_Controller::User_Aiming_Release()
{
	Player_Aim_Now = false;
}
void AUser_Player_Controller::User_Aiming_Function(float DeltaTime)
{
	if (Player_Aim_Now)
	{
		User_Pawn_Character->SpringArm->TargetArmLength = FMath::FInterpTo(User_Pawn_Character->SpringArm->TargetArmLength,150.0f,DeltaTime,10.0f);
		User_Pawn_Character->Camera->SetRelativeLocation(FMath::VInterpTo(User_Pawn_Character->Camera->GetRelativeLocation(), FVector(0.0f, 50.0f, 50.0f),DeltaTime,10.0f));
	}
	else
	{
		User_Pawn_Character->SpringArm->TargetArmLength = FMath::FInterpTo(User_Pawn_Character->SpringArm->TargetArmLength, 400.0f, DeltaTime, 5.0f);
		User_Pawn_Character->Camera->SetRelativeLocation(FMath::VInterpTo(User_Pawn_Character->Camera->GetRelativeLocation(), FVector(0.0f, 0.0f, 0.0f), DeltaTime, 10.0f));
	}
}
void AUser_Player_Controller::User_Launch_Rope_Press()
{
	// Call Method Link
	User_Pawn_Character->Character_Play_RopeAction();
	UE_LOG(LogTemp, Error, TEXT("User_Shoot_Activated"));

}
void AUser_Player_Controller::User_Restart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}