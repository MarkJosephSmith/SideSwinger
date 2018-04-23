// Fill out your copyright notice in the Description page of Project Settings.

#include "Chain.h"
#include "SideSwingerCharacter.h"


// Sets default values
AChain::AChain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChain::MakeAllLinksSeperated(float i_LinkRadius, float i_SeperationRadius, FVector i_ChainStart, AActor* i_pStartAttachment, AActor* i_pEndAttachment, FVector i_ChainEnd)
{
	//find the length of the chain and end early if it's too long
	float DistanceBetweenStartAndEnd = (i_ChainEnd - i_ChainStart).Size();

	if (DistanceBetweenStartAndEnd > m_ChainMaxLength)
	{
		DistanceBetweenStartAndEnd = m_ChainMaxLength;
	}
	//set the number of links and find the padding space between the first link and the last.
	float SeperationDiameter = i_SeperationRadius * 2;
	int NumberOfLinks = DistanceBetweenStartAndEnd / SeperationDiameter;
	float ChainLength = SeperationDiameter * static_cast<float>(NumberOfLinks);
	float RemainingSpace = DistanceBetweenStartAndEnd - ChainLength;
	FVector ChainPath = (i_ChainEnd - i_ChainStart);
	FVector ChainNormal = ChainPath;
	ChainNormal.Normalize();
	

	int CreatedLinks = 0;

	//make the first link and attach it to the character's hand socket
	UWorld * TheWorld = GetWorld();
	

	if (TheWorld)
	{
		//ASideSwingerCharacter * TheChar = Cast<ASideSwingerCharacter>(TheWorld->GetFirstPlayerController()));

		FActorSpawnParameters LinkSpawnParams;
		LinkSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector SpawnLocation = i_ChainStart + ((i_SeperationRadius) * ChainNormal);
		AChainLink * CurrentLink;
		//AChainLink * PreviousLink;
		
		 
		
		//spawn the first link
		if (NumberOfLinks > 0)
		{

			//spawn the link, add it to the array
			CurrentLink = (TheWorld->SpawnActor<AChainLink>(SpawnLocation, FRotator::ZeroRotator, LinkSpawnParams));
			ChainOfConnectedLinks.Emplace(CurrentLink);
																																							//ChainOfConnectedLinks.push_back(*CurrentLink);

			//Set up link and joint info

			//increment the count, update the spawn location and set the link we just spawned to the previous link
			CreatedLinks++;
			SpawnLocation = SpawnLocation + ((SeperationDiameter)* ChainNormal);
			//PreviousLink = CurrentLink;
		}
		
		
		//create and connect the remaining links
		while ( (CreatedLinks < NumberOfLinks) && (NumberOfLinks > 0))
		{
			
			//spawn the link, add it to the array
			CurrentLink = TheWorld->SpawnActor<AChainLink>(SpawnLocation, FRotator::ZeroRotator, LinkSpawnParams);
			ChainOfConnectedLinks.Emplace(CurrentLink);
			
			//attach to the ************************************************************** SHOULD BE ATTACHING TO THE NEXT LINK!!!!  (maybe, who the fuck knows) previous link
			//hand has joint, anchored to hand, linked first ball.  Each ball links the previous ball's joint to itself.  Final one links to the hit location outside the loop.

			 
			//PreviousLink->m_pPhysicsJoint->AddWorldOffset(ChainNormal * i_SeperationRadius);
			//PreviousLink->m_pPhysicsJoint->ConstraintActor1 = PreviousLink;
			//PreviousLink->m_pPhysicsJoint->ConstraintActor2 = CurrentLink;
			

			
			((ChainOfConnectedLinks[CreatedLinks -1])->m_pPhysicsJoint)->AddWorldOffset(ChainNormal * i_SeperationRadius);
			((ChainOfConnectedLinks[CreatedLinks - 1])->m_pPhysicsJoint)->ConstraintActor1 = (ChainOfConnectedLinks[CreatedLinks - 1]);
			((ChainOfConnectedLinks[CreatedLinks - 1])->m_pPhysicsJoint)->ComponentName1.ComponentName = FName("m_pLinkMesh");
			((ChainOfConnectedLinks[CreatedLinks - 1])->m_pPhysicsJoint)->ConstraintActor2 = (ChainOfConnectedLinks[CreatedLinks]);
			((ChainOfConnectedLinks[CreatedLinks - 1])->m_pPhysicsJoint)->ComponentName2.ComponentName = FName("m_pLinkMesh");

			//Set up link and joint info

			//increment the count
			CreatedLinks++;
			SpawnLocation = SpawnLocation + ((SeperationDiameter)* ChainNormal);
		
		}
		
	}



	
}
