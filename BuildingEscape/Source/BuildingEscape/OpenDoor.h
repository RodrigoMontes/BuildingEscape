// Rodrigo Montes 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameframework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"

//siempre el ultimo include!
#include "OpenDoor.generated.h"

// define a new class to broadcast an event to a blueprint (to the owner)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)	// assign an event of the class FDoorEvent for broadcast to blueprints
		FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)	// assign an event of the class FDoorEvent for broadcast to blueprints
		FDoorEvent OnClose;

private:
	//UPROPERTY(VisibleAnywhere)	// no es editable

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float PlateMaxMass = 30.0f;

	//AActor* ActorThatOpens;
	AActor* Owner = nullptr;

	// Returns total mass of actors in plate in kg
	float GetTotalMassOfActorsOnPlate();
};
