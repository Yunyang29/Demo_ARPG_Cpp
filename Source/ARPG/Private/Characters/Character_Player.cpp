#include "Characters/Character_Player.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTags_Base.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/CombatComponent_Player.h"
#include "Components/Input/InputComponent_Base.h"
#include "Components/UI/UIComponent_Player.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "DataAssets/StartUp/DataAsset_StartUp_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameModes/GameMode_Base.h"

/// @brief 玩家角色类
void ACharacter_Player::BeginPlay()
{
	Super::BeginPlay();
}

/// @brief 角色被控制器占有时调用
/// @param NewController
void ACharacter_Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 根据startup数据资产赋予能力
	if (!StartUpData.IsNull())
	{
		if (UDataAsset_StartUp* LoadedData = StartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;
			if (AGameMode_Base* BaseGameMode = GetWorld()->GetAuthGameMode<AGameMode_Base>())
			{
				switch (BaseGameMode->GetCurrentGameDifficulty())
				{
				case EGameDifficulty::Easy:
					AbilityApplyLevel = 4;
					Debug::Print(TEXT("Current Difficulty: Easy"));
					break;
				case EGameDifficulty::Normal:
					AbilityApplyLevel = 3;
					Debug::Print(TEXT("Current Difficulty: Normal"));
					break;
				case EGameDifficulty::Hard:
					AbilityApplyLevel = 2;
					Debug::Print(TEXT("Current Difficulty: Hard"));
					break;
				case EGameDifficulty::VeryHard:
					AbilityApplyLevel = 1;
					Debug::Print(TEXT("Current Difficulty: VeryHard"));
					break;
				default:
					break;
				}
			}

			LoadedData->GiveToAbilitySystemComponent(ASC, AbilityApplyLevel);
		}
	}
}

UCombatComponent_Base* ACharacter_Player::GetCombatComponent() const
{
	return CombatComponent;
}

UUIComponent_Base* ACharacter_Player::GetUIComponent() const
{
	return UIComponent;
}

UUIComponent_Player* ACharacter_Player::GetPlayerUIComponent() const
{
	return UIComponent;
}

/// @brief 构造函数
ACharacter_Player::ACharacter_Player()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CombatComponent = CreateDefaultSubobject<UCombatComponent_Player>(TEXT("CombatComp"));
	UIComponent = CreateDefaultSubobject<UUIComponent_Player>(TEXT("UIComp"));
}

/// @brief 设置玩家输入组件
/// @param PlayerInputComponent
void ACharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	/* 输入配置数据检查 */
	checkf(InputConfigData, TEXT("Forget to assign a valid data asset as input config"));

	/* 获取本地玩家和输入子系统 */
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);

	/* 添加输入映射上下文 */
	Subsystem->AddMappingContext(InputConfigData->DefaultMappingContext, 0);

	/* 绑定具体输入动作 */
	UInputComponent_Base* InputComp = CastChecked<UInputComponent_Base>(PlayerInputComponent);
	InputComp->BindNativeInputAction(InputConfigData, GameplayTags_Base::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	InputComp->BindNativeInputAction(InputConfigData, GameplayTags_Base::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	InputComp->BindNativeInputAction(InputConfigData, GameplayTags_Base::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	InputComp->BindNativeInputAction(InputConfigData, GameplayTags_Base::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	InputComp->BindNativeInputAction(InputConfigData, GameplayTags_Base::InputTag_PickUp_Stone, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStoneStarted);

	InputComp->BindAbilityInputAction(InputConfigData, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

/// @brief 玩家输入移动事件
/// @param InputActionValue
void ACharacter_Player::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

/// @brief 玩家输入视角事件
/// @param InputActionValue
void ACharacter_Player::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACharacter_Player::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void ACharacter_Player::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData EventData;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? GameplayTags_Base::Player_Event_SwitchTarget_Right : GameplayTags_Base::Player_Event_SwitchTarget_Left,
		EventData
	);
}

void ACharacter_Player::Input_PickUpStoneStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		GameplayTags_Base::Player_Event_ConsumeStone,
		Data
	);
}

/// @brief 玩家输入能力按下事件
/// @param InInputTag
void ACharacter_Player::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	ASC->OnAbilityInputPressed(InInputTag);
}

/// @brief 玩家输入能力释放事件
/// @param InInputTag
void ACharacter_Player::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	ASC->OnAbilityInputReleased(InInputTag);
}
