// Fill out your copyright notice in the Description page of Project Settings.


#include "User_Player_Controller.h"

AUser_Player_Controller::AUser_Player_Controller() // Constructor
{
	// Possess to Pawn
	AController::Possess(GetPawn());

	//Properties Setting
	PlayerSpeed = 1.0f;

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
	
}
void AUser_Player_Controller::User_Aiming_Press()
{
	User_Pawn_Character->bUseControllerRotationYaw = true;
	User_Pawn_Character->Camera->SetRelativeLocation(FVector(290.0f,30.0f,75.0f));
}
void AUser_Player_Controller::User_Aiming_Release()
{
	User_Pawn_Character->bUseControllerRotationYaw = false;
	User_Pawn_Character->Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}