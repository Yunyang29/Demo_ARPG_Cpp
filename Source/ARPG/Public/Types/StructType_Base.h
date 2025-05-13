#pragma once
#include "StructType_Base.generated.h"

class ULinkedAnimLayer_Player;

USTRUCT(BlueprintType)
struct FWeaponData_Player
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULinkedAnimLayer_Player> WeaponAnimLayerToLink;
};
