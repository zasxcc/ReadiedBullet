// Fill out your copyright notice in the Description page of Project Settings.


#include "RBNetwork.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "ReadiedBullet/RBCharacter.h"
#include "ReadiedBullet/RBPlayerController.h"
// Sets default values
ARBNetwork::ARBNetwork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	memset(m_PacketBuf, 0, MAX_BUFFER);
	m_PrevSize = 0;

	static ConstructorHelpers::FClassFinder<ARBCharacter> Character(TEXT("/Game/Blueprints/BP_RBCharacter.BP_RBCharacter_C"));
	if (Character.Succeeded() && Character.Class != NULL)
	{
		BPCharacter = Character.Class;
	}
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
	
	//if (RecvBytes == -1) return;
	int iobytes = RecvBytes;
	ProcessPacket(iobytes, m_RecvBuf);
}

void ARBNetwork::ProcessPacket(int iobytes, char* buf)
{
	/*char* ptr = buf;
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
	}*/

	int packet_size = 0;
	char* p = buf;
	int rest_byte = iobytes;

	// p가 맨 앞부분(즉, 크기)을 가리키고 있지 않으면?
	if (m_PrevSize != 0)
		packet_size = buf[0];

	while (rest_byte > 0)
	{
		// 새 패킷을 받아왔을 때.
		if (packet_size == 0)
			packet_size = *p;

		if (packet_size <= rest_byte + m_PrevSize)
		{	// 패킷 완성
			// cu.m_prev_size 만큼 뒤에 전송하려면, cu.m_prev_size만큼 뺀 크기를 복사해야 한다.
			memcpy(m_PacketBuf + m_PrevSize, p, packet_size - m_PrevSize);
			p += (packet_size - m_PrevSize);
			rest_byte -= (packet_size - m_PrevSize);
			packet_size = 0;
			//RecvPacketProcess(m_PacketBuf);
			switch ((e_PacketType)m_PacketBuf[1])
			{
			case e_PacketType::e_LoginOK:
			{
				sc_packet_loginOK* packet = reinterpret_cast<sc_packet_loginOK*>(m_PacketBuf);
				m_ID = packet->m_id;
			}
			break;
			case e_PacketType::e_StartPacket:
			{
				sc_packet_startPacket* packet = reinterpret_cast<sc_packet_startPacket*>(m_PacketBuf);

				UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
				UGameplayStatics::LoadStreamLevel(GetWorld(), FName("Desert1"), true, false, FLatentActionInfo{});
				UGameplayStatics::UnloadStreamLevel(GetWorld(), FName("Room"), FLatentActionInfo{}, false);
				
				FVector pos = FVector(packet->pos.x, packet->pos.y, packet->pos.z);
				FRotator rot = FRotator(packet->rot.Pitch, packet->rot.Yaw, packet->rot.Roll);
				m_myCharacter = GetWorld()->SpawnActor<ARBCharacter>(BPCharacter, pos, rot, FActorSpawnParameters{});
				m_myCharacter->m_ID = m_ID;
				
				GetWorldTimerManager().SetTimer(m_SendTimer, this, &ARBNetwork::SendMyTransform, 0.016f, true, 0.0f);
			}
			break;
			case e_PacketType::e_EnterPacket:
			{
				sc_packet_enterPacket* packet = reinterpret_cast<sc_packet_enterPacket*>(m_PacketBuf);
				if (m_ID == packet->m_id) return;

				
				FVector pos = FVector(packet->pos.x, packet->pos.y, packet->pos.z);
				FRotator rot = FRotator(packet->rot.Pitch, packet->rot.Yaw, packet->rot.Roll);
				m_OtherPlayers.Emplace(packet->m_id, GetWorld()->SpawnActor<ARBCharacter>(BPCharacter, pos, rot, FActorSpawnParameters{}) );
				//m_OtherPlayers[packet->m_id]->m_ID= m_ID;
				m_OtherPlayers.FindRef(packet->m_id)->m_ID = packet->m_id;
			}
			break;
			case e_PacketType::e_PlayerInfoPacket:
			{
				sc_packet_playerInfo* packet = reinterpret_cast<sc_packet_playerInfo*>(m_PacketBuf);
				auto character = m_OtherPlayers.FindRef(packet->m_id);
				auto pos = packet->info.m_Position;
				auto rot = packet->info.m_Rotation;
				auto vel = packet->info.m_Velocity;

				if (character != nullptr)
				{
					character->SetActorLocation(FVector(pos.x, pos.y, pos.z));
					character->SetActorRotation(FRotator(rot.Pitch, rot.Yaw, rot.Roll));
					//character->AddMovementInput(FVector(vel.vx, vel.vy, vel.vz));
				}
			}
			break;
			}
			m_PrevSize = 0;
		}
		else
		{	// 패킷 미완성
			// 처리해야 될 버퍼 + 전에 받은 크기에, 지금 처리하고 있는 버퍼를, 처리해야 할 남은 크기만큼.
			memcpy(m_PacketBuf + m_PrevSize, p, rest_byte);
			m_PrevSize += rest_byte;
			rest_byte = 0;
			p += rest_byte;
		}
	}
}

void ARBNetwork::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//Disconnect();
	memset(m_PacketBuf, 0, MAX_BUFFER);
	m_PrevSize = 0;
	GetWorldTimerManager().ClearTimer(m_SendTimer);
	
}
void ARBNetwork::SendMyTransform()
{
	PlayerPosition pos{};
	PlayerRotation rot{};
	PlayerVelocity vel{};

	if (m_myCharacter == nullptr) return;
	auto apos = m_myCharacter->GetActorLocation();
	pos.x = apos.X;
	pos.y = apos.Y;
	pos.z = apos.Z;
	UE_LOG(LogTemp, Error, TEXT("id: %d pos: %f %f %f"), m_ID ,pos.x, pos.y, pos.z);

	auto arot = m_myCharacter->GetActorRotation();
	rot.Pitch = arot.Pitch;
	rot.Roll = arot.Roll;
	rot.Yaw = arot.Yaw;

	auto avel = m_myCharacter->GetVelocity();
	vel.vx = avel.X;
	vel.vy = avel.Y;
	vel.vz = avel.Z;

	PlayerInfo info{ pos,rot,vel };

	cs_packet_playerInfo p{};
	p.m_id = m_ID;
	p.size = sizeof(p);
	p.type = e_PacketType::e_PlayerInfoPacket;
	p.info = info;


	DWORD SentBytes = 0;
	DWORD flags = 0;

	memcpy(m_SendBuf, &p, sizeof(p));
	m_WSASendBuf.len = sizeof(p);
	int retval = WSASend(m_ClientSocket, &m_WSASendBuf, 1, &SentBytes, flags, NULL, NULL);

}
void ARBNetwork::Disconnect()
{
	cs_packet_leavePacket p{};
	p.m_id = m_ID;
	p.size = sizeof(p);
	p.type = e_PacketType::e_LeavePacket;

	DWORD SentBytes = 0;
	DWORD flags = 0;

	memcpy(m_SendBuf, &p, sizeof(p));
	m_WSASendBuf.len = sizeof(p);
	int retval = WSASend(m_ClientSocket, &m_WSASendBuf, 1, &SentBytes, flags, NULL, NULL);
}

void ARBNetwork::RecvPacketProcess(char* Packet)
{
	//char PacketType = Packet[1];

	switch ((e_PacketType)Packet[1])
	{
	case e_PacketType::e_LoginOK:
	{
		sc_packet_loginOK* packet = reinterpret_cast<sc_packet_loginOK*>(Packet);
		m_ID = packet->m_id;
	}
	break;
	default:
	{
		DebugBreak();
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

	m_gamemode = modeType;

	DWORD SentBytes = 0;
	DWORD flags = 0;

	memcpy(m_SendBuf, &p, sizeof(p));
	m_WSASendBuf.len = sizeof(p);
	int retval = WSASend(m_ClientSocket, &m_WSASendBuf, 1, &SentBytes, flags, NULL, NULL);
	UE_LOG(LogTemp, Error, TEXT("Send_Select_GameMode %d"), retval);
}

void ARBNetwork::SetMyCharacter(ARBCharacter* character)
{
	this->m_myCharacter = character;
}

uint8 ARBNetwork::Get_Mode()
{
	return (uint8)m_gamemode;
}

bool ARBNetwork::Get_Ready()
{
	return m_IsReady;
}

void ARBNetwork::Set_Ready(bool setValue)
{
	m_IsReady = setValue;
}

void ARBNetwork::Send_Ready()
{
	cs_packet_readyPacket p{};

	if (m_IsReady)
		p.isReady = true;
	else
		p.isReady = false;

	p.m_id = m_ID;
	p.size = sizeof(p);
	p.type = e_PacketType::e_ReadyPacket;

	DWORD SentBytes = 0;
	DWORD flags = 0;

	memcpy(m_SendBuf, &p, sizeof(p));
	m_WSASendBuf.len = sizeof(p);
	int retval = WSASend(m_ClientSocket, &m_WSASendBuf, 1, &SentBytes, flags, NULL, NULL);
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
