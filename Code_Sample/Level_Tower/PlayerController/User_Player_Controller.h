// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "User_Character.h"
#include "User_Player_Controller_Base.h"
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
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupInputComponent() override;

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void User_Jump();
	void User_Aiming_Press();
	void User_Aiming_Release();
	void User_Aiming_Function(float DeltaTime);
	void User_Launch_Rope_Press();
	void User_Restart();


	UPROPERTY(VisibleAnywhere)
		float PlayerSpeed;
	UPROPERTY(VisibleAnywhere)
		bool Player_Aim_Now;

private:
	UPROPERTY(VisibleAnywhere)
		AUser_Character* User_Pawn_Character;
		
};
