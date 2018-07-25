// Rodrigo Montes 2018

#include "OpenDoor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// busca top down el pawn (player), desde el mundo, al controlador, al player
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	// cambiar la rotacion para abrir la puerta
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	// cambiar la rotacion para cerrar la puerta
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// we check on each tick if volume on trigger volume is higher or equal to the max mass threshold
	if (TotalMassOfActorsOnPlate() >= PlateMaxMass) 
	{
		OpenDoor();
		LastTimeDoorOpen = GetWorld()->GetTimeSeconds();
	}

	if ((GetWorld()->GetTimeSeconds() - LastTimeDoorOpen) > OpenDoorWaitTime)
	{
		LastTimeDoorOpen = 0;
		CloseDoor();
	}

}

float UOpenDoor::TotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray <AActor*>  OverlappingActors;

	// Find the actors overlapping the pressure plate
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	/// Iterate through them adding their masses
	for (const auto* ActorThatOverlaps : OverlappingActors)
	{
		TotalMass += ActorThatOverlaps->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

