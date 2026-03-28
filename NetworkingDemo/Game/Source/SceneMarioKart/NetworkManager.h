#pragma once

#include <winsock.h>

class SceneMarioKart;

class NetworkManager
{
protected:
    bool m_serverInitialized;
    bool m_clientInitialized;

    int m_socketHandle;

    std::vector<sockaddr_in> m_clientAddresses;
    sockaddr_in m_serverAddr;

    float m_timeSinceLastPacketSent;

protected:
    void initializeSocket(unsigned short port);

public:
    NetworkManager();
    virtual ~NetworkManager();

    bool isInitialized();

    void initAsServer(unsigned short localPort);
    void initAsClient(unsigned short localPort, const char* hostName, unsigned short serverPort);

    void update(float deltaTime, fw::Scene* pScene);

    void handleIncomingPackets(fw::Scene* pScene);
    void sendUpdatePackets(fw::Scene* pScene);

    void webRequest();
};
