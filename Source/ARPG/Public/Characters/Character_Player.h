#pragma once

#include "CoreMinimal.h"
#include "Characters/Character_Base.h"
#include "GameplayTagContainer.h"
#include "Character_Player.generated.h"

class UUIComponent_Player;
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
class UCombatComponent_Player;
struct FInputActionValue;

UCLASS()
class ARPG_API ACharacter_Player : public ACharacter_Base
{
	GENERATED_BODY()

public:
	ACharacter_Player();
	virtual UCombatComponent_Base* GetCombatComponent() const override;
	virtual UUIComponent_Base*     GetUIComponent() const override;
	virtual UUIComponent_Player*   GetPlayerUIComponent() const override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|Camera", meta = (ALLowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|Camera", meta = (ALLowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|Combat", meta = (ALLowPrivateAccess = "true"))
	UCombatComponent_Player* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|UI", meta = (ALLowPrivateAccess = "true"))
	UUIComponent_Player* UIComponent;

#pragma endregion

#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "A_My|CharacterData", meta = (ALLowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigData;

	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_PickUpStoneStarted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

#pragma endregion

public:
	FORCEINLINE UCombatComponent_Player* GetPlayerCombatComp() const
	{
		return CombatComponent;
	}
};
