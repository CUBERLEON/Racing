#include <iostream>
#include <vector>
#include "track.h"

int main(int argc, char** argv) {
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

        c.push_back(Cockroach("t1", 10, 1, 30, 8));
        c.push_back(Cockroach("t2", 12, 1.1, 25, 7, "my_strategy"));
        c.push_back(Cockroach("t3", 9, 0.7, 40, 11));
        c.push_back(Cockroach("t4", 11, 1.2, 23, 6));
                
        o.push_back(Obstacle({5, 10}, 3, 0.5));
        o.push_back(Obstacle({12, 8}, 4, 0.7));
        
        t.setCockroaches(c);
        t.setObstacles(o);
        
        t.run();
        
        //TODO: send response to server
        std::cout << t.serialize().dump(4);
    } catch (const std::exception& e) {
        std::cerr << e.what();
        exit(1);
    }
    
    return 0;
}