// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Particles/ParticleSystemComponent.h"
#include "ST_BuffTower.generated.h"

/**
 * 
 */

USTRUCT(Atomic , BlueprintType)
struct PLEASE_DEFENCE_API FST_BuffTower:public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float DamageVariance;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float DelayVariance;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UParticleSystem* Particle;



};
