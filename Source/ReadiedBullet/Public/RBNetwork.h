// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma comment(lib, "ws2_32.lib")
#include "ReadiedBullet/ReadiedBullet.h"
#include "GameFramework/Actor.h"
#include <WS2tcpip.h>
#include "RBNetwork.generated.h"


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_BUFFER 4096


UCLASS()
class READIEDBULLET_API ARBNetwork : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARBNetwork();

	bool m_IsRun;

	UFUNCTION(BlueprintCallable)
	void InitClientSocket();

	UFUNCTION(BlueprintCallable)
		void Connect();//const char*);

	//void DisConnect();
	void ProcessPacket(int user_id, char* buf);
	void RecvPacketProcess(char* Packet);
	void RecvPacket();
	
	UFUNCTION(BlueprintCallable)
	void Send_Select_GameMode(uint8 modeType);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	SOCKET m_ClientSocket;
	int m_ID;

	char m_RecvBuf[MAX_BUFFER]; //사용자정의 수신버퍼
	char m_SendBuf[MAX_BUFFER]; //사용자정의 송신버퍼

	char m_PacketBuf[MAX_BUFFER];
	int m_PrevSize;

	WSABUF m_WSASendBuf; //운영체제와 통신하는 센드버퍼
	WSABUF m_WSARecvBuf;//운영체제와 통신하는 수신버퍼

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
