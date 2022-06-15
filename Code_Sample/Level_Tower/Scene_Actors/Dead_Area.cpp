// Fill out your copyright notice in the Description page of Project Settings.


#include "Dead_Area.h"
#include "User_Character.h"

// Sets default values
ADead_Area::ADead_Area()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Dead_Zone = CreateDefaultSubobject<UBoxComponent>(TEXT("DEAD_ZONE_BOX"));
	Dead_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DEAD_ZONE_PARTICLE"));
	
	RootComponent = Dead_Zone;

	Dead_Particle->SetAutoActivate(false);

	Dead_Zone->SetGenerateOverlapEvents(true);
	Dead_Cause = TEXT("FLLLLLLLLYYYYYYYYYYYY");
}

// Called when the game starts or when spawned
void ADead_Area::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADead_Area::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ADead_Area::NotifyActorBeginOverlap(AActor* Other)
{
	if (Other->ActorHasTag(TEXT("Destroy")))
	{
		UE_LOG(LogTemp, Error, TEXT("Destroy_Area_On"));
		Other->Destroy();
	}
	if (Other->IsA<AUser_Character>())
	{
		FVector TargetTrans = Other->GetActorLocation();
		Dead_Particle->SetWorldLocation(TargetTrans);

		UE_LOG(LogTemp, Error, TEXT("Destroy_Area_On_Char"));
		AUser_Character* Dead_User = Cast<AUser_Character>(Other);
		Dead_User->Player_Dead_Cause = Dead_Cause;
		if (Dead_Particle != nullptr)
		{
			Dead_Particle->Activate(true);
		}
		Dead_User->User_Die();
	}
}