// Fill out your copyright notice in the Description page of Project Settings.


#include "Spring_Board.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpring_Board::ASpring_Board()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring_Board_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SPRING_BOARD_MESH"));
	Spring_Board_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("SPRING_BOARD_BOX"));

	RootComponent = Spring_Board_Mesh;
	Spring_Board_Box->SetupAttachment(RootComponent);
	Spring_Board_Mesh->SetGenerateOverlapEvents(false);
	//StaticMesh'/Game/WaterMill/Meshes/Buildings/Platform5.Platform5'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Spring_Board_Mesh_OF(TEXT("/Game/WaterMill/Meshes/Buildings/Platform5.Platform5"));
	if (Spring_Board_Mesh_OF.Succeeded())
	{
		Spring_Board_Mesh->SetStaticMesh(Spring_Board_Mesh_OF.Object);
	}

	Spring_Board_Box->SetGenerateOverlapEvents(true);
	Spring_Activate = false;

	Board_Up_Speed = 0.3f;
	Board_Up_Angle = -75.0f;

}

// Called when the game starts or when spawned
void ASpring_Board::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpring_Board::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Board_Rotation = Spring_Board_Mesh->GetRelativeRotation();
	if (Spring_Activate)
	{
		Spring_Board_Mesh->SetRelativeRotation(FMath::Lerp(FQuat(Board_Rotation), FQuat(FRotator(Board_Up_Angle, Board_Rotation.Yaw, 0.0f)),Board_Up_Speed));	}
}
void ASpring_Board::NotifyActorBeginOverlap(AActor* Other)
{
	if (Other->ActorHasTag(TEXT("User_Character")))
	{
		UE_LOG(LogTemp, Error, TEXT("Spring Detect"));
		Spring_Activate = true;
	}

}
