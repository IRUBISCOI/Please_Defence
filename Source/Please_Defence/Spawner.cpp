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
	StartPoint->SetRelativeRotation(FRotator(0, -90, 90));
	StartPoint->SetRelativeScale3D(FVector(2));

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(timerHandle, this, &ASpawner::DelayTime, 0.1f, false);

	

	//AActor* state = UGameplayStatics::GetActorOfClass(GetWorld(), AMainGameState::StaticClass());

}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	StartDelay_Cur += DeltaTime;
//
//	if (StartDelay_Cur >= StartDelay_Del)
//	{
//		TTTT();
//
//		StartDelay_Cur = 0;
//	}

}

void ASpawner::SetStart()
{
	bSetPathLocation = true;

	FTimerManager& spawntimeManager = GetWorld()->GetTimerManager();
	spawntimeManager.SetTimer(timerHandle, this, &ASpawner::TTTT, 1.0f, true);
}

void ASpawner::DelayTime()
{
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::White, TEXT("Spawner Beginplay"));

	mainState = Cast<AMainGameState>(GetWorld()->GetGameState());

	SpawnerDispatcher();

	for (float i = 0; i <= Totalcount; i++)
	{

		spawnMon = GetWorld()->SpawnActor<AMonster>(MonsterFactory, Arrow->GetRelativeLocation(), FRotator(0));

		if (spawnMon != nullptr)
		{
			mys.push(spawnMon);
		}
	}
};

void ASpawner::TTTT()
{
	FTimerManager& spawntimeManager = GetWorld()->GetTimerManager();

	if (bSetPathLocation)
	{
		if (SpawnCount >= 0)
		{
			if (spawnMon != nullptr)
			{
				spawnMon = mys.front();
				moving.push(spawnMon);
				spawnMon->MonsterMove();
				mys.pop();
			}
			SpawnCount -= 1;
		}
		if(moving.size() <= 0)
		{
			bSetPathLocation = false;
			mainState->WidgetVisible();
			mainState->StageUp();
			spawntimeManager.ClearTimer(timerHandle);

			
		}
	}
}





