#include "DataAssets/Input/DataAsset_InputConfig.h"

/// 通过游戏标签查找对应的输入动作
/// @param InInputTag 
/// @return 
UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for(const FARPGInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if(InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
