// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Task4Character.generated.h"

class UTask4Object;

UCLASS()
class REDRUINS_TT_2024_API ATask4Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATask4Character();

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "Class"))
	UObject* CreateSubobject(TSubclassOf<UTask4Object> Class); 

	UFUNCTION(BlueprintCallable)
	void CleanupSubobject();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	UPROPERTY(Replicated, BlueprintReadWrite)
	UTask4Object* ReplicatedSubobject;
};
