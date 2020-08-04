

CFLAGS=-I. 
CFLAGS+=$(shell grutinizer-config --cflags) 
CFLAGS+=$(shell root-config --cflags)


LIBS=$(shell grutinizer-config --all-libs --root) 
#LIBS+=$(shell root-config --libs)



OBJS= make_fsu.o  
OBJS+=check_pid.o 
OBJS+=check_time.o  
OBJS+=fill_tree.o  
OBJS+=output.o 
OBJS+=input.o  
OBJS+=save_output.o  
OBJS+=process_hits.o 



all: REDUCT

%.o: %.cxx
	g++ -c $< $(CFLAGS) 

REDUCT: $(OBJS) 
	g++ -o $@ $^ $(CFLAGS) $(LIBS) 



clean:
	rm -rf *.o
	rm -rf REDUCT





