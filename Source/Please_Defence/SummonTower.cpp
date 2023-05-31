// Fill out your copyright notice in the Description page of Project Settings.


#include "SummonTower.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/DataTable.h"
#include "Engine/AssetManager.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"


// Sets default values
void ExAttack_Implementation();
ASummonTower::ASummonTower()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_StaticMeshComponent(TEXT("StaticMesh'/Game/Meshes/GroupOfBox.GroupOfBox'"));
	BeforeSummonZone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeforeSummonZone"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BeforeSummonZone(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
	static ConstructorHelpers::FObjectFinder<UMaterial>M_BeforeSummonZone(TEXT("Material'/Game/_Dev/Defencer_KHY/M_DrawBeforeSummon.M_DrawBeforeSummon'"));
	RootComponent = StaticMeshCom;

	Tower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower"));
	Box = CreateDefaultSubobject< UBoxComponent>(TEXT("Box"));
	
	if (SM_StaticMeshComponent.Succeeded() || SM_BeforeSummonZone.Succeeded())
	{
		StaticMeshCom->SetStaticMesh(SM_StaticMeshComponent.Object);
		BeforeSummonZone->SetStaticMesh(SM_BeforeSummonZone.Object);
		Tower->SetCollisionProfileName(FName(TEXT("NoCollision")));

		BeforeSummonZone->SetCollisionProfileName(FName(TEXT("NoCollision")));
		BeforeSummonZone->AttachToComponent(StaticMeshCom , FAttachmentTransformRules::KeepRelativeTransform);
		BeforeSummonZone->SetRelativeLocation(FVector(GetActorLocation().X , GetActorLocation().Y , GetActorLocation().Z + 150));
		Tower->AttachToComponent(BeforeSummonZone , FAttachmentTransformRules::KeepWorldTransform);
		Box->AttachToComponent(StaticMeshCom , FAttachmentTransformRules::KeepWorldTransform);
		Box->SetCollisionProfileName(FName(TEXT("OverlapAll")));
		
		Tower->SetRelativeLocation(FVector(0,0,0));
		Tower->SetWorldScale3D(FVector(0.5 , 0.5 , 0.5));
		BeforeSummonZone->SetMaterial(0 , M_BeforeSummonZone.Object);
	}
	Box->SetRelativeLocation(FVector(0,0,0));
	Box->SetWorldScale3D(FVector(10 ,10 ,2.5f));
	SkillCom=CreateDefaultSubobject<USkillComponent>(TEXT("SkillCom"));
	BuffCom =CreateDefaultSubobject<UBuffComponent>(TEXT("BuffCom"));

	Box->OnComponentBeginOverlap.AddDynamic(this , &ASummonTower::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this , &ASummonTower::OnOverlapEnd);

	
}

// Called when the game starts or when spawned
void ASummonTower::BeginPlay()
{
	Super::BeginPlay();
	BeforeSummonZone->SetVisibility(false);
	
	
}

// Called every frame
void ASummonTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetArr.Num()>0)
	{
		AttackTimeAcc += DeltaTime;
		switch (MyType)
		{
		case 0:
		{
			float AttackInterval=0.5;
			if (AttackTimeAcc >= AttackInterval)
			{
				// 공격력으로 공격
				if (Target->MonCurStageHP>=0)
				{
					ExAttack();
				}

				// 다음 공격을 위해 시간누적값 초기화
				AttackTimeAcc = 0;
			}
			break;
		}
		case 1:
		{
			float AttackInterval=0.5;
			if (AttackTimeAcc >= AttackInterval)
			{
				// 공격력으로 공격
				if (Target->MonCurStageHP >= 0)
				{
					SkillCom->ActiveSkill();
				}

				// 다음 공격을 위해 시간누적값 초기화
				AttackTimeAcc = 0;
			}
			break;
		}
		
		}
		
	}
	else
	{
		Target=nullptr;
		FindNewTarget();
	}
	//if (IsValid(Target))
	//{
	//	if (Target->MonTypeHP <= 0)
	//	{
	//		Target=nullptr;
	//		FirstDistance=15000.0f;
	//		
	//		ExSettingTarget();
	//	}
	//}
	

}

void ASummonTower::Call_MissileArrayReset()
{
	FOutputDeviceNull Ar;
	CallFunctionByNameWithArguments(TEXT("MissileArrayReset"),Ar,nullptr,true);
}

void ASummonTower::Call_SetNormalTarget()
{
	FOutputDeviceNull Ar;
	CallFunctionByNameWithArguments(TEXT("SetNormalTarget") , Ar , nullptr , true);
}

void ASummonTower::OnOverlapBegin(UPrimitiveComponent* OverlappedComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Monster"))
	{ 
		if (MyType == 0 || MyType == 1)
		{
			AMonster* OverlapMon= Cast<AMonster>(OtherActor);
			if (OverlapMon->Capsule == Cast <UCapsuleComponent> (OtherComp))
			{
				TargetArr.Add(OverlapMon);
				MonName=*OverlapMon->GetName();
				if (IsValid(Target))
				{

				}
				else
				{
					Target= OverlapMon;
					//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::White , FString::Printf(TEXT("OnOverlapBegin and TargetOn")));

					switch (MyType)
					{
					case 0:
						{
						Call_SetNormalTarget();
						//FTimerManager& TimerManager = GWorld->GetTimerManager();
						//FName ArrayName="Die"; 
						//ArrayName = OtherActor->Tags[0];
						//TimerManager.SetTimer(TimerHandle , this , &ASummonTower::ExAttack , 0.5f , true);
						
						}
						break;
					case 1:
						{
						SkillCom->SetTarget(Target);
						SkillCom->ClearEmitter();
						//SkillCom->ActiveSkill();
						//FName ArrayName = "Die";
						//ArrayName = OtherActor->Tags[0];
						//FTimerManager& TimerManager = GWorld->GetTimerManager();
						//TimerManager.SetTimer(TimerHandle , SkillCom , &USkillComponent::ActiveSkill, SkillCom ->Delay, true);
						
						}
						break;
					}
				}
			}
		}
	}
}

void ASummonTower::OnOverlapEnd(UPrimitiveComponent* OverlappedComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex)
{
		if (MyType == 0 || MyType == 1)
		{
			if (AMonster* OverlapMon = Cast<AMonster>(OtherActor))
			{

					
				TargetArr.Remove(OverlapMon);
				if (!IsValid(Target))
				{
					//TargetArr.Remove(OverlapMon);
					FindNewTarget();
					switch (MyType)
					{
					
						case 0:
						{
							Call_SetNormalTarget();
							
							//FTimerManager& TimerManager = GWorld->GetTimerManager();
							//TimerManager.ClearTimer(TimerHandle);
						
						}
						break;
						case 1:
						{
							SkillCom->SetTarget(Target);
							
							//FTimerManager& TimerManager = GWorld->GetTimerManager();
							//TimerManager.ClearTimer(TimerHandle);
							
							//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::White , FString::Printf(TEXT("TargetLost")));
						}
						break;
						
						
						default:
							break;
						
					}
				}
				//else
				//{
				//	TargetArr.Remove(OverlapMon);
				//	FindNewTarget();
				//}
					
				
			}
		}
}

					//if (TargetArr.Remove(OverlapMon))
					//{
					//	for ( AMonster* var : TargetArr)
					//	{
					//		if (FVector::Distance(StaticMeshCom->GetComponentLocation() , var->GetActorLocation()) < FirstDistance)
					//		{
					//			//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::White , FString::Printf(TEXT("OnOverlapEnd")));
					//			FirstDistance= FVector::Distance(StaticMeshCom->GetComponentLocation() , var->GetActorLocation());
					//			Target= var;
					//			
					//		}
					//	}
					//	////GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Target:%s") , *Target->GetName()));
					//	ExSettingTarget();
					//	FirstDistance=15000.0f;
					//}
					//else
					//{
					//	FirstDistance=15000.0f;
					//	Target=nullptr;
					//	switch (MyType)
					//	{
					//
					//	case 0:
					//	{
					//		Call_SetNormalTarget();
					//		//FTimerManager& TimerManager = GWorld->GetTimerManager();
					//		//TimerManager.ClearTimer(TimerHandle);
					//
					//	}
					//	break;
					//	case 1:
					//	{
					//		SkillCom->SetTarget(Target);
					//		//FTimerManager& TimerManager = GWorld->GetTimerManager();
					//		//TimerManager.ClearTimer(TimerHandle);
					//		
					//		//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::White , FString::Printf(TEXT("TargetLost")));
					//	}
					//	break;
					//
					//
					//	default:
					//		break;
					//	}
					//
					//}
				
				
				

			
	




void ASummonTower::FindNewTarget_Implementation()
{

	Target=nullptr;
	float NearDistance=15000.0f;
	for (AMonster* var : TargetArr)
	{
		if (var->MonCurStageHP >= 0)
		{
			continue;
		}
		float Distance= FVector::Distance(StaticMeshCom->GetComponentLocation() , var->GetActorLocation());
		if (Distance < NearDistance)
		{
			NearDistance= Distance;
			Target=var;
		}

		//if (FVector::Distance(StaticMeshCom->GetComponentLocation() , var->GetActorLocation()) < FirstDistance)
		//{
		//	//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::White , FString::Printf(TEXT("OnOverlapEnd")));
		//	FirstDistance = FVector::Distance(StaticMeshCom->GetComponentLocation() , var->GetActorLocation());
		//	Target = var;
		//
		//}
	}

}





void ASummonTower::ExAttack_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Magenta, FString::Printf(TEXT("Attack")));
	if (IsValid(Target))
	{
		if (Target->MonCurStageHP > 0)
		{
			if (ArrayNum >= 10)
			{
				ArrayNum=0;
				Call_MissileArrayReset();

			}
			else
			{
				Call_MissileArrayReset();
			}
		}
	}
}

void ASummonTower::ExSetAttackArray_Implementation()
{

	for (int i=0;i<10;i++)
	{ 
		UObject* cls = StaticLoadObject(UObject::StaticClass() , nullptr , TEXT("Blueprint'/Game/_Dev/Defencer_KHY/BP_Missile.BP_Missile'"));
		UBlueprint* bp = Cast<UBlueprint>(cls);
		TSubclassOf<class UObject> blockBP = (UClass*)bp->GeneratedClass;
		Missile= GetWorld()->SpawnActor<AActor>(blockBP , Tower->GetComponentTransform());
		//Missile->FindComponentByClass(UStaticMeshComponent* )
		//Missile->GetComponentsByTag(UStaticMeshComponent* Cube,FName"asd")
		MissileArray.Add(Missile);
		//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Array")));
	}
	
	
}

void ASummonTower::Summon_Implementation()
{
	if (ActorHasTag("Tower"))
	{
		
		
	
		if (BeforeSummonZone->IsVisible())
		{

			int RandomInteger = 1;
			//int RandomInteger = FMath::RandRange(0,2);
			//RandomInteger = 1;
			MyType= RandomInteger;
			//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Damage:%d") , MyType));
			switch (RandomInteger)
			{
				case 0:
				{
					//int ZeroRandomInteger = 1;
					UDataTable* ZDataTable = LoadObject<UDataTable>(nullptr , TEXT("DataTable'/Game/_Dev/Defencer_KHY/DataTable/DT_ExNormalTower.DT_ExNormalTower'"));
					FName  ZeroRandomIntegerName = "";
					int ZeroRandomInteger = FMath::RandRange(0 , 2);
					ZeroRandomIntegerName = FName(*FString::FromInt(ZeroRandomInteger));
					FST_NormalTower *ExNormalTower;

					ExNormalTower = ZDataTable->FindRow<FST_NormalTower>(ZeroRandomIntegerName , FString("NormalTowerError"));
					//NormalTower = *ZDataTable->FindRow<FST_NormalTower>(ZeroRandomIntegerName , FString("NormalTowerError"));
					if (IsValid(ExNormalTower->StaticMesh))
					{
						Tower->SetStaticMesh(ExNormalTower->StaticMesh);
						NormalTower.AttackDistacne= ExNormalTower->AttackDistacne;
						NormalTower.Damage= ExNormalTower->Damage;
						NormalTower.Delay= ExNormalTower->Delay;
						////GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Damage:%f") , NormalTower.Damage));
						Tags[0] = "MakeTower";
						
						SelectTower();
					}
				}

				break;
				case 1:
				{
					//int FirstRandomInteger = 0;
					UDataTable* FDataTable = LoadObject<UDataTable>(nullptr , TEXT("DataTable'/Game/_Dev/Defencer_KHY/DataTable/DT_ExSkillTower.DT_ExSkillTower'"));
					FName  FirstRandomIntegerName = "";
					FST_SKillTower* ExSkillTower;
					int FirstRandomInteger = FMath::RandRange(0 , 2);
					FirstRandomInteger = 1;
					FirstRandomIntegerName = FName(*FString::FromInt(FirstRandomInteger));
					ExSkillTower = FDataTable->FindRow<FST_SKillTower>(FirstRandomIntegerName , FString("SkillTowerError"));
					//SkillTower = *FDataTable->FindRow<FST_SKillTower>(FirstRandomIntegerName , FString("SkillTowerError"));

					//SkillTower.Damage=ExSkillTower->Damage;
					//SkillTower.Delay=ExSkillTower->Delay;
					//SkillTower.Distance =ExSkillTower->Distance;

					////GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Damage:%s") , SkillTower.Damage));
					////GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Delay:%s") , SkillTower.Delay));
					////GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Dis:%s") , SkillTower.Distance));
					if (IsValid(ExSkillTower->StaticMesh))
					{ 
						Tower->SetStaticMesh(ExSkillTower->StaticMesh);
						BeforeSummonZone->SetVisibility(false);
						SkillTower.Damage=ExSkillTower->Damage;
						SkillTower.Delay=ExSkillTower->Delay;
						SkillTower.Distance =ExSkillTower->Distance;
						SkillTower.Particle =ExSkillTower->Particle;
						//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Tags:%f") , SkillTower.Damage));


					
						Tags[0] = "MakeTower";
						SelectTower();
						////GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Tags:%s") , *this->Tags[0].ToString()));
						////GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Tags:%f") , ExSkillTower->Damage));
					}
				}
				break;
				case 2:
				{
					//int SecondRandomInteger = 0;
					FName  SecondRandomIntegerName = "";
					int SecondRandomInteger = FMath::RandRange(0 , 3);
					UDataTable* SDataTable = LoadObject<UDataTable>(nullptr , TEXT("DataTable'/Game/_Dev/Defencer_KHY/DataTable/DT_ExBuffTower.DT_ExBuffTower'"));
					SecondRandomIntegerName = FName(*FString::FromInt(SecondRandomInteger));
					FST_BuffTower* ExBuffTower;
					//BuffTower = *SDataTable->FindRow<FST_BuffTower>(SecondRandomIntegerName , FString("BuffTowerError"));
					ExBuffTower = SDataTable->FindRow<FST_BuffTower>(SecondRandomIntegerName , FString("BuffTowerError"));

					if (IsValid(ExBuffTower->StaticMesh))
					{
						Tower->SetStaticMesh(ExBuffTower->StaticMesh);
						BuffTower.Particle= ExBuffTower->Particle;
						BuffTower.DamageVariance= ExBuffTower->DamageVariance;
						BuffTower.DelayVariance= ExBuffTower->DelayVariance;
						//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("DamageVariance:%f") , BuffTower.DamageVariance));
					
						Tags[0] = "MakeTower";
						SelectTower();
					}


				}
				break;


			}

		}
	}
}

void ASummonTower::SelectTower_Implementation()
{
	switch (MyType)
	{
	case 0:
		{
			ExSetAttackArray();
			//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::White , FString::Printf(TEXT("NormalTower")));
		}
		break;
	case 1:
		{
			//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::White , FString::Printf(TEXT("SkillTower")));
			SkillCom->SettingSkill(SkillTower.Range, SkillTower.Damage, SkillTower.Delay, SkillTower.Distance, SkillTower.Particle, StaticMeshCom->GetComponentLocation());

		}
		break;
	case 2:
		{
			//GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::White , FString::Printf(TEXT("BuffTower")));
			BuffCom->SettingBuff(BuffTower.DamageVariance, BuffTower.DelayVariance, BuffTower.Particle, StaticMeshCom->GetComponentLocation());
			BuffCom->Buff();
		}
		break;
	}
}

void ASummonTower::ExSettingTarget_Implementation()
{
	
	switch (MyType)
	{
	case 0:
		{
		Call_SetNormalTarget();
		}
		break;
	case 1:
		{
		SkillCom->SetTarget(Target);
		////GEngine->AddOnScreenDebugMessage(-1 , 10 , FColor::Red , FString::Printf(TEXT("Target:%s") , *Target->GetName()));

		}
		break;
	
	
	}
}