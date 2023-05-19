// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Containers/Array.h" 
#include "queue"

#include "Spawner.generated.h"


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

	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TSubclassOf<class AMonster> MonsterFactory;

	float StartDelay_Cur = 0;
	float StartDelay_Del = 5;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SpawnerDispatcher();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMainGameState* mainState;

	UPROPERTY(EditAnywhere)
	AMonster* spawnMon;

	UFUNCTION(BlueprintCallable)
		void SetStart();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurSpawnCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int count = 0;

	std::queue<AMonster*> mys;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSetPathLocation = false;

	UPROPERTY()
		float SpawnCount;
	
	FTimerHandle timerHandle;

private:
	void DelayTime();

};
