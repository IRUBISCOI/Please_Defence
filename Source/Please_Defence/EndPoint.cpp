// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPoint.h"

#include "MainGameState.h"
#include "Please_Defence_PlayerState.h"
#include "Monster.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AEndPoint::AEndPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Mesh->SetupAttachment(Root);

	//Mesh->SetCollisionObjectType(ECollisionChannel::ECC_OverlapAll_Deprecated);
	
}

// Called when the game starts or when spawned
void AEndPoint::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AEndPoint::OnMeshBeginOverlap);

	DelayTime();
}

// Called every frame
void AEndPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndPoint::DelayTime()
{
	AActor* maingamestate = UGameplayStatics::GetActorOfClass(GetWorld(), AMainGameState::StaticClass());
	AActor* spline = UGameplayStatics::GetActorOfClass(GetWorld(), AMonsterMovePath::StaticClass());

	MainGameState = Cast<AMainGameState>(maingamestate);
	MonPath = Cast<AMonsterMovePath>(spline);

	if ((MainGameState == NULL)||(MonPath == NULL))
	{
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.SetTimer(timerhandle, this, &AEndPoint::DelayTime, 0.1f, false);
	}
}

void AEndPoint::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Monster = Cast<AMonster>(OtherActor);
	if (Monster)
	{
		Monster->SkeletalMesh->SetVisibility(false);
		Monster->Widget_Front->SetVisibility(false);
		Monster->Widget_Back->SetVisibility(false);
		
		Monster->Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		FVector Loc0 = MonPath->Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		
		Monster->SetActorLocation(Loc0);
		
		Monster->MonsterStop();
		
		MainGameState->RemovetoMyList(Monster);

		MainGameState->Decrease();
	}
}


