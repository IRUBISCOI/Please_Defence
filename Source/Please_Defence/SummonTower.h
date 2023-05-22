// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BuffComponent.h"
#include "SkillComponent.h"
#include "Monster.h"
#include "SummonTower.generated.h"


UStruct ST_NormalTower;

UCLASS()
class PLEASE_DEFENCE_API ASummonTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASummonTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshCom;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMeshComponent* BeforeSummonZone;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMeshComponent* Tower;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	FName tag;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float FiestDistance;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	AMonster* Target;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	int MyType ;

	//UPROPERTY(EditAnywhere , BlueprintReadWrite)
	//TArray<class BP_Missile*>MissileArray;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStruct ST_NormalTower * DT_NormalTower ;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	int ArrayNum;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray<AActor*>OverlappintActors;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray<class BP_Monster*>MonsterArray;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class ST_NormalTower* NormalTower;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class ST_SkillTower* SkillTower;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class ST_BuffTower* BuffTower;

	
public:
	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void Summon();
	

};
