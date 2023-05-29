// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterMovePath.h"
#include "EndPoint.h"
#include "Spawner.h"
#include "MainGameState.h"
#include "Please_DefenceCharacter.h"
#include "Please_Defence_PlayerState.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"

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

	Widget_Front = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_Front"));
	Widget_Front->SetupAttachment(SkeletalMesh);
	Widget_Back = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_Back"));
	Widget_Back->SetupAttachment(SkeletalMesh);

	Capsule->SetCollisionObjectType(ECollisionChannel::ECC_OverlapAll_Deprecated);

	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass
	(TEXT("WidgetBlueprint'/Game/_Dev/Monster_KHJ/MonHPbar.MonHPbar_C'"));
	if (WidgetClass.Succeeded())
	{
		Widget_Front->SetWidgetClass(WidgetClass.Class);
		Widget_Back->SetWidgetClass(WidgetClass.Class);
	}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	AActor* spline = UGameplayStatics::GetActorOfClass(GetWorld(), AMonsterMovePath::StaticClass());
	AActor* endpoint = UGameplayStatics::GetActorOfClass(GetWorld(), AEndPoint::StaticClass());
	AActor* mainstate = UGameplayStatics::GetActorOfClass(GetWorld(), AMainGameState::StaticClass());
	AActor* spawner = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawner::StaticClass());

	AActor* spawnerA = UGameplayStatics::GetActorOfClass(GetWorld(), TypeA);
	AActor* spawnerB = UGameplayStatics::GetActorOfClass(GetWorld(), TypeB);
	AActor* spawnerC = UGameplayStatics::GetActorOfClass(GetWorld(), TypeC);


	MonPath = Cast<AMonsterMovePath>(spline);
	EndPoint = Cast<AEndPoint>(endpoint);
	MainState = Cast<AMainGameState>(mainstate);
	Spawner = Cast<ASpawner>(spawner);

	SpawnerA = Cast<ASpawner>(spawnerA);
	SpawnerB = Cast<ASpawner>(spawnerB);
	SpawnerC = Cast<ASpawner>(spawnerC);

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnCapsuleBeginOverlap);

	MonCurStageHP = MainState->dt.MaxHP;
	MonCurStageSpeed = MainState->dt.Speed;

	MonsterDispatcher();

	MonTypeCurHP = MonTypeHP;

	Capsule->SetVisibility(false);
	SkeletalMesh->SetVisibility(false);
	Widget_Front->SetVisibility(false);
	Widget_Back->SetVisibility(false);

	if (spline == nullptr)
	{
	}
	if (endpoint == nullptr)
	{
	}
	if (spawner == nullptr)
	{
	}
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AMonster::MoveToSpline(float Value)
{
	if (MonPath != nullptr)
	{
		Capsule->SetVisibility(true);
		SkeletalMesh->SetVisibility(true);
		Widget_Front->SetVisibility(true);
		Widget_Back->SetVisibility(true);

		float Loc = MonPath->Spline->GetSplineLength();
		float lerp = UKismetMathLibrary::Lerp(0, Loc, Value);

		SplineLoc = MonPath->Spline->GetLocationAtDistanceAlongSpline(lerp, ESplineCoordinateSpace::World);
		SplineRot = MonPath->Spline->GetRotationAtDistanceAlongSpline(lerp, ESplineCoordinateSpace::World);
		
		SetActorLocationAndRotation(SplineLoc, SplineRot);
		SetActorScale3D(FVector(1));
	}
}

void AMonster::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == EndPoint)
	{
		Capsule->SetVisibility(false);
		SkeletalMesh->SetVisibility(false);
		Widget_Front->SetVisibility(false);
		Widget_Back->SetVisibility(false);

		FVector Loc0 = MonPath->Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);

		this->SetActorLocation(Loc0);

		this->MonsterStop();

		MainState->RemovetoMyList(this);
	}
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange,
		FString::Printf(TEXT("TakeDamage Damage = %f "), DamageAmount));

	AController* Player = Cast<AController>(EventInstigator);

	if (Player)
	{
		SufferDamage(DamageAmount, EventInstigator);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange,
			FString::Printf(TEXT("Player NULL")));
	}
	return 0.0f;
}

void AMonster::SufferDamage(float damage, AController* EventInstigator)
{
	MonTypeCurHP -= damage;
	MonTypeCurHP = FMath::Clamp((float)MonTypeCurHP, 0.0f, (float)MonTypeHP);

	SetHpBar();

	if (!MonTypeCurHP)
	{
		Capsule->SetVisibility(false);
		SkeletalMesh->SetVisibility(false);
		Widget_Front->SetVisibility(false);
		Widget_Back->SetVisibility(false);

		FVector Loc0 = MonPath->Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);

		this->SetActorLocation(Loc0);

		this->MonsterStop();

		MainState->RemovetoMyList(this);

		DieAnimation();
		Gain_Gold(EventInstigator);

	}
}




