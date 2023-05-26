// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Particles/ParticleSystemComponent.h"
#include "ST_SKillTower.generated.h"

/**
 * 
 */

USTRUCT(Atomic , BlueprintType)
struct PLEASE_DEFENCE_API FST_SKillTower: public FTableRowBase
{

public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Delay;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Distance;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UParticleSystem* Particle;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMesh* StaticMesh;





};
