# this is the makefile for sample_report

KGUILOC=../../
include $(KGUILOC)/makefile.in

SRC=report.cpp

OBJ=$(SRC:%.cpp=$(OBJDIR)/%.o) # replaces the .cpp from SRC with .o

PROGRAM=report$(EXE)

DEP=makefile_$(OBJDIR).dep

$(OBJDIR)/%.o: %.cpp         # combined w/ next line will compile recently changed .cpp files
	$(CC) $(CCOPTS) $(SYS) $(KGUILIB_INCLUDES) -o $@ -c $<

.PHONY : all
all: $(PROGRAM)		# all is dependent on $(PROGRAM) to be complete

ifeq ($(SYS),-DMINGW)

RESOBJ=$(OBJDIR)/simpleres.o

$(RESOBJ): report.rc
	windres report.rc $(RESOBJ)

endif

$(PROGRAM): $(DEP) $(OBJ) $(RESOBJ) $(KGUILIB_DEP) # $(PROGRAM) is dependent on all of the files in $(OBJ) to exist
	$(LINK) $(RESOBJ) $(KGUILIB_LIBPATHS) $(OBJ) $(KGUILIB_LIBS) $(KGUILIB_SYSLIBS) $(LDFLAGS) -o $@

.PHONY : clean   # .PHONY ignores files named clean
clean:
	-$(RM) $(OBJ) $(RESOBJ) $(PROGRAM) $(DEP) # '-' causes errors not to exit the process

$(DEP):
	@echo "Generating Dependencies"
	mkdir -p $(OBJDIR)
	-$(CC) $(KGUILIB_INCLUDES) -E -MM $(SYS) $(CFLAGS) $(SRC) >>$(DEP)
	$(KGUILOC)$(OBJDIR)/fixdep$(EXE) $(DEP) $(OBJDIR)/
	

ifeq (,$(findstring clean,$(MAKECMDGOALS)))
-include $(DEP)
endif
