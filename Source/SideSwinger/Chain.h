// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChainLink.h"
#include <list>
#include "Chain.generated.h"

UCLASS()
class SIDESWINGER_API AChain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChain();

	UPROPERTY(EditAnywhere, Category = "Chain")
	float m_ChainMaxLength;

	//std::list<AChainLink*> ChainOfConnectedLinks;
	TArray<AChainLink*> ChainOfConnectedLinks;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Use the distance between links and the distance from the start to the target to spawn an array of connected links*/
	UFUNCTION(BlueprintCallable, Category = "Chain")
	void MakeAllLinksSeperated(float i_LinkRadius, float i_SeperationRadius, FVector i_ChainStart, AActor* i_pStartAttachment, AActor* i_pEndAttachment, FVector i_ChainEnd);
	
	
};
