// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Please_Defence_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_DEFENCE_API APlease_Defence_PlayerState : public APlayerState
{
	GENERATED_BODY()


private:

	int Weapon_Damage = 30;

	int Gold = 0;


public:
	class AWeapon* weapon;
	UPROPERTY(BlueprintReadWrite)
	int Ammo = 30;

	void Set_Weapon(AWeapon* New_weapon) { weapon = New_weapon; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Set_Weapon_Damage(int Damage);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int Get_Weapon_Damage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Set_Gold(int newGold);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int Get_Gold() { return Gold; };

	UFUNCTION(BlueprintImplementableEvent)
	void UI_AmmoUpdate();

	UFUNCTION(BlueprintCallable)
	void Reload_Ammo() { Ammo = 30; UI_AmmoUpdate(); };
};
