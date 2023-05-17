// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MainGameState.h"
#include "Monster.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = Arrow;
	StartPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartPoint"));
	StartPoint->SetupAttachment(Arrow);
	StartPoint->SetRelativeRotation(FRotator(0,-90,90));
	StartPoint->SetRelativeScale3D(FVector(2));

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//AActor* state = UGameplayStatics::GetActorOfClass(GetWorld(), AMainGameState::StaticClass());

	mainState = Cast<AMainGameState>(GetWorld()->GetGameState());

	SpawnerDispatcher();

}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StartDelay_Cur += DeltaTime;

	if (StartDelay_Cur >= StartDelay_Del)
	{
		if (CurSpawnCount <= mainState->dt.MaxCount)
		{
			AddArray();

			StartDelay_Cur = 0;
		}
	}
}

void ASpawner::AddArray()
{
	int count = 0;

	if (count <= 99)
	{
		spawnMon = GetWorld()->SpawnActor<AMonster>(MonsterFactory, Arrow->GetRelativeLocation(), FRotator(0));

		MonArr[count] = spawnMon;

		CurSpawnCount += 1;

		count += 1;
	}

}



