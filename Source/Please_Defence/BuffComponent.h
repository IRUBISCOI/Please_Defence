// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), Blueprintable ,meta=(BlueprintSpawnableComponent) )
class PLEASE_DEFENCE_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UParticleSystem* Particle;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Delay;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	FVector Location;


public:

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void Buff();

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void SettingBuff(float BeforeDamage, float BeforeDelay, UParticleSystem* BeforeParticle ,FVector BeforeLocation);


};
