#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <json/json.hpp>
#include "server.h"
#include "utils.h"
#include "cockroach.h"
#include "obstacle.h"

using json=nlohmann::json;

void results_listener();

Server* server;

int main() {
    try {
        server = new Server(5000);
        server->start();
        
        std::thread results_listener_thread(results_listener);
        
        std::vector<Cockroach> c;
        std::vector<Obstacle> o;
        
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

        std::string command;
        std::cout << ">";
        while (std::getline(std::cin, command)) {
            if (command == "exit") {
                server->stop();
                exit(0);
            } else if (command == "run") {
                json data;
                data["length"] = 150;
                data["width"] = 40;
                
                for (unsigned i = 0; i < c.size(); ++i)
                    data["cockroaches"][i] = c[i].serialize();
                for (unsigned i = 0; i < o.size(); ++i)
                    data["obstacles"][i] = o[i].serialize();
                
                std::string s = data.dump();
                replaceStringInPlace(s, "\"", "\"\"\"");
                system((std::string(".\\match.exe ") + "\"" + s + "\" 5000").c_str());
            } else if (command == "dd") {
                
            } else if (command == "help") {
                std::cout << "Help is currently not available!" << std::endl;
            } else {
                std::cout << "'" << command << "' is unknown command. Please type 'help' for usage instructions." << std::endl;
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << ">";
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }    
    
    return 0; 
}

void results_listener() {
    while (true) {
        for (unsigned i = 0; i < server->getInboxSize(); ++i) {
            try {
                json data = json::parse(server->getInbox()[i]);
                if (data["run_finished"]) {
                    std::cout << "----------RACE FINISHED----------" << std::endl;
                    std::cout << "Results:" << std::endl;
                    for (unsigned i = 0; i < data["standings"].size(); ++i) {
                        std::string name = data["world"]["cockroaches"][(int)data["standings"][i]]["name"];
                        std::cout << i+1 << ((i == 0) ? "st" : (i == 1) ? "nd" : (i == 2) ? "rd" : "th") << " - " << name << std::endl; 
                    }
                    std::cout << "---------------------------------" << std::endl;
                }
            } catch (std::exception& e) {
                std::cerr << "Error! " << e.what() << std::endl;
            }
        }
        server->clearInbox();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}