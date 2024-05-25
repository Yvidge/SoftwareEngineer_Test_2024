// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_2.generated.h"

class UDA_1;

UENUM()
enum class ETestEnum : uint8
{
	value_true,
	value_false,
	value_n
};

/**
 * 
 */
UCLASS()
class REDRUINS_TT_2024_API UDA_2 : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	ETestEnum TestEnum;

	UPROPERTY(EditDefaultsOnly, meta=(EditCondition="TestEnum==ETestEnum::value_true", EditConditionHides))
	TObjectPtr<UDA_1> DA1;
};
