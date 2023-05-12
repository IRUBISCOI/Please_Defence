// Fill out your copyright notice in the Description page of Project Settings.


#include "Pocket_Spawner.h"
#include "Components/SphereComponent.h"
#include "Gold_Pocket.h"

// Sets default values
APocket_Spawner::APocket_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;


	SphereComponent->InitSphereRadius(10.0f);
}

// Called when the game starts or when spawned
void APocket_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	AGold_Pocket* pocket = GetWorld()->SpawnActor<AGold_Pocket>(AGold_Pocket::StaticClass(), GetActorTransform());
}

// Called every frame
void APocket_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APocket_Spawner::NewPocketSpawn()
{
	
}

void APocket_Spawner::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(NewPocketSpawning, this, &APocket_Spawner::NewPocketSpawn, 2.0f, false);
}

