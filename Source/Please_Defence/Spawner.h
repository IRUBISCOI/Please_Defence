// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Containers/Array.h" 
#include "queue"

#define MAXCOUNT 100;

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
	float StartDelay_Del = 1;

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
	// Totalcount == 1000¸¶¸®
	int Totalcount = MAXCOUNT;

	std::queue<AMonster*> mys;
	std::queue<AMonster*> moving;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSetPathLocation = false;

	UPROPERTY(EditAnywhere)
		float SpawnCount;
	

	FTimerHandle timerHandle;

	UFUNCTION()
		void TTTT();

private:
	void DelayTime();
	

};
