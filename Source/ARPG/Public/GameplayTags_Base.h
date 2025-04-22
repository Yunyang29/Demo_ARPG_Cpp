#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GameplayTags_Base
{
	/**Input Tags**/
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move); // 移动输入标签
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look); // 视角输入标签
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe); // 装备
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe); // 装备

	/**Player Tags**/
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unquip_Axe);
}
