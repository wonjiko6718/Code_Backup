// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "User_Player_Controller.h"
#include "Code_SampleGameMode.generated.h"

UCLASS(minimalapi)
class ACode_SampleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACode_SampleGameMode();

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
		AUser_Player_Controller* User_Character_Controller;

};



