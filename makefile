GPP=g++
PROJ_FILES_PATH=.
TESTS_DIR=./WorldCupTests
O_FILES_DIR=$(TESTS_DIR)/OFiles
EXEC=WorldCupUnitTester
TESTS_INCLUDED_FILE=worldcup23a1.h $(TESTS_DIR)/catch.hpp
OBJS=$(O_FILES_DIR)/UnitTests.o $(O_FILES_DIR)/NodeList_Teams.o $(O_FILES_DIR)/Team.o $(O_FILES_DIR)/Player.o $(O_FILES_DIR)/worldcup23a1.o # UPDATE HERE ALL THE O FILES YOU CREATED BELOW
DEBUG_FLAG= -g # can add -g
COMP_FLAG=--std=c++11 -Wall -Werror -pedantic-errors $(DEBUG_FLAG)

$(EXEC) : $(OBJS)
	$(GPP) $(COMP_FLAG) $(OBJS) -o $@

$(O_FILES_DIR)/UnitTests.o : $(TESTS_DIR)/WorldCupTests.cpp
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) $(TESTS_DIR)/WorldCupTests.cpp -o $@

 # UPDATE FROM HERE

#$(O_FILES_DIR)/AVL_tree.o : AVL_tree.h NodeList_Teams.h
#	@mkdir -p $(O_FILES_DIR)
#	$(GPP) -c $(COMP_FLAG) AVL_tree.cpp -o $@

#nodelist
$(O_FILES_DIR)/NodeList_Teams.o : NodeList.cpp NodeList.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) NodeList_Teams.cpp -o $@

$(O_FILES_DIR)/Team.o : Team.cpp Team.h Player.h AVL_tree.h NodeList.h Exception.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) Team.cpp -o $@

$(O_FILES_DIR)/Player.o : Player.cpp Player.h Team.h AVL_tree.h NodeList.h Exception.h Team.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) Player.cpp -o $@

$(O_FILES_DIR)/worldcup23a1.o : worldcup23a1.cpp worldcup23a1.h wet1util.h AVL_tree.h NodeList.h Exception.h Team.h Player.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) worldcup23a1.cpp -o $@

#$(O_FILES_DIR)/developer_tests.o : developer_tests.cpp developer_tests.h worldcup23a1.h wet1util.h AVL_tree.h NodeList_Teams.h Exception.h Team.h Player.h
#	@mkdir -p $(O_FILES_DIR)
#	$(GPP) -c $(COMP_FLAG) developer_tests.cpp -o $@

 # UNTIL HERE
	

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)
