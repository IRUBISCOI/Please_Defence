// Fill out your copyright notice in the Description page of Project Settings.


#include "Gold_Pocket.h"
#include "Please_DefenceCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Please_Defence_PlayerState.h"

// Sets default values
AGold_Pocket::AGold_Pocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGold_Pocket::BeginPlay()
{
	Super::BeginPlay();
	
}
/**/
void AGold_Pocket::Gain_Gold_Implementation(AController* target)
{
	APlease_Defence_PlayerState* ps = Cast<APlease_Defence_PlayerState>(target->GetPawn()->GetPlayerState());

	if (ps)
	{
		if (Owning_Gold)
		{
			ps->Set_Gold(ps->Get_Gold() + Owning_Gold);
		}
		else
		{
			ps->Set_Weapon_Damage(ps->Get_Weapon_Damage() + 1);
		}
	}
}

/*
void AGold_Pocket::Gain_Gold_Implementation(APlease_DefenceCharacter* target)
{
	target->Set_Gold(Owning_Gold);
}
*/
// Called every frame
void AGold_Pocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AGold_Pocket::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
	//	FString::Printf(TEXT("TakeDamage Damage=%f EventInstigator=%s"), DamageAmount, *EventInstigator->GetName()));
	
	//Gainer = Cast<APlease_DefenceCharacter>(EventInstigator->GetInstigator());
	Gainer = EventInstigator;

	AddDamage(DamageAmount);

	return 0.0f;
}

void AGold_Pocket::AddDamage(float Damage)
{
	CurHP = CurHP - Damage;
	CurHP = FMath::Clamp((float)CurHP, 0.0f, (float)MaxHP);

	if (!CurHP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Destroy!")));
		UParticleSystem* ParticleSystem = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"), nullptr, LOAD_None, nullptr);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation(), GetActorRotation(), FVector(1.f, 1.f, 1.f));
		Gain_Gold(Gainer);
		Destroy();
	}

	CalculateHp(CurHP, MaxHP);
}




