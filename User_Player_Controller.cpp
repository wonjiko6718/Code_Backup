// Fill out your copyright notice in the Description page of Project Settings.


#include "User_Player_Controller.h"
#include "User_Character.h"

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
	User_Pawn_Character = Cast<ACharacter>(GetPawn());
	UE_LOG(LogTemp, Error, TEXT("User_Player_Controller Posses : %s"), *User_Pawn_Character->GetName());

}
void AUser_Player_Controller::SetupInputComponent() // SetupInput
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("UpDown"), this, &AUser_Player_Controller::UpDown);
	InputComponent->BindAxis(TEXT("LeftRight"), this, &AUser_Player_Controller::LeftRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AUser_Player_Controller::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &AUser_Player_Controller::Turn);


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