// Rodrigo Montes 2018

#include "Grabber.h"

/// We #define the word OUT to mark parameters that are going to be changed when calling some methods or functions
/// it's just "cosmetic"
#define OUT						


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	/// Mi codigo:
	FindPhysicsHandleComponent();	
	SetupInputComponent();			
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// If we grab something
	if (PhysicsHandle->GetGrabbedComponent())
	{
		/// We move the grabbed object with the player
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}		
}


FVector UGrabber::GetReachLineStart()
{
	/// Funcion getter that get the position and rotation of player controller (GetFirstPlayerController)
	/// note that modifies the input parameters also (added the word OUT to mark that fact)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPortLocation,
		OUT PlayerViewPortRotation);

	return PlayerViewPortLocation;
}


// Get the end point for the trace line (with reach)
FVector UGrabber::GetReachLineEnd()
{
	/// Getter function that get the position and rotation of player controller (GetFirstPlayerController)
	/// note that modifies the input parameters also (added the word OUT to mark that fact)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPortLocation,
		OUT PlayerViewPortRotation);

	/// Calculate the end point of our reach line
	return PlayerViewPortLocation + (PlayerViewPortRotation.Vector() * Reach);
}


// Line traces and grabs what's in reach
void UGrabber::Grab()
{
	/// Line trace and see if we reach actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();

	// Only if we hit an actor with physics body while pressing the grab key
	if (HitResult.GetActor())
	{
		// Attach physics handle to actor with physics body
		PhysicsHandle->GrabComponent(
			ComponentToGrab,												// component to grab
			NAME_None,														// if its rigged body we name the bone connected, if not we put NAME_None
			ComponentToGrab->GetOwner()->GetActorLocation(),				// location of actor to grab
			true															// allow rotation (or not) while grabbing
		);
	}
}


// Called on key release
void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}


// Finds a physics handle component
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle component missing in %s"), *GetOwner()->GetName());
	}
}


// Finds and binds the input component for grabbing
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		/// If we find the input component we bind the press and release actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component missing in %s"), *GetOwner()->GetName());
	}
}


// Returns the first physics body in reach
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Draws a test line (visible)
	//DrawDebugLine(GetWorld(),GetReachLineStart(),GetEndPointOfReach(),FColor(255,0,0),false,0.0f,0.0f,1.0f);

	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line trace (ray-casting) for detecting a physics body in front and in reach of the line traced
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,																//output
		GetReachLineStart(),														//line start
		GetReachLineEnd(),															//line end
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),			//type of object to find
		TraceParameters																//some parameters... dunno
	);

	return HitResult;
}

