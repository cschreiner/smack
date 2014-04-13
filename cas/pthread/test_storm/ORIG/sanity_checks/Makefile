DRIVER_SRC = storm_check.c
HAVOC_DIR = $(STORM_ROOT)\havoc

# the makefile uses INCLUDE env flag to search for windows headers (windows.h, stdio.h, etc.)
# run vcvars32.bat from C:\Program Files\Microsoft Visual Studio 8\VC\bin\vcvars32.bat to set INCLUDE from command prompt

# comment this line to compile without havoc
#ANALYZE_OPT = /analyze:plugin $(HAVOC_INSTALL_DIR)\HavocFe.dll /analyze:log d.xml
ANALYZE_OPT = /analyze:plugin $(HAVOC_DIR)\EspFe.dll


# Shouldn't have to change anything below
SRC = $(DRIVER_SRC)

OBJ = $(SRC:.c=.obj)

DRIVER_OPT = /I. /I$(STORM_ROOT)\include /I$(HAVOC_DIR)\include

all: $(OBJ)

.c.obj: 
	cl $(ANALYZE_OPT) $(DRIVER_OPT) -c -nologo $<

clean:
	del *.obj* d.xml* *.blob *.cfg.files *.cg.files *.vfg.files espfe.dmp

