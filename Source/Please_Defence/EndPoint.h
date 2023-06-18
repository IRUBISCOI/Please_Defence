// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPoint.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class PLEASE_DEFENCE_API AEndPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	class APlease_Defence_PlayerState* PlayerState;
	class AMonster* Monster;
	class AMainGameState* MainGameState;
	class AMonsterMovePath* MonPath;

	FTimerHandle timerhandle;

	UFUNCTION()
	void DelayTime();

	UFUNCTION()
	void OnMeshBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
