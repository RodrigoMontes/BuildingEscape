// Rodrigo Montes 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
//#include "Gameframework/Actor.h"

//siempre el ultimo include!
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector PlayerViewPortLocation;
	FRotator PlayerViewPortRotation;
	APlayerController* PlayerController;
	FVector LineTraceEnd;	
	float Reach = 100.0f;	// que tan lejos se puede tomar las cosas (largo de manos)
	
};
