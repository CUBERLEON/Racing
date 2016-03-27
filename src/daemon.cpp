#include <iostream>
#include "server.h"

int main() {
    try {
        Server server(5000);
        server.start();
        
        // Sleep(8000);
        // for (unsigned i = 1; i <= server.getConnectionsCnt(); ++i)
        //     server.sendMessage("ttt", i);
        
        while (true) {
            for (int i = 0; i < server.getInboxSize(); ++i) {
                std::cout << "Inbox message: " << server.getInbox()[i] << std::endl;
                for (unsigned j = 1; j <= server.getConnectionsCnt(); ++j)
                    server.sendMessage("forwarded message: " + server.getInbox()[i], j);
            }
            server.clearInbox();
            Sleep(200);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    system("pause");    
    
    return 0; 
}