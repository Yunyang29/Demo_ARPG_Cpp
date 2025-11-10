#include "GameInstance_Base.h"

TSoftObjectPtr<UWorld> UGameInstance_Base::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid()) continue;

		if (GameLevelSet.LevelTag == InTag)
		{
			return GameLevelSet.Level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}
