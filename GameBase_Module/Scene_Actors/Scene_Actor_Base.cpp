// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene_Actor_Base.h"

// Sets default values
AScene_Actor_Base::AScene_Actor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScene_Actor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScene_Actor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

