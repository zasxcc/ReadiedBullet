// Fill out your copyright notice in the Description page of Project Settings.


#include "RBNetwork.h"

// Sets default values
ARBNetwork::ARBNetwork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARBNetwork::BeginPlay()
{
	Super::BeginPlay();
	InitClientSocket();
	Connect();
}

// Called every frame
void ARBNetwork::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if(this != nullptr) // 솔로모드인지 멀티모드인지 확인 
	RecvPacket();
	
}

void ARBNetwork::RecvPacket()
{
	DWORD RecvBytes = 0;
	DWORD flags = 0;

	WSARecv(m_ClientSocket, &m_WSARecvBuf, 1, &RecvBytes, &flags, NULL, NULL);
	UE_LOG(LogTemp, Error, TEXT("iobytes: %d"), RecvBytes);
	//if (RecvBytes == -1) return;
	ProcessPacket(RecvBytes, m_RecvBuf);
}

void ARBNetwork::ProcessPacket(int iobytes, char* buf)
{
	char* ptr = buf;
	static size_t in_packet_size = 0;
	while (iobytes > 0)
	{
		if (0 == in_packet_size)
			in_packet_size = ptr[0];
		if (iobytes + m_PrevSize >= in_packet_size)
		{
			memcpy(m_PacketBuf + m_PrevSize, ptr, in_packet_size - m_PrevSize);
			RecvPacketProcess(m_PacketBuf);
			ptr += in_packet_size - m_PrevSize;
			iobytes -= in_packet_size - m_PrevSize;
			in_packet_size = 0;
			m_PrevSize = 0;
		}
		else
		{
			memcpy(m_PacketBuf + m_PrevSize, ptr, iobytes);
			m_PrevSize += iobytes;
			iobytes = 0;
			break;
		}
	}
}

void ARBNetwork::RecvPacketProcess(char* Packet)
{
	char PacketType = Packet[1];

	switch ((e_PacketType)PacketType)
	{
	case e_PacketType::e_LoginOK:
	{
		sc_packet_loginOK* packet = reinterpret_cast<sc_packet_loginOK*>(Packet);
		m_ID = packet->m_id;
	}
	break;
	
	}
}
void ARBNetwork::Send_Select_GameMode(uint8 modeType)
{
	cs_packet_selectGameMode p{};
	p.mode = modeType;
	p.size = sizeof(p);
	p.type = e_PacketType::e_Select_GameMode;

	DWORD SentBytes = 0;
	DWORD flags = 0;

	memcpy(m_SendBuf, &p, sizeof(p));
	m_WSASendBuf.len = sizeof(p);
	int retval = WSASend(m_ClientSocket, &m_WSASendBuf, 1, &SentBytes, flags, NULL, NULL);
	UE_LOG(LogTemp, Error, TEXT("Send_Select_GameMode %d"), retval);
}


void ARBNetwork::InitClientSocket()
{
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return;
	}

	m_ClientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_ClientSocket)
	{
		//PWLOG(Error, TEXT("Make Socket Error"));
		return;
	}
	m_WSARecvBuf.buf = m_RecvBuf;
	m_WSARecvBuf.len = MAX_BUFFER;
	m_WSASendBuf.buf = m_SendBuf;
}

void ARBNetwork::Connect()//const char* serverIP)
{
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(SOCKADDR_IN));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVER_PORT);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");//(serverIP);

	int retval = connect(m_ClientSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	UE_LOG(LogTemp, Error, TEXT("%d"), retval);
	if (retval == SOCKET_ERROR)
	{
		return;
	}
	m_IsRun = true;

	u_long sock_on = 1;
	retval =ioctlsocket(m_ClientSocket, FIONBIO, &sock_on);

	return;
}
