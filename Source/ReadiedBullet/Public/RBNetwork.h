// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma comment(lib, "ws2_32.lib")
#include "ReadiedBullet/ReadiedBullet.h"
#include "GameFramework/Actor.h"
#include <WS2tcpip.h>
#include <map>
#include "RBNetwork.generated.h"


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_BUFFER 8192


UCLASS()
class READIEDBULLET_API ARBNetwork : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARBNetwork();

	bool m_IsRun;
	int m_ID;

	UPROPERTY(EditAnywhere)
	bool m_IsReady;

	UFUNCTION(BlueprintCallable)
	void InitClientSocket();

	UFUNCTION(BlueprintCallable)
	void Connect();//const char*);

	void Disconnect();
	void ProcessPacket(int iobytes, char* buf);
	void RecvPacketProcess(char* Packet);
	void RecvPacket();
	
	UFUNCTION(BlueprintCallable)
	void Send_Select_GameMode(uint8 modeType);

	UFUNCTION(BlueprintCallable)
	void Send_Ready();

	UFUNCTION(BlueprintCallable)
	bool Get_Ready();
	
	UFUNCTION(BlueprintCallable)
	void Set_Ready(bool setValue);

	UFUNCTION(BlueprintCallable)
	uint8 Get_Mode();

	void SetMyCharacter(class ARBCharacter*);

	class ARBCharacter* m_myCharacter;
	class ARBCharacter* m_otherplayer;

	struct FTimerHandle m_SendTimer;

	//UFUNCTION()
	void SendMyTransform();

	void SendProjectileSpawn(FVector loc, FRotator rot);

	void SendBulletType(e_bulletType type);
	
	std::map<int, class ARBCharacter*> m_OtherPlayers;
	UClass* BPCharacter;
	UClass* BPProjectile;

	class ARBPlayerController* pc;
	FVector m_myPos;
	FRotator m_myRot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	SOCKET m_ClientSocket;
	char m_gamemode;


	char m_RecvBuf[MAX_BUFFER]; //��������� ���Ź���
	char m_SendBuf[MAX_BUFFER]; //��������� �۽Ź���

	char m_PacketBuf[MAX_BUFFER];
	int m_PrevSize;

	WSABUF m_WSASendBuf; //�ü���� ����ϴ� �������
	WSABUF m_WSARecvBuf;//�ü���� ����ϴ� ���Ź���

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
