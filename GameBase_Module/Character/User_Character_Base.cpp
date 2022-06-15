// Fill out your copyright notice in the Description page of Project Settings.


#include "User_Character_Base.h"

// Sets default values
AUser_Character_Base::AUser_Character_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUser_Character_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUser_Character_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUser_Character_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

