// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMovePath.h"

#include "Components/SplineComponent.h"

// Sets default values
AMonsterMovePath::AMonsterMovePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;

	//LocationPath = Spline->GetSplineLength();

}

// Called when the game starts or when spawned
void AMonsterMovePath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterMovePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

