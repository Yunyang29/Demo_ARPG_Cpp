#include "Characters/Character_Enemy.h"
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelper.h"

ACharacter_Enemy::ACharacter_Enemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	CombatComponent = CreateDefaultSubobject<UCombatComponent_Enemy>("CharCombatComp");
}

void ACharacter_Enemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

void ACharacter_Enemy::InitEnemyStartUpData()
{
	if(StartUpData.IsNull())
	{
		return;
	}

	// ?
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if(UDataAsset_StartUp* LoadedData = StartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(ASC);

					Debug::Print(TEXT("Enemy Start Up Data Loaded"), FColor::Green);
				}
			}
		)
	);
}
