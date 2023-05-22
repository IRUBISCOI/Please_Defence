// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterMovePath.h"
#include "EndPoint.h"
#include "Spawner.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Actor.h"




// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(RootComp);
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Capsule);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SKeletalBase
	(TEXT("SkeletalMesh'/Game/_Dev/Monster_KHJ/Animation/Standing_Walk_Forward.Standing_Walk_Forward'"));
	if (SKeletalBase.Succeeded())
	{
		SkeletalMesh->SetSkeletalMesh(SKeletalBase.Object);
		SkeletalMesh->SetRelativeLocationAndRotation(FVector(0, 0, -40), FRotator(0, 90, 0));
		SkeletalMesh->SetRelativeScale3D(FVector(0.5f));
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance>WalkBase
	(TEXT("AnimBlueprint'/Game/_Dev/Monster_KHJ/Animation/WalkBase.WalkBase_C'"));
	if (WalkBase.Succeeded())
	{
		SkeletalMesh->SetAnimInstanceClass(WalkBase.Class);
	}

//	BP_spline = LoadObject<UClass>(NULL, TEXT("Blueprint'/Game/_Dev/Monster_KHJ/BP_Spline.BP_Spline_C'"), NULL, LOAD_None, NULL);
//	BP_endpoint = LoadObject<UClass>(NULL, TEXT("Blueprint'/Game/_Dev/Monster_KHJ/BP_EndPoint.BP_EndPoint_C'"), NULL, LOAD_None, NULL);

	Capsule->SetCollisionObjectType(ECollisionChannel::ECC_OverlapAll_Deprecated);

	
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, TEXT("Monster Beginplay"));

	AActor* spline = UGameplayStatics::GetActorOfClass(GetWorld(), AMonsterMovePath::StaticClass());
	AActor* endpoint = UGameplayStatics::GetActorOfClass(GetWorld(), AEndPoint::StaticClass());
	AActor* spawner = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawner::StaticClass());

	MonPath = Cast<AMonsterMovePath>(spline);
	EndPoint = Cast<AEndPoint>(endpoint);
	Spawner = Cast<ASpawner>(spawner);

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnCapsuleBeginOverlap);

	MonsterDispatcher();

	Capsule->SetVisibility(false);
	SkeletalMesh->SetVisibility(true);

	if (spline == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Magenta, FString::Printf(TEXT("spline Null")));
	}
	if (endpoint == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Magenta, FString::Printf(TEXT("endpoint Null")));
	}
	if (spawner == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Magenta, FString::Printf(TEXT("spawner Null")));
	}


}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StartDelayTime += DeltaTime;
	
}

void AMonster::MoveToSpline(float Value)
{
		if (MonPath != nullptr)
		{
			float Loc = MonPath->Spline->GetSplineLength();
			float lerp = UKismetMathLibrary::Lerp(0, Loc, Value);

			SplineLoc = MonPath->Spline->GetLocationAtDistanceAlongSpline(lerp, ESplineCoordinateSpace::World);
			SplineRot = MonPath->Spline->GetRotationAtDistanceAlongSpline(lerp, ESplineCoordinateSpace::World);

			SetActorLocationAndRotation(SplineLoc, SplineRot);
			SetActorScale3D(FVector(1));

			Capsule->SetVisibility(true);
			SkeletalMesh->SetVisibility(true);

			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("loc : %f"), Value));
		}
}

void AMonster::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == EndPoint)
	{
		Capsule->SetVisibility(false);
		SkeletalMesh->SetVisibility(true);

		FVector Loc35 = MonPath->Spline->GetLocationAtSplinePoint(35, ESplineCoordinateSpace::World);

		this->SetActorLocation(Loc35);

		this->MonsterStop();

		Spawner->moving.pop();
		Spawner->mys.push(this);
		
	}
}



