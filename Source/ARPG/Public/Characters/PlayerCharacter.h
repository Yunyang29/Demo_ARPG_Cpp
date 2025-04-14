// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MainCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
/**
 *
 */
UCLASS()
class ARPG_API APlayerCharacter : public AMainCharacter
{
	GENERATED_BODY() // 生成类

public:
	APlayerCharacter(); // 构造函数

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

#pragma endregion

#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "CharacterData", meta = (ALLowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigData;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

#pragma endregion
};
