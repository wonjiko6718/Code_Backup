// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "User_Player_Controller.generated.h"

/**
 * 
 */
UCLASS()
class CODE_SAMPLE_API AUser_Player_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	AUser_Player_Controller();
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void SetupInputComponent() override;

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	UPROPERTY(VisibleAnywhere)
		float PlayerSpeed;
private:
	UPROPERTY(VisibleAnywhere)
		ACharacter* User_Pawn_Character;
		
};
