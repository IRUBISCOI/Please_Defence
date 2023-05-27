// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MonsterMovePath.h"

#include "Monster.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UWidgetComponent;


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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* Widget_Front;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* Widget_Back;

public:
	// BP¿¡¼­ call
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterMove();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterStop();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MonsterDispatcher();


	UFUNCTION(BlueprintCallable)
		void MoveToSpline(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurveTrack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonCurStageHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonCurStageSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MonTypeHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonTypeSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MonTypeMoney = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MonTypeCurHP;

	class AMonsterMovePath* MonPath;
	class AEndPoint* EndPoint;
	class AMainGameState* MainState;
	class ASpawner* Spawner;

	class ASpawner* SpawnerA;
	class ASpawner* SpawnerB;
	class ASpawner* SpawnerC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ASpawner> TypeA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ASpawner> TypeB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ASpawner> TypeC;

	UFUNCTION()
	void OnCapsuleBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	FVector SplineLoc;
	FRotator SplineRot;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void SufferDamage(float damage, AController* EventInstigator);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void DieAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void Gain_Gold(AController* target);

	UFUNCTION(BlueprintImplementableEvent)
	void SetHpBar();

};
