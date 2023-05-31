// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	

	// ...
	
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void USkillComponent::SettingSkill_Implementation(float BeforeRange , float BeforeDamage , float BeforeDelay , float BeforeDistance , UParticleSystem* BeforePaticle , FVector BeforeLocation)
{
	Range= BeforeRange;
	Distance=BeforeDistance;
	Particle=BeforePaticle;
	Damage=BeforeDamage;
	Delay=BeforeDelay;
	//Target=BeforeAActor;
}

void USkillComponent::ActiveSkill_Implementation()
{
	if (IsValid(Target))
	{
		Location = Target->GetActorLocation();
		if (Particle!=nullptr)
		{
			FTimerManager& TimerManager = GWorld->GetTimerManager();
			if (IsValid(SettingEmitter))
			{
				SettingEmitter->SetWorldLocation(Location);
				SettingEmitter->Activate(true);
			}
			else
			{

				SettingEmitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld() , Particle , Location , FRotator::ZeroRotator , FVector(1.f , 1.f , 1.f) , true , EPSCPoolMethod::None , true);
			}
			UGameplayStatics::ApplyDamage(Target , Damage, nullptr , nullptr , UDamageType::StaticClass());
			TimerManager.SetTimer(TimerHandle ,this,&USkillComponent::ClearEmitter_Implementation ,Delay-0.1f ,false );
			//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Magenta , FString::Printf(TEXT("Damage: %f") , Damage));
			//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Emitter:%s"), *(SettingEmitter->GetName())));


		}
		
	}

}


void USkillComponent::ClearEmitter_Implementation()
{
	FTimerManager& TimerManager = GWorld->GetTimerManager();
	if (IsValid(SettingEmitter))
	{ 
		//SettingEmitter->DestroyComponent();
		//SettingEmitter=nullptr;
		SettingEmitter->SetActive(false);
		TimerManager.ClearTimer(TimerHandle);
		//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("ClearEmitter") ));
	}
}

void USkillComponent::SetTarget_Implementation(AActor* BeforeTarget)
{
	Target= BeforeTarget;
}



