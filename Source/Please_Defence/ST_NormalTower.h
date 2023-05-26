// Fill out your copyright notice in the Description page of Project Settings.



#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ST_NormalTower.generated.h"



/**
 * 
 */

USTRUCT(Atomic , BlueprintType)
struct PLEASE_DEFENCE_API FST_NormalTower:public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()


	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Delay;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float AttackDistacne;



};
