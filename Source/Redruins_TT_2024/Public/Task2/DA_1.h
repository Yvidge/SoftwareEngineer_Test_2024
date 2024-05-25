// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_1.generated.h"

class UDA_2;

USTRUCT()
struct FTestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDA_2> DA2;

	UPROPERTY(EditDefaultsOnly)
	FText TestText;
};

/**
 * 
 */
UCLASS()
class REDRUINS_TT_2024_API UDA_1 : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FTestStruct TestStruct;
};
