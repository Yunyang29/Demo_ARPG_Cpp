#include "Characters/Character_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/InputComponent_Base.h"
#include "GameplayTags_Base.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "..\..\Public\DataAssets\StartUp\DataAsset_StartUp_Player.h"
#include "Components/Combat/CombatComponent_Player.h"

#include "DebugHelper.h"


void ACharacter_Player::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print(TEXT("Working"));
}

void ACharacter_Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUp* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(CharacterASC);
		}
	}

	//if (CharacterAbilitySystemComponent && CharacterAttributeSet)
	//{
	//	const FString ASCText = FString::Printf(TEXT("Owner Actor: %p, AvatarActor: %s"), *CharacterAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *CharacterAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
	//	Debug::Print(TEXT("Ability system component valid. ") + ASCText, FColor::Green);
	//	Debug::Print(TEXT("Attribute system component valid. ") + ASCText, FColor::Green);
	//}
}

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

	CombatComponent = CreateDefaultSubobject<UCombatComponent_Player>(TEXT("CharCombatComp"));
}

void ACharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigData, TEXT("Forget to assign a valid data asset as input config"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigData->DefaultMappingContext, 0);

	UInputComponent_Base* MainInputComponent = CastChecked<UInputComponent_Base>(PlayerInputComponent);
	MainInputComponent->BindNativeInputAction(InputConfigData, GameplayTags_Base::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	MainInputComponent->BindNativeInputAction(InputConfigData, GameplayTags_Base::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
}

void ACharacter_Player::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator  MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

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
