// Copyright Epic Games, Inc. All Rights Reserved.

#include "Code_SampleGameMode.h"
#include "User_Character.h"
#include "UObject/ConstructorHelpers.h"

ACode_SampleGameMode::ACode_SampleGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
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
	//Link CrossHair Widget
	//WidgetBlueprint'/Game/Widget_BP/InGame_User.InGame_User'
	ConstructorHelpers::FClassFinder<UUserWidget> CrossHairWidget_CF(TEXT("/Game/Widget_BP/InGame_User.InGame_User_C"));
	if (CrossHairWidget_CF.Succeeded())
	{
		CrossHairWidgetClass = CrossHairWidget_CF.Class;
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
	User_Character_Controller = Cast<AUser_Player_Controller>(GetWorld()->GetFirstPlayerController());
	if (HudWidgetClass != nullptr && GetWorld()->GetName() == TEXT("MainMenu"))
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
	else
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), CrossHairWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
void ACode_SampleGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (User_Character_Controller->Player_Aim_Now)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		//	UE_LOG(LogTemp, Warning, TEXT("Character Aiming Detected"));		
	}
	else
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

}