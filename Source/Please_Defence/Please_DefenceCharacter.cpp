// Copyright Epic Games, Inc. All Rights Reserved.

#include "Please_DefenceCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon.h"
#include "Please_Defence_PlayerState.h"

//////////////////////////////////////////////////////////////////////////
// APlease_DefenceCharacter

void APlease_DefenceCharacter::BeginPlay()
{
	Super::BeginPlay();

	weapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), GetActorTransform());

	weapon->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon"));

	weapon->OwnChar = this;

	playerState = Cast<APlease_Defence_PlayerState>(GetPlayerState());
	
	if(playerState)
	{
		playerState->Set_Weapon(weapon);
	}

	//bUseControllerRotationYaw = false;
}

void APlease_DefenceCharacter::Tick(float DeltaTime)
{
	ControlPitch = GetControlRotation().Pitch;
}

APlease_DefenceCharacter::APlease_DefenceCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ConstructorHelpers::FObjectFinder<UAnimMontage> montage_Shoot(TEXT("AnimMontage'/Game/_Dev/Character_CSH/Character/Animation/Mixamo/Firing_Rifle_mixamo_com_Montage.Firing_Rifle_mixamo_com_Montage'"));
	ConstructorHelpers::FObjectFinder<UAnimMontage> montage_Reload(TEXT("AnimMontage'/Game/_Dev/Character_CSH/Character/Animation/Mixamo/Reloading_mixamo_com_Montage.Reloading_mixamo_com_Montage'"));
	ConstructorHelpers::FObjectFinder<UAnimMontage> montage_Construct(TEXT("AnimMontage'/Game/_Dev/Character_CSH/Character/Animation/Mixamo/Looking_mixamo_com_Montage.Looking_mixamo_com_Montage'"));
	
	AnimMontage_Shoot = montage_Shoot.Object;
	AnimMontage_Reload = montage_Reload.Object;
	AnimMontage_Construct = montage_Construct.Object;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	//static ConstructorHelpers::FObjectFinder<UBlueprint> BPObject(TEXT("Blueprint'/Game/_Dev/Character_CSH/Character/BP_Weapon.BP_Weapon'")); // PATH is blueprint object path
	//
	//if (BPObject.Object != NULL)
	//{
	//	BP_Weapon = (UClass*)BPObject.Object->GeneratedClass;
	//}

}

//////////////////////////////////////////////////////////////////////////
// Input

void APlease_DefenceCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlease_DefenceCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlease_DefenceCharacter::MoveRight);

	PlayerInputComponent->BindAction("Construct", IE_Released, this, &APlease_DefenceCharacter::ToggleMode);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlease_DefenceCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlease_DefenceCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &APlease_DefenceCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &APlease_DefenceCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &APlease_DefenceCharacter::OnResetVR);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlease_DefenceCharacter::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlease_DefenceCharacter::Reload);
}

void APlease_DefenceCharacter::ExTouch_Implementation(FVector Location)
{
	
	GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Magenta , FString::Printf(TEXT("loactionX = %f") , Location.X));
	GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Magenta , FString::Printf(TEXT("loactionY = %f") , Location.Y));
	GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Magenta , FString::Printf(TEXT("loactionZ = %f") , Location.Z));
}


void APlease_DefenceCharacter::OnResetVR()
{
	// If Please_Defence is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Please_Defence.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void APlease_DefenceCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		//Jump();
	ExTouch(Location);
}

void APlease_DefenceCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		//StopJumping();0
}

void APlease_DefenceCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlease_DefenceCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlease_DefenceCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlease_DefenceCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlease_DefenceCharacter::ToggleMode_Implementation()
{
	if (IsEquipWeapon)
	{
		IsEquipWeapon = false;
		weapon->Mesh->SetVisibility(false);
		bUseControllerRotationYaw = false;	
	}
	else
	{
		IsEquipWeapon = true;
		weapon->Mesh->SetVisibility(true);
		bUseControllerRotationYaw = true;
	}

}

void APlease_DefenceCharacter::Shoot()
{
	if (!IsEquipWeapon)
	{
		//Construstion();
		return;
	}

	int Ammo = playerState->Ammo;

	if (!Ammo)
	{
		return;
	}

	PlayAnimMontage(AnimMontage_Shoot);	
	weapon->PlaySound();
	weapon->Fire_Effect();
	weapon->Shoot();

	playerState->Ammo = Ammo - 1;
	playerState->UI_AmmoUpdate();
}

void APlease_DefenceCharacter::Reload()
{
	PlayAnimMontage(AnimMontage_Reload);
}
