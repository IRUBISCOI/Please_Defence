// Fill out your copyright notice in the Description page of Project Settings.


#include "Please_Defence_PlayerState.h"
#include "Weapon.h"


void APlease_Defence_PlayerState::Set_Weapon_Damage_Implementation(int Damage)
{
	Weapon_Damage = Damage;
	weapon->Damage = Damage;
}

int APlease_Defence_PlayerState::Get_Weapon_Damage()
{
	return Weapon_Damage;
}

void APlease_Defence_PlayerState::Set_Gold_Implementation(int newGold)
{ 
	Gold = newGold;
}

