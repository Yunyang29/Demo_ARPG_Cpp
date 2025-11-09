#include "Characters/Character_Enemy.h"

#include "DebugHelper.h"
#include "FunctionLibrary_Base.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/CombatComponent_Enemy.h"
#include "Components/UI/UIComponent_Enemy.h"
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameModes/GameMode_Base.h"
#include "Widgets/Widget_Base.h"

class AGameMode_Base;

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

	LeftHandBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandBoxComp"));
	LeftHandBox->SetupAttachment(GetMesh());
	LeftHandBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

	RightHandBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandBoxComp"));
	RightHandBox->SetupAttachment(GetMesh());
	RightHandBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
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
	if (UWidget_Base* HealthWidget = Cast<UWidget_Base>(HealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void ACharacter_Enemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

void ACharacter_Enemy::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandBoxSocket))
	{
		LeftHandBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, LeftHandBoxSocket);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandBoxSocket))
	{
		RightHandBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandBoxSocket);
	}
}

void ACharacter_Enemy::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UFunctionLibrary_Base::IsTargetPawnHostile(this, HitPawn))
		{
			CombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void ACharacter_Enemy::InitEnemyStartUpData()
{
	if (StartUpData.IsNull())
		return;

	int32 AbilityApplyLevel = 1;
	if (AGameMode_Base* BaseGameMode = GetWorld()->GetAuthGameMode<AGameMode_Base>())
	{
		switch (BaseGameMode->GetCurrentGameDifficulty())
		{
		case EGameDifficulty::Easy:
			AbilityApplyLevel = 1;
			break;
		case EGameDifficulty::Normal:
			AbilityApplyLevel = 2;
			break;
		case EGameDifficulty::Hard:
			AbilityApplyLevel = 3;
			break;
		case EGameDifficulty::VeryHard:
			AbilityApplyLevel = 4;
			break;
		default:
			break;
		}
	}
	// ?
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this,AbilityApplyLevel]()
			{
				if (UDataAsset_StartUp* LoadedData = StartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(ASC, AbilityApplyLevel);
				}
			}
		)
	);
}
