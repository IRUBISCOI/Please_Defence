// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Please_Defence_PlayerState.h"

// Sets default values for this component's properties
UBuffComponent::UBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;





	// ...
}


// Called when the game starts
void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuffComponent::Buff_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld() , Particle , Location , FRotator::ZeroRotator , FVector(1.f , 1.f , 1.f) , false , EPSCPoolMethod::None , true);
	APlease_Defence_PlayerState* Ps= Cast<APlease_Defence_PlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	if (Ps)
	{
		float DefaultDamage= Ps->Get_Weapon_Damage();
		Ps->Set_Weapon_Damage(DefaultDamage + Damage);
		//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Magenta , FString::Printf(TEXT("DefaultDamage = %f") , DefaultDamage));
		//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Magenta , FString::Printf(TEXT("DefaultDamage + Damage = %f") , DefaultDamage + Damage));
	}
}

void UBuffComponent::SettingBuff_Implementation(float BeforeDamage , float BeforeDelay , UParticleSystem* BeforeParticle , FVector BeforeLocation)
{
	Damage=BeforeDamage;
	Delay=BeforeDelay;
	Particle=BeforeParticle;
	Location=BeforeLocation;
}

