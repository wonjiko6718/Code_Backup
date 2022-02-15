// Copyright Epic Games, Inc. All Rights Reserved.

#include "Code_SampleGameMode.h"
#include "User_Character.h"
#include "User_Player_Controller.h"
#include "UObject/ConstructorHelpers.h"

ACode_SampleGameMode::ACode_SampleGameMode()
{
	// set default pawn class to our Blueprinted character
	//Class'/Script/Code_Sample.User_Character'
	//WidgetBlueprint'/Game/Widget_BP/MainMenu.MainMenu'
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Code_Sample.User_Character"));
	//Link MainMenu Widget
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidget_CF(TEXT("/Game/Widget_BP/MainMenu.MainMenu_C"));
	if (MainMenuWidget_CF.Succeeded())
	{
		HudWidgetClass = MainMenuWidget_CF.Class;
	}
	//Setting Default Class
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerControllerClass = AUser_Player_Controller::StaticClass();
}
void ACode_SampleGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (HudWidgetClass != nullptr && GetWorld()->GetName() == TEXT("MainMenu"))
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}