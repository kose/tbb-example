## Copyright (C) 2018, 2020 KOSEKI Yoshinori

OPT = -DDEBUG
CXX = c++ -O3 -std=c++11 -march=native
CC = c++ -O3
CVDIR=/opt/intel/openvino/opencv
CVLIBS = -L$(CVDIR)/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio \
	-lopencv_video -lopencv_imgcodecs #-lopencv_dnn
CVFLAGS = -I$(CVDIR)/include

# Darwin or Raspbian
OS = $(shell uname)

ifeq ($(OS),Darwin)
	OPT := $(OPT) -DTBB_SUPPRESS_DEPRECATED_MESSAGES
	CFLAGS = $(CVFLAGS) -I/opt/local/include
	ADDLIBS = -L/opt/local/lib -ltbb #-lgflags -ltbb -lzmq
	ETAGS = /Applications/Emacs.app/Contents/MacOS/bin/etags
else
	OPT := $(OPT)
	CFLAGS = $(CVFLAGS)
	ADDLIBS = -ltbb -lpthread #-lgflags  -lzmq
	ETAGS = etags
endif

CPPFLAGS = $(OPT) $(CFLAGS)
LDLIBS = $(CVLIBS) $(ADDLIBS)

##
HEADERS = $(wildcard *.hpp)
SRC = $(wildcard *.cpp) $(wildcard lib/*.cpp)
OBJECTS = $(subst .cpp,.o,$(SRC))
EXE = edge-detect

all: depend $(EXE) TAGS

$(EXE): $(OBJECTS)

$(OBJECTS): Makefile

TAGS: $(SRC) $(HEADERS)
	$(ETAGS) $^

clean:
	rm -f $(OBJECTS) $(EXE) *~ TAGS depend

distclean: clean

##
## 依存関係は、gcc -MM *.cpp で自動生成。
##
-include depend

depend: $(SRC)
	$(CXX) -MM $(CPPFLAGS) $^ > $@

### Local Variables: ###
### truncate-lines:t ###
### End: ###
