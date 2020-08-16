#pragma once
#define SERVERPORT 9000
#define MAXBUFFER 4096
#define MAXPLAYER 2
#define MAXPACKETSIZE 255
#define MAX_ID_LEN 30

//��Ŷ�� ////////
enum class e_PacketType : uint8_t
{
	e_LoginOK,
	e_Select_GameMode,

};

enum class e_GameStateInfo : uint8_t//unsigned char
{
	e_None,
	e_Ready,
	e_UnReady
};

//Ŭ��:ó���� ���ӿ� �α����� �Ѵ�.(start scene, �α��� ��ư�� ������)
//����: �α����� Ȯ�εǾ����� Ŭ�󿡰� �α��� ��Ŷ�� SEND�Ѵ�. 
//Ŭ��: �α�����Ŷ�� RECV�Ѵ�. 
//Ŭ��: �÷��̸�带 �����ϴµ� ���⼭ �̱۸�带 �����ϸ� 
//Ŭ��: �÷��̸�带 ��Ƽ��带 �����ϸ� ��Ʈ��ũ�� �����Ѵ�.

//Ŭ��: ��, ĳ����Ÿ�� ������ ���ù�ư�� ������ �������� ������ ��Ŷ�� SEND�Ѵ�.
//����: RECV�ϰ� ���̸� ��, ĳ���͸� ĳ���͸� �ٸ� Ŭ���̾�Ʈ���� SEND�Ѵ�.
//Ŭ��: ���̸� ��, ĳ���͸� ĳ���Ϳ� ���� �κ�scene���� ���� �ٸ� ĳ���ͶǴ� �̹����� id�� �°� ����.
//Ŭ��: READY��ư�� ������ READY��Ŷ�� SEND�Ѵ�.
//����: READY�� RECV�Ѵ�. ��� Ŭ���̾�Ʈ�� READY�������� Ȯ���Ѵ�.
//����: ������ ���Ŭ���̾�Ʈ�鿡�� ������ �����϶�� ���¸� ������. 
//����: �����϶�� ���¸� ������ ���ÿ� GameTime��Ŷ�� ������.. �̴� 1�ʿ� �ѹ��� Ŭ���̾�Ʈ���� send���־���Ѵ�.
//����: �ƴϸ� Ŭ���̾�Ʈ�鿡�� ��� ���� �����ҋ����� ���. 
//Ŭ��: ������ �����϶�� ���¸� RECV�ϰ� GameTime�� RECV�Ѵ�.
//Ŭ��:OpenLevel("TestLevel")�� �ϰ� ����������. ��� 6���� ĳ���� ����->���� �÷��̾���Ʈ�ѷ� ����.
//Ŭ��: ���� �÷��̾��� ������ 60�����Ӹ��� SEND, 
//����: ���� �÷��̾��� ������ RECV, send�� �÷��̾ �����ϰ� �ٸ��÷��̾�鿡�� send�� �÷��̾��� ������ send
//Ŭ��: �ٸ��÷��̾���� ������recv,  ��Ŷ ó�� �� ����


#pragma pack(push, 1)
struct PlayerPositon
{
	float x;
	float y;
	float z;
};
struct PlayerPosition
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
	PlayerPositon m_Position;
	PlayerPosition m_Rotation;
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
	unsigned char mode;// 0 = solo , 1 = multi
};


#pragma pack(pop)
////////////////