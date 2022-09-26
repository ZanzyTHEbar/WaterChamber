#ifndef LOCAL_MDNS_HANDLER_HPP
#define LOCAL_MDNS_HANDLER_HPP
#include <mDNS/MDNSManager.hpp>
#include <data/StateManager/StateManager.hpp>

class XMDNSHandler : public MDNSManager
{
private:
    MDNSHandler *mdnsHandler;
    StateManager<WiFiState_e> *stateManager;

public:
    XMDNSHandler(MDNSHandler *mdnsHandler,
                 StateManager<WiFiState_e> *stateManager);
    virtual ~XMDNSHandler();

    bool DiscoverMDNSBroker();

};

#endif // LOCAL_MDNS_HANDLER_HPP