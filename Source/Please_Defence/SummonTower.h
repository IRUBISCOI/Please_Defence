// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BuffComponent.h"
#include "SkillComponent.h"
#include "ST_NormalTower.h"
#include "ST_SKillTower.h"
#include "ST_BuffTower.h"
#include "Monster.h"
#include "ST_SKillTower.h"
#include "Misc/OutputDeviceNull.h"
#include "Components/CapsuleComponent.h"
#include "SummonTower.generated.h"



class BP_Missile;

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
	float FirstDistance=15000.0f;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	AMonster* Target;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray<AMonster*>TargetArr;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	int MyType =10;



	FTimerHandle TimerHandle;

	

	UPROPERTY(EditAnywhere , Category = "Blueprint")
	AActor* Missile;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray <AActor*> MissileArray;


	
	

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	FST_NormalTower DT_NormalTower ;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	int ArrayNum;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray<AActor*>OverlappintActors;

	//UPROPERTY(EditAnywhere , BlueprintReadWrite)
	//TArray<class BP_Monster*>MonsterArray;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	FST_NormalTower NormalTower;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	FST_SKillTower SkillTower;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	FST_BuffTower BuffTower;

public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class UBuffComponent* BuffCom;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class USkillComponent* SkillCom; 

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UActorComponent* SkillActorCom;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UActorComponent* BuffActorCom;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	bool IsOn=false;
	bool IsSummon=false;


	float AttackTimeAcc=0;

	FName MonName;

	int ArrCount=0;

	bool Cooldown = true;


	
	
public:
	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void Summon();

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void ExSetAttackArray();

	UFUNCTION()
	void Call_MissileArrayReset();
	//블루 프린트에서 만든 함수 콜
	
	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void ExAttack();


	UFUNCTION()
	void Call_SetNormalTarget();


	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void SelectTower();

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void ExSettingTarget();


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void FindNewTarget();
};
