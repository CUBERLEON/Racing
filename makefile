CC=g++
CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Ilibs/include
LDFLAGS=-static-libgcc -static-libstdc++ -static -lpthread
LDLIBS=
ifeq ($(OS),Windows_NT)
    LDLIBS+=-lws2_32 -lmswsock
endif
vpath %.o obj
vpath %.cpp src
vpath %.cpp libs/src/netlink

src_daemon=server.cpp daemon.cpp
src_match=match.cpp cockroach.cpp obstacle.cpp track.cpp state.cpp world.cpp client.cpp
src_test=test.cpp cockroach.cpp obstacle.cpp state.cpp world.cpp

src_netlink=core.cpp smart_buffer.cpp socket.cpp socket_group.cpp util.cpp

obj_daemon=$(addprefix obj/,$(src_daemon:.cpp=.o))
obj_match=$(addprefix obj/,$(src_match:.cpp=.o))
obj_test=$(addprefix obj/,$(src_test:.cpp=.o))
obj_netlink=$(addprefix obj/libs/netlink/,$(src_netlink:.cpp=.o))

all: daemon match test client

daemon: $(obj_daemon) $(obj_netlink)

#-include ./.depend
match: $(obj_match) $(obj_netlink)

test: $(obj_test)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) -c $(CXXFLAGS) $^ -o $@
	@#$(CXX) $(CXXFLAGS) -MM $^>>./.depend

obj/libs/netlink/%.o: libs/src/netlink/%.cpp
	@mkdir -p obj/libs/netlink
	$(CXX) -c $(CXXFLAGS) $^ -o $@

clean:
	@$(RM) -r obj
	@rm -f .depend
	@$(RM) daemon match test client