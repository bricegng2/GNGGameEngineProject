#include "Framework.h"

#include "MKPlayerObject.h"
#include "SceneMarioKart.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
    m_serverInitialized = false;
    m_clientInitialized = false;

    m_socketHandle = 0;

    m_timeSinceLastPacketSent = FLT_MAX;

    WSAData wsaData;
    WSAStartup(MAKEWORD(1, 1), &wsaData);
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::initializeSocket(unsigned short port)
{
    m_socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    DWORD value = 1;
    ioctlsocket(m_socketHandle, FIONBIO, &value);

    sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = INADDR_ANY;
    localaddr.sin_port = htons(port);

    bind(m_socketHandle, (const sockaddr*)&localaddr, sizeof(sockaddr_in));
}

bool NetworkManager::isInitialized()
{
    return false;
}

void NetworkManager::initAsServer(unsigned short localPort)
{
}

void NetworkManager::initAsClient(unsigned short localport, const char* hostName, unsigned short serverPort)
{
    if (m_clientInitialized)
    {
        return;
    }

    initializeSocket(localport);

    hostent* host = gethostbyname(hostName);
    in_addr serverInAddr = *(in_addr*)host->h_addr_list[0];

    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_addr = serverInAddr;
    m_serverAddr.sin_port = htons(serverPort);

    m_clientInitialized = true;
}

void NetworkManager::update(float deltaTime, fw::Scene* pScene)
{
    sendUpdatePackets(pScene);
}

struct positionPacket
{
    vec3 pos;
    float angle;
};

struct allPositionsPacket
{
    int numPositions;
    positionPacket positions[4];
};

void NetworkManager::handleIncomingPackets(fw::Scene* pScene)
{
    char buffer[1000];
    int bufferSize = 1000;
    sockaddr_in address;
    int addrLength = sizeof(sockaddr_in);

    int bytes = -500;
    while (bytes != -1)
    {
        int flags = 0;
        bytes = (int)recvfrom(m_socketHandle, buffer, bufferSize,
            flags, (sockaddr*)&address, &addrLength);

        if (bytes != -1)
        {
            // Process packets here.
            allPositionsPacket* pPacket = (allPositionsPacket*)buffer;
            
            SceneMarioKart* mkScene = static_cast<SceneMarioKart*>(pScene);
            MKPlayerObject* player =  static_cast<MKPlayerObject*>(mkScene->getGameObjectByName("Player0"));
            MKPlayerObject* player1 = static_cast<MKPlayerObject*>(mkScene->getGameObjectByName("Player1"));
            MKPlayerObject* player2 = static_cast<MKPlayerObject*>(mkScene->getGameObjectByName("Player2"));
            MKPlayerObject* player3 = static_cast<MKPlayerObject*>(mkScene->getGameObjectByName("Player3"));
            
            player1->setTransform(pPacket->positions[1].pos.xz(), pPacket->positions[1].angle);
            player2->setTransform(pPacket->positions[2].pos.xz(), pPacket->positions[2].angle);
            player3->setTransform(pPacket->positions[3].pos.xz(), pPacket->positions[3].angle);
        }
    }
}

void NetworkManager::sendUpdatePackets(fw::Scene* pScene)
{
    if (m_clientInitialized)
    {
        SceneMarioKart* pMKScene = static_cast<SceneMarioKart*>(pScene);
        fw::GameObject* player = pMKScene->getGameObjectByName("Player0");

        positionPacket packet;
        packet.pos = player->getPosition();
        packet.angle = player->getRotation().y;

        int flags = 0;
        sendto(m_socketHandle, (const char*)&packet, sizeof(positionPacket),
            flags, (sockaddr*)&m_serverAddr, sizeof(sockaddr_in));

        handleIncomingPackets(pScene);
    }
}

void NetworkManager::webRequest()
{
}
