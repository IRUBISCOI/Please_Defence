// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gold_Pocket.generated.h"

UCLASS()
class PLEASE_DEFENCE_API AGold_Pocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGold_Pocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void CalculateHp(int CurHealthPoint, int MaxHealthPoint);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Gain_Gold(AController* target);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AController* Gainer;

	int CurHP = 1000;
	int MaxHP = 1000;

	UPROPERTY(BlueprintReadWrite)
	int Owning_Gold = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void AddDamage(float Damage);

};
