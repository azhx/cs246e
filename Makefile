CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = gameone
AGE = ./age
GAME = ./game1
SOURCES = $(wildcard $(AGE)/*.cc) $(wildcard $(GAME)/*.cc)
OBJECTS = ${SOURCES:.cc=.o}

EXEC2 = gametwo
GAME2 = ./game2
SOURCES2 = $(wildcard $(AGE)/*.cc) $(wildcard $(GAME2)/*.cc)
OBJECTS2 = ${SOURCES2:.cc=.o}

DEPENDS = ${OBJECTS:.o=.d} ${OBJECTS2:.o=.d} $(wildcard $(AGE)/*.h=.d) $(wildcard $(GAME)/*.h=.d)  $(wildcard $(GAME2)/*.h=.d) 
all: ${EXEC} ${EXEC2}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${GIVEN} -o ${EXEC} ${CXXFLAGS} -lncursesw -D_XOPEN_SOURCE_EXTENDED

${EXEC2}: ${OBJECTS2}
	${CXX} ${OBJECTS2} ${GIVEN} -o ${EXEC2} ${CXXFLAGS} -lncursesw -D_XOPEN_SOURCE_EXTENDED

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${OBJECTS2} ${EXEC2} ${EXEC} ${DEPENDS}
