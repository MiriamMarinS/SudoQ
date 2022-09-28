OUT = lib/alib.a
CC = g++
ODIR = obj
SDIR = src
INC = -I include/

_OBJS = sudo.o cell.o utils.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


$(ODIR)/%.o: $(SDIR)/%.cpp 
    $(CC) -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
    ar rvs $(OUT) $^

.PHONY: clean

clean:
    rm -f $(ODIR)/*.o $(OUT)