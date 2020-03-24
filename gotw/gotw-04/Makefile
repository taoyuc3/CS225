EXENAME = main
OBJS = main.o skipNode.o skipList.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm


all: $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp skipNode.h skipList.h
	$(CXX) $(CXXFLAGS) main.cpp

skipNode.o: skipNode.cpp skipNode.h
	$(CXX) $(CXXFLAGS) skipNode.cpp

skipList.o: skipList.cpp skipList.h
	$(CXX) $(CXXFLAGS) skipList.cpp

clean:
	-rm -f *.o $(EXENAME)
