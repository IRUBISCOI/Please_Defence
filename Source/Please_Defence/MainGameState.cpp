// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"
#include "Spawner.h"

#include "Kismet/GameplayStatics.h"


// Called when the game starts or when spawned
void AMainGameState::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Blue, TEXT("MainState Beginplay"));

	LoadDT();

	MonsterCount = dt.MaxCount;

	AActor* spawner = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawner::StaticClass());

	Spawner = Cast<ASpawner>(spawner);

	if (Spawner != nullptr)
	{
		Spawner->SpawnCount = MonsterCount;
	}
	
}

// Called every frame
void AMainGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMainGameState::SpawnTimeCondition(float value)
{

}

void AMainGameState::UpdateCount()
{
	MonsterCount -= 1;

	if (MonsterCount <= 0)
	{
		StageUp();
	}
	
}

void AMainGameState::StageUp()
{

	dt.Stage += 1;
	dt.MaxHP *= 1.25;
	dt.MaxCount *= 1.25;
	
	StageCount += 1;

	if (StageCount >= 2)
	{
		dt.Speed *= 1.25;
		StageCount = 0;
	}

	MonsterCount = dt.MaxCount;
	Spawner->SpawnCount = dt.MaxCount;

	StateDispatcher(dt.MaxHP, dt.MaxCount, dt.Speed);

	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Blue, TEXT("Stage Up"));
	
}




