// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Character_Base.h"
#include "GameplayTagContainer.h"
#include "Character_Player.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
class UCombatComponent_Player;
struct FInputActionValue;
/**
 *
 */
UCLASS()
class ARPG_API ACharacter_Player : public ACharacter_Base
{
	GENERATED_BODY()

public:
	ACharacter_Player();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Camera", meta = (ALLowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom; /// 相机弹簧臂

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Camera", meta = (ALLowPrivateAccess = "true"))
	UCameraComponent* FollowCamera; /// 相机组件

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Combat", meta = (ALLowPrivateAccess = "true"))
	UCombatComponent_Player* CombatComponent; /// 角色的战斗组件
#pragma endregion

#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "CharacterData", meta = (ALLowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigData;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

#pragma endregion

public:
	FORCEINLINE UCombatComponent_Player* GetPlayerCombatComp() const { return CombatComponent; }
};
