#pragma once

UENUM()
enum class EConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class ESuccessType : uint8
{
	Succeed,
	Failed
};

UENUM()
enum class ECountdownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class ECountdownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	VeryHard
};
