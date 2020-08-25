#pragma once
#define SERVERPORT 9000
#define MAXBUFFER 8192
#define MAXPLAYER 2
#define MAXPACKETSIZE 255
#define MAX_ID_LEN 30

//패킷들 ////////
enum class e_PacketType : uint8_t
{
	e_LoginOK,
	e_Select_GameMode,
	e_LeavePacket,
	e_ReadyPacket,
	e_StartPacket,
	e_PlayerInfoPacket,
	e_EnterPacket,
	e_myCharacterPacket,
	e_BulletSpawnPacket,
	e_BulletSlotPacket,
	e_BulletMovePacket,
};

enum class e_bulletType : uint8_t
{
	e_Bullet1,
	e_Bullet2,
	e_Bullet3,
};

//클라:처음에 게임에 로그인을 한다.(start scene, 로그인 버튼을 누르면)
//서버: 로그인이 확인되었으면 클라에게 로그인 패킷을 SEND한다. 
//클라: 로그인패킷을 RECV한다. 
//클라: 플레이모드를 선택하는데 여기서 싱글모드를 선택하면 
//클라: 플레이모드를 멀티모드를 선택하면 네트워크를 지속한다.

//클라: 팀, 캐릭터타입 각각을 선택버튼을 누르면 서버에게 각각의 패킷을 SEND한다.
//서버: RECV하고 팀이면 팀, 캐릭터면 캐릭터를 다른 클라이언트에게 SEND한다.
//클라: 팀이면 팀, 캐릭터면 캐릭터에 따라 로비scene에서 각각 다른 캐릭터또는 이미지를 id에 맞게 띄운다.
//클라: READY버튼을 누르면 READY패킷을 SEND한다.
//서버: READY를 RECV한다. 모든 클라이언트가 READY상태인지 확인한다.
//서버: 맞으면 모든클라이언트들에게 게임을 시작하라는 상태를 보낸다. 
//서버: 시작하라는 상태를 보냄과 동시에 GameTime패킷을 보낸다.. 이는 1초에 한번씩 클라이언트에게 send해주어야한다.
//서버: 아니면 클라이언트들에게 모두 레디를 수신할떄까지 대기. 
//클라: 게임을 시작하라는 상태를 RECV하고 GameTime을 RECV한다.
//클라:OpenLevel("TestLevel")을 하고 게임을시작. 모든 6명의 캐릭터 스폰->각각 플레이어컨트롤러 적용.
//클라: 현재 플레이어의 정보를 60프레임마다 SEND, 
//서버: 현재 플레이어의 정보를 RECV, send한 플레이어를 제외하고 다른플레이어들에게 send한 플레이어의 정보를 send
//클라: 다른플레이어들의 정보를recv,  패킷 처리 후 적용


#pragma pack(push, 1)
struct PlayerPosition
{
	float x;
	float y;
	float z;
};
struct PlayerRotation
{
	float Pitch;
	float Yaw;
	float Roll;
};
struct PlayerVelocity
{
	float vx;
	float vy;
	float vz;
};
struct PlayerInfo
{
	PlayerPosition m_Position;
	PlayerRotation m_Rotation;
	PlayerVelocity m_Velocity;
};

struct sc_packet_loginOK
{
	char size;
	e_PacketType type;
	int m_id;
};

struct cs_packet_selectGameMode
{
	char size;
	e_PacketType type;
	unsigned char mode;		// 0 = solo , 1 = multi
};

struct cs_packet_leavePacket
{
	char size;
	e_PacketType type;
	int m_id;
};

struct sc_packet_leavePacket
{
	char size;
	e_PacketType type;
	int m_id;
};

struct cs_packet_readyPacket
{
	char size;
	e_PacketType type;
	int m_id;
	bool isReady;
};

struct cs_packet_playerInfo
{
	char size;
	e_PacketType type;
	int m_id;
	PlayerInfo info;
};

struct sc_packet_playerInfo
{
	char size;
	e_PacketType type;
	int m_id;
	PlayerInfo info;
};

struct sc_packet_startPacket
{
	char size;
	e_PacketType type;
	int m_id;
	PlayerPosition pos;
	PlayerRotation rot;
};

struct sc_packet_enterPacket
{
	char size;
	e_PacketType type;
	int m_id;
	PlayerPosition pos;
	PlayerRotation rot;
};
 
struct sc_packet_myCharacterPacket
{
	char size;
	e_PacketType type;
	int m_id;
	PlayerPosition pos;
	PlayerRotation rot;
};

struct cs_packet_bulletSpawnPacket
{
	char size;
	e_PacketType type;
	int m_id;
	PlayerPosition pos;
	PlayerRotation rot;
};

struct sc_packet_bulletSpawnPacket
{
	char size;
	e_PacketType type;
	int m_id;
	PlayerPosition pos;
	PlayerRotation rot;
};

struct cs_packet_bulletSlotPacket
{
	char size;
	e_PacketType type;
	e_bulletType bulletType;
	int m_id;
};

struct sc_packet_bulletSlotPacket
{
	char size;
	e_PacketType type;
	e_bulletType bulletType;
	int m_id;
};

#pragma pack(pop)
////////////////