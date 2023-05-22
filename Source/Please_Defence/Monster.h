// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MonsterMovePath.h"

#include "Monster.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USceneComponent;


UCLASS()
class PLEASE_DEFENCE_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// Base Component
	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Capsule;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;
	
	// 지워도 될듯
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_spline;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BP_endpoint;
	//

public:
	// BP에서 call
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterMove();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void MoveMove();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterStop();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterDispatcher();


	UFUNCTION(BlueprintCallable)
		void MoveToSpline(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurveTrack;
	UPROPERTY()
	class AMonsterMovePath* MonPath;

	UPROPERTY()
	class AEndPoint* EndPoint;

	UPROPERTY()
		class ASpawner* Spawner;

	UFUNCTION()
	void OnCapsuleBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterCurHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterCurSpeed = 0.1;

	FVector SplineLoc;
	FRotator SplineRot;

	float StartDelayTime = 0;

		


};
