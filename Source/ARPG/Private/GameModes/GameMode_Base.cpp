#include "GameModes/GameMode_Base.h"

AGameMode_Base::AGameMode_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
