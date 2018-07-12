// Rodrigo Montes 2018

#include "OpenDoor.h"


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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	// cambiar la rotacion para abrir la puerta
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	// cambiar la rotacion para cerrar la puerta
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// chequeamos el trigger volume en cada frame
	// si ActorThatOpens esta dentro del trigger volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
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

