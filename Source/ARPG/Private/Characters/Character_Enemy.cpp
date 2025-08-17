#include "Characters/Character_Enemy.h"

#include "Components/WidgetComponent.h"
#include "Components/Combat/CombatComponent_Enemy.h"
#include "Components/UI/UIComponent_Enemy.h"
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/Widget_Base.h"

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

	CombatComponent = CreateDefaultSubobject<UCombatComponent_Enemy>("CombatComp");
	UIComponent = CreateDefaultSubobject<UUIComponent_Enemy>(TEXT("UIComp"));
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	HealthWidgetComponent->SetupAttachment(GetMesh());
}

UCombatComponent_Base* ACharacter_Enemy::GetCombatComponent() const
{
	return CombatComponent;
}

UUIComponent_Base* ACharacter_Enemy::GetUIComponent() const
{
	return UIComponent;
}

UUIComponent_Enemy* ACharacter_Enemy::GetEnemyUIComponent() const
{
	return UIComponent;
}

void ACharacter_Enemy::BeginPlay()
{
	Super::BeginPlay();
	if(UWidget_Base* HealthWidget = Cast<UWidget_Base>(HealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
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
				}
			}
		)
	);
}
