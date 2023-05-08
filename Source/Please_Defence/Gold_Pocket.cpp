// Fill out your copyright notice in the Description page of Project Settings.


#include "Gold_Pocket.h"
#include "Please_DefenceCharacter.h"

// Sets default values
AGold_Pocket::AGold_Pocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGold_Pocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGold_Pocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AGold_Pocket::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("TakeDamage Damage=%f EventInstigator=%s"), DamageAmount, *EventInstigator->GetName()));

	CurHP = CurHP - DamageAmount;
	CurHP = FMath::Clamp((float)CurHP, 0.0f, (float)MaxHP);

	CalculateHp(CurHP, MaxHP);

	return 0.0f;
}

