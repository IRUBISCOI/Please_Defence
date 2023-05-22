// Fill out your copyright notice in the Description page of Project Settings.


#include "SummonTower.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/DataTable.h"
#include "Engine/AssetManager.h"

// Sets default values
ASummonTower::ASummonTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_StaticMeshComponent(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
	BeforeSummonZone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeforeSummonZone"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BeforeSummonZone(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
	static ConstructorHelpers::FObjectFinder<UMaterial>M_BeforeSummonZone(TEXT("Material'/Game/_Dev/Defencer_KHY/M_DrawBeforeSummon.M_DrawBeforeSummon'"));

	Tower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Tower(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
	Box = CreateDefaultSubobject< UBoxComponent>(TEXT("Box"));
	if (SM_StaticMeshComponent.Succeeded()&& SM_BeforeSummonZone.Succeeded()&& SM_Tower.Succeeded())
	{
		StaticMeshCom->SetStaticMesh(SM_StaticMeshComponent.Object);
		BeforeSummonZone->SetStaticMesh(SM_BeforeSummonZone.Object);
		Tower->SetStaticMesh(SM_Tower.Object);
		Tower->SetCollisionProfileName(FName(TEXT("NoCollision")));
		Box->SetCollisionProfileName(FName(TEXT("OverlapAll")));
		Box->SetWorldScale3D(FVector(10,10,2.5));
		BeforeSummonZone->SetRelativeLocation(FVector(0,0,100));

	}

}

// Called when the game starts or when spawned
void ASummonTower::BeginPlay()
{
	Super::BeginPlay();
	BeforeSummonZone->SetVisibility(false);
	
}

// Called every frame
void ASummonTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASummonTower::Summon()
{
	if (BeforeSummonZone->IsVisible())
	{
		int RandomInteger = FMath::RandRange(0,3);

		switch (RandomInteger)
		{
		case 0:
			int SecondRandomInteger = FMath::RandRange(0 , 3);
			UDataTable* DataTable = LoadObject<UDataTable>(nullptr , TEXT("DataTable'/Game/_Dev/Defencer_KHY/DataTable/DT_NormalTower.DT_NormalTower'"));
			FName  RandomIntegerName = FName(*FString::FromInt(SecondRandomInteger));
			NormalTower = DataTable->FindRow<ST_NormalTower>(RandomIntegerName , FString(""));
			break;
		case 1:
			int SecondRandomInteger = FMath::RandRange(0 , 3);
			UDataTable * DataTable = LoadObject<UDataTable>(nullptr , TEXT("DataTable'/Game/_Dev/Defencer_KHY/DataTable/DT_SkillTower.DT_SkillTower'"));
			FName  RandomIntegerName = FName(*FString::FromInt(SecondRandomInteger));
			SkillTower = DataTable->FindRow<ST_SkillTower>(RandomIntegerName , FString(""));

			break;
		case 2:
			int SecondRandomInteger = FMath::RandRange(0 , 4);
			UDataTable * DataTable = LoadObject<UDataTable>(nullptr , TEXT("DataTable'/Game/_Dev/Defencer_KHY/DataTable/DT_BuffTower.DT_BuffTower'"));
			FName  RandomIntegerName = FName(*FString::FromInt(SecondRandomInteger));
			BuffTower = DataTable->FindRow<ST_BuffTower>(RandomIntegerName , FString(""));
			
			break;
			
		default:
			break;
		}

	}
}

