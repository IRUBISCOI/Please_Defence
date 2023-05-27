// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Containers/Array.h" 
#include "queue"

#define MAXCOUNT 100;

#include "Spawner.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FTypeCount
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int SpawnCount;
};

class UStaticMeshComponent;
class UArrowComponent;


UCLASS()
class PLEASE_DEFENCE_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StartPoint;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMonster> MonsterFactory;

	float StartDelay_Cur = 0;
	float StartDelay_Del = 1;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SpawnerDispatcher();
	
	UPROPERTY()
		class AMainGameState* mainState;

	UPROPERTY(EditAnywhere)
	AMonster* spawnMon;

	UFUNCTION(BlueprintCallable)
		void SetStart();

	UPROPERTY(BlueprintReadWrite)
		float CurSpawnCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Totalcount = MAXCOUNT;

	std::queue<AMonster*> mys;

	UPROPERTY(BlueprintReadOnly)
	bool bSetPathLocation = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTypeCount SetCount;
	

	FTimerHandle timerHandle;

	UFUNCTION()
		void TTTT();

	

private:
	void DelayTime();
	

};
