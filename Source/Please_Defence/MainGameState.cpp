// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"
#include "Spawner.h"

#include "Kismet/GameplayStatics.h"


// Called when the game starts or when spawned
void AMainGameState::BeginPlay()
{
	Super::BeginPlay();


	LoadDT();

	MonsterCount = dt.MaxCount;

	AActor* spawner = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawner::StaticClass());


}

// Called every frame
void AMainGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnTimeCondition(DeltaTime);

}

void AMainGameState::SpawnTimeCondition(float value)
{
	CurrentTime += value;

	if (CurrentTime >= DelayTime)
	{

	}

}



