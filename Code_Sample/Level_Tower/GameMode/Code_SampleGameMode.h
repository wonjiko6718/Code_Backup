// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_Base.h"
#include "Blueprint/UserWidget.h"
#include "User_Player_Controller.h"
#include "LevelSequence.h"
#include "Code_SampleGameMode.generated.h"

UCLASS(minimalapi)
class ACode_SampleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACode_SampleGameMode();
	void GameMode_GameOver();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString Player_Dead_Cause;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HudWidgetClass;
	UPROPERTY(EditAnywhere)
		class UUserWidget* CurrentWidget;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> CrossHairWidgetClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> GameOverWidgetClass;
	UPROPERTY(EditAnywhere)
		AUser_Player_Controller* User_Character_Controller;
	UPROPERTY(VisibleAnywhere)
		bool IsMainMenu;
	UPROPERTY(VisibleAnywhere)
		bool Game_Over;
};



