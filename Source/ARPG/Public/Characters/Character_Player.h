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
	GENERATED_BODY() // 生成类

public:
	ACharacter_Player(); // 构造函数

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override; // 设置玩家输入组件
	virtual void BeginPlay() override; // 开始播放
	virtual void PossessedBy(AController* NewController) override; // 被控制

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Camera", meta = (ALLowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Camera", meta = (ALLowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Combat", meta = (ALLowPrivateAccess = "true"))
	UCombatComponent_Player* CombatComponent;
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
