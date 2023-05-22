// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMath.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEASE_DEFENCE_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		UParticleSystem* Particle;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		UParticleSystemComponent* SettingEmitter;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		float Distance;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		float Range;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		float Damage;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		float Delay;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		FVector Location;


	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		AActor* Target;
		

	FTimerHandle TimerHandle;
	


public:

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
		void ActiveSkill();

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
		void SettingSkill(float BeforeRange , float BeforeDamage, float BeforeDelay, float BeforeDistance, UParticleSystem* BeforePaticle,FVector BeforeLocation, AActor* BeforeAActor);

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
		void ClearEmitter();

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
		void SetTarget(AActor * BeforeTarget);
		
};
