// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"
#include "Spawner.h"
#include "Monster.h"

#include "Kismet/GameplayStatics.h"




// Called when the game starts or when spawned
void AMainGameState::BeginPlay()
{
	Super::BeginPlay();
	LoadDT();

	MonsterCount = ReadMainDT.count.MonACount + ReadMainDT.count.MonBCount + ReadMainDT.count.MonCCount;

	GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Blue, FString::Printf(TEXT("AAAA : %f"), ReadMainDT.count.MonACount));
	GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Red, FString::Printf(TEXT("BBBB : %f"), ReadMainDT.count.MonBCount));
	GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Green, FString::Printf(TEXT("CCCC : %f"), ReadMainDT.count.MonCCount));

	MonsterCount = dt.MaxCount;

	AActor* spawner = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawner::StaticClass());

	AActor* spawnerA = UGameplayStatics::GetActorOfClass(GetWorld(), TypeA);
	AActor* spawnerB = UGameplayStatics::GetActorOfClass(GetWorld(), TypeB);
	AActor* spawnerC = UGameplayStatics::GetActorOfClass(GetWorld(), TypeC);

	Spawner = Cast<ASpawner>(spawner);
	SpawnMonTypeA = Cast<ASpawner>(spawnerA);
	SpawnMonTypeB = Cast<ASpawner>(spawnerB);
	SpawnMonTypeC = Cast<ASpawner>(spawnerC);

	if (Spawner != nullptr)
	{
		Spawner->SetCount.SpawnCount = MonsterCount;
	}
	if (SpawnMonTypeA != nullptr)
	{
		SpawnMonTypeA->SetCount.SpawnCount = ReadMainDT.count.MonACount;
	}
	if (SpawnMonTypeB != nullptr)
	{
		SpawnMonTypeB->SetCount.SpawnCount = ReadMainDT.count.MonBCount;
	}
	if (SpawnMonTypeC != nullptr)
	{
		SpawnMonTypeC->SetCount.SpawnCount = ReadMainDT.count.MonCCount;
	}


}

// Called every frame
void AMainGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainGameState::StageUp_Implementation()
{
	if (DTLowName >= 30)
	{
		DTLowName = 0;
	}

	DTLowName += 1;

}

void AMainGameState::RemovetoMyList(AMonster* Monster)
{
	MyList.remove(Monster);

	Spawner->mys.push(Monster);
	
	// remove시 MyList의 size 체크 하는 부분
	if (MyList.size() <= 0)
	{
		Spawner->bSetPathLocation = false;
		WidgetVisible();
		StageUp();
		
	}
}

	
