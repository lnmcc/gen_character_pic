CFLAGS += -std=c99 -g -Wall
LDFLAGS += -lGL -lglut

genPic: genPic.o saveBmp.o
	cc  -o genPic  genPic.o saveBmp.o $(CFLAGS) $(LDFLAGS)
genPic.o: genPic.c
	cc  -c  genPic.c $(CFLAGS) $(LDFLAGS)
saveBmp.o: saveBmp.c
	cc -c saveBmp.c $(CFLAGS) $(LDFLAGS)
clean:
	rm -rf *.o genPic
