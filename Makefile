OBJ = \
    main.o \

CXXFLAGS = -I/home/chaisneau/boost_1_85_0
LDFLAGS = -L/home/chaisneau/boost_1_85_0/stage/lib -lboost_system -lpthread

all: output

output: $(OBJ)
	g++ $(OBJ) -o output $(LDFLAGS)

%.o: %.cpp
	g++ -c $^ -o $@ $(CXXFLAGS)


clean:
	rm -f ./*.o

fclean: clean
	rm -f ./output

re: fclean all

.PHONY: all clean fclean re all
