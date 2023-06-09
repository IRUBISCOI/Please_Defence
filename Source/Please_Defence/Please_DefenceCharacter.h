// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Please_DefenceCharacter.generated.h"

UCLASS(config=Game)
class APlease_DefenceCharacter : public ACharacter
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	APlease_DefenceCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	class AWeapon* weapon;
	class APlease_Defence_PlayerState* playerState;
	UAnimMontage* AnimMontage_Shoot;
	UAnimMontage* AnimMontage_Reload;
	UAnimMontage* AnimMontage_Construct;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleMode();

	UFUNCTION(BlueprintImplementableEvent)
	void Construstion();

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION(BlueprintCallable)
	void Shoot();
	UFUNCTION(BlueprintCallable)
	void Reload();

	float ControlPitch;
	UPROPERTY(BlueprintReadWrite)
	bool IsEquipWeapon = true;

public: 

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetControlPitch() const { return ControlPitch; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetIsEquipWeapon() const { return IsEquipWeapon; }
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	void ExTouch(FVector Location);
};

