RESOLV_SUDOKU := resolv_sudoku


all: $(RESOLV_SUDOKU)
.PHONY: $(RESOLV_SUDOKU)
 
CC:= gcc


PROJ_CFLAGS = -I./

PROJ_LIBS = 
				
PROJ_SRCS := main.c rs_global.c rs_function.c

PROJ_OBJS := $(filter %.o, $(patsubst %.c,%.o,$(PROJ_SRCS)) $(patsubst %.cpp,%.o,$(PROJ_SRCS)))	
PROJ_DEPS :=$(filter %.d, $(patsubst %.c,%.d,$(PROJ_SRCS)) $(patsubst %.cpp,%.d,$(PROJ_SRCS)))	

$(RESOLV_SUDOKU):  $(PROJ_OBJS)
	@${CC} $(PROJ_CFLAGS) -Wl,--start-group $(PROJ_OBJS) -Wl,--end-group -o $@

%.o: %.c
	@echo "Compiling:" $<...
	@$(CC) $(PROJ_CFLAGS) -c -MMD -MF $*.d $*.c -o $*.o

%.d: %.c
	@echo "Generating dependency:" $@...
	@$(CC) $(PROJ_CFLAGS) -MM -MT $*.o -MF $@ $<


-include $(PROJ_DEPS)	
	
clean:
	@rm -rf $(RESOLV_SUDOKU)
	@rm -rf $(PROJ_OBJS)
	@rm -rf $(PROJ_DEPS)
