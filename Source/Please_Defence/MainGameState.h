// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Containers/List.h"
#include <iostream>
#include <list>

#include "MainGameState.generated.h"

using namespace std;

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

USTRUCT(Atomic, BlueprintType)

struct FCount
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonACount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonBCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonCCount;
};

USTRUCT(Atomic, BlueprintType)

struct FReadMainDT
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MainStage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CorrectionValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FCount count;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	Fmaindt dt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FReadMainDT ReadMainDT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ASpawner> TypeA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ASpawner> TypeB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ASpawner> TypeC;

	UPROPERTY(BlueprintReadWrite)
		float MonsterCount;

	UPROPERTY(BlueprintReadWrite)
		float CurrentTime = 0;
	UPROPERTY(BlueprintReadWrite)
		float DelayTime = 2;
	UPROPERTY(BlueprintReadWrite)
		bool bSpawnTimeBoolean = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ASpawner* Spawner;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ASpawner* SpawnMonTypeA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ASpawner* SpawnMonTypeB;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ASpawner* SpawnMonTypeC;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StageUp();
	UPROPERTY(BlueprintReadOnly)
		int DTLowName = 1;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void MisstionStart();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void WidgetVisible();

	
	UFUNCTION()
	void RemovetoMyList(AMonster* Monster);

	list<AMonster*> MyList;
	
	

};
