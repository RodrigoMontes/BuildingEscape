// Rodrigo Montes 2018

#include "Grabber.h"

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
}


// Line traces and grabs what's in reach
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key pressed"));

	/// Line trace and see if we reach actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();
}


// Called on key release
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key released"));
}


// Finds a physics handle component
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		/// If we find the physics hande component we do something...
	}
	else
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
		
		UE_LOG(LogTemp, Warning, TEXT("Input component found in %s"), *GetOwner()->GetName());

		/// If we find the input component we bind it
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component missing in %s"), *GetOwner()->GetName());
	}
}


// Returns the first physics body in reach and returns it
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Funcion getter que obtiene la posicion y rotacion del player
	/// notar que modifica los parametros que le pasemos, en este caso un FVector y un FRotator
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPortLocation,
		OUT PlayerViewPortRotation);

	/// Calculate the end point of our reach line
	LineTraceEnd = PlayerViewPortLocation + (PlayerViewPortRotation.Vector() * Reach);

	/// dibuja una linea para pruebas
	//DrawDebugLine(GetWorld(),PlayerViewPortLocation,LineTraceEnd,FColor(255,0,0),false,0.0f,0.0f,1.0f);

	/// line trace (ray-casting) for detecting a physics body in front and in reach of the line traced
	FHitResult LineTraceHit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,															//output
		PlayerViewPortLocation,														//line start
		LineTraceEnd,																//line end
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),			//type of object to find
		TraceParameters																//some parameters... dunno
	);

	/// shows the actor in reach on the log (for debug)
	//if (LineTraceHit.GetActor())
	//{
	//	
	//	UE_LOG(LogTemp, Warning, TEXT("Actor %s within reach"), *LineTraceHit.GetActor()->GetName());
	//}

	return LineTraceHit;
}

