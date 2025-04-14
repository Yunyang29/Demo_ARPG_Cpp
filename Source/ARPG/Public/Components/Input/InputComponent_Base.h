#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "InputComponent_Base.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UInputComponent_Base : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
};

template <class UserObject, typename CallbackFunc>
inline void UInputComponent_Base::BindNativeInputAction(
	const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag&           InInputTag,
	ETriggerEvent                 TriggerEvent,
	UserObject*                   ContextObject,
	CallbackFunc                  Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	if(UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}
