// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainWeapon.generated.h"

class UBoxComponent;

UCLASS()
class ARPG_API AMainWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	UBoxComponent* WeaponCollisionBox;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};
