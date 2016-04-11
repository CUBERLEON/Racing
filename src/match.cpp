#include <iostream>
#include <vector>
#include "track.h"
#include "client.h"

int main(int argc, char** argv) {
    // try {
    //     Client client("127.0.0.1", 5000);
    //     client.connect();
    //     client.sendMessage("aaaa");
    //     client.sendMessage("bbbb");

    //     while (true) {
    //         for (int i = 0; i < client.getInboxSize(); ++i)
    //             std::cout << "Inbox message: " << client.getInbox()[i] << std::endl;
    //         client.clearInbox();
    //         Sleep(200);
    //     }
    // } catch (std::exception& e) {
    //     std::cout << e.what() << std::endl;
    // }
    
    // system("pause");
    
    try {
        if (argc < 2)
            throw std::invalid_argument("There are no passed arguments!");
        std::vector<Cockroach> c;
        std::vector<Obstacle> o;

        json data = json::parse(argv[1]);
        std::string port = (argc >= 3) ? argv[2] : "9002";
               
        for (unsigned int i = 0; i < data["cockroaches"].size(); ++i)
            c.push_back(Cockroach(data["cockroaches"][i]));
        for (unsigned int i = 0; i < data["obstacles"][i].size(); ++i)
            o.push_back(Obstacle(data["obstacles"][i]));
        
        Track t(data["length"], data["width"]);

        c.push_back(Cockroach("t1", 1.5, 0.05, 30, 8));
        c.push_back(Cockroach("t2", 2, 0.06, 25, 7, "my_strategy"));
        c.push_back(Cockroach("t3", 1.45, 0.04, 40, 11));
        c.push_back(Cockroach("t4", 1.8, 0.09, 23, 6));
        
        o.push_back(Obstacle({10, 20}, 7, 0.1));
        o.push_back(Obstacle({50, 15}, 15, 0.1));
        o.push_back(Obstacle({70, 10}, 13, 0.1));
        o.push_back(Obstacle({90, 5}, 7, 0.1));
        o.push_back(Obstacle({60, 13}, 9, 0.1));
        o.push_back(Obstacle({75, 17}, 11, 0.1));
        
        t.setCockroaches(c);
        t.setObstacles(o);
        
        t.run();
        
        //TODO: send response to server
        // std::cout << t.serialize().dump(4);
    } catch (const std::exception& e) {
        std::cerr << e.what();
        exit(1);
    }
    
    return 0;
}