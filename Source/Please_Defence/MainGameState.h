// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameState.generated.h"

USTRUCT(Atomic, BlueprintType)
struct Fmaindt
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
};


/**
 * 
 */
UCLASS()
class PLEASE_DEFENCE_API AMainGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadDT();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpawner> BP_Spawner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	Fmaindt dt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterCount;

	UFUNCTION()
		void SpawnTimeCondition(float value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DelayTime = 2;

};
