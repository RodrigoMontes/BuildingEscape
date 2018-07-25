// Rodrigo Montes 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameframework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"

//siempre el ultimo include!
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//UPROPERTY(VisibleAnywhere)	// no es editable
	UPROPERTY(EditAnywhere)			// es editable
		float OpenAngle = 75.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float OpenDoorWaitTime = 0.2f;

	UPROPERTY(EditAnywhere)
		float PlateMaxMass = 30.0f;

	//AActor* ActorThatOpens;
	AActor* Owner = nullptr;
	float LastTimeDoorOpen;

	// Returns total mass in kg
	float TotalMassOfActorsOnPlate();
};
