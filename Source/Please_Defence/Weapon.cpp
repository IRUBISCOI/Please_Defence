// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SM_KA47_X.SM_KA47_X'"));

	if (mesh.Succeeded())
	{
		Mesh->SetStaticMesh(mesh.Object);
	}

	//
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->SetSimulatePhysics(false);

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	ConstructorHelpers::FObjectFinder<USoundBase> audio(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion01.Explosion01'"));
	if (audio.Succeeded())
	{
		Audio->SetSound(audio.Object);
	}

	Audio->bAutoActivate = false;
	Audio->SetupAttachment(RootComponent);

	//FireEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("FireEffect"));


	//ConstructorHelpers::FObjectFinder<UParticleSystem> fire_effect(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	//if (fire_effect.Succeeded())
	//{
	//	FireEffect = fire_effect.Object;
	//}

	//FireEffect->bAutoActivate = false;
	//FireEffect->SetupAttachment(RootComponent);

	Ammo = 30;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	//AttachToComponent(OwnChar->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon"));
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Shoot()
{
	APlayerController* shooter = GetWorld()->GetFirstPlayerController();
	if (shooter == OwnChar->GetController())
	{
		FVector forward = shooter->PlayerCameraManager->GetActorForwardVector();

		FVector start = (forward * 350) + shooter->PlayerCameraManager->GetCameraLocation();
		FVector end = (forward * 5000) + shooter->PlayerCameraManager->GetCameraLocation();

		FHitResult result;

		bool isHit = GetWorld()->LineTraceSingleByObjectType(result, start, end, ECollisionChannel::ECC_WorldDynamic);

		DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false, 1.0f);

		if (result.Actor != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *result.GetActor()->GetName()));
		}

		if (isHit)
		{
			ACharacter* HitChar = Cast<ACharacter>(result.GetActor());
			if (HitChar)
			{
				UGameplayStatics::ApplyDamage(HitChar, Damage, OwnChar->GetController(), this, UDamageType::StaticClass());
			}
		}
	}
}

void AWeapon::PlaySound()
{
	Audio->Play();
}

void AWeapon::Fire_Effect()
{
	ParticleSystem = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"), nullptr, LOAD_None, nullptr);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Mesh->GetSocketLocation("Muzzle"), Mesh->GetSocketRotation("Muzzle"), FVector(0.2f, 0.2f, 0.2f)); //FVector(0.3f, 0.3f, 0.3f)
}

