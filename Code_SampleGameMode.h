// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Code_SampleGameMode.generated.h"

UCLASS(minimalapi)
class ACode_SampleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACode_SampleGameMode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HudWidgetClass;
	UPROPERTY(EditAnywhere)
		class UUserWidget* CurrentWidget;

};



