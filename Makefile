# maintools - small c++ library for application development.
# Copyright (C)2004 Sven Schoradt
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
#
# Contact by Mail via <sven@dex.de>.
#
.SUFFIXES: .cpp .h .o .l .y
.PHONY: tests clean clean_all clean_dep all lib FORCE

# set global definitions
CC = gcc
CPP = g++
LINKER = g++
LEX = flex
LEX_FLAGS = -l
YACC = bison
YACC_FLAGS = -d -v
CPP_FLAGS = -Wall -w -g -ggdb
LIBLINKER_FLAGS = -shared
LINKER_FLAGS = 
CPP_INCLUDES = -I.
CPP_DEFINES =
TAR = tar

DOXYGEN = doxygen

LIBRARYS = -L. -lmaintools

RM = rm -f
MKDIR = mkdir -p
MV = mv -f
TOUCH = touch

# set object path
POBJ = .obj

# stamps
PREPARE_STAMP = .prepare_stamp

# define subdirs to process
SUBDIRS = src include $(POBJ)
SUBDIRPATH = src:test

# define search pathes to source files
vpath %.cpp .:$(SUBDIRPATH)
vpath %.h   .:include
vpath %.l   .:$(SUBDIRPATH)
vpath %.y   .:$(SUBDIRPATH)
vpath %.o   $(POBJ)

# define include dirs
IDIRS = $(foreach DIR, $(SUBDIRS), -I$(DIR))
CPP_INCLUDES    += $(IDIRS)

# set more flags for compiler and linker
CPP_FLAGS 	+= -g
LINKER_FLAGS 	+= -g
CPP_INCLUDE     += 

# set the needed objects
# there should no 'main' function in these objects
OBJECTS = maintools.o arguments.o config_section.o config.o \
          config_scanner.yy.o

LIBNAME = maintools
LIBVERSION = 1

LIBSONAME = lib$(LIBNAME).so.$(LIBVERSION)
LIBLINKERNAME = lib$(LIBNAME).so

LIBLINKER_FLAGS += -Wl,-soname,$(LIBLINKERNAME)

# File for dependencies
DEPFILE = Makefile.depend

LIBOBJECTS = $(PREPARE_STAMP) $(OBJECTS:%=$(POBJ)/%)

#####################################################################

all: lib tests

objects: $(PREPARE_STAMP) $(OBJECTS:%=$(POBJ)/%)

#####################################################################

############################
# library building
############################
lib: $(LIBLINKERNAME)

$(LIBLINKERNAME): $(LIBSONAME)
	$(RM) $(LIBLINKERNAME)
	ln -s $(LIBSONAME) $(LIBLINKERNAME)

$(LIBSONAME): $(LIBOBJECTS)
	$(LINKER) $(LINKER_FLAGS) $(LIBLINKER_FLAGS) -o $@ $(OBJECTS:%=$(POBJ)/%)



############################
# cleaning
############################
clean:	clean_dep
	@echo -n "cleaning object files  ... "
	@$(RM) $(POBJ)/*.o
	@echo "DONE"
	@echo -n "cleaning all temporary editor files (*~) ... "
	@find . -name "*~" -exec $(RM) '{}' ';'
	@echo "DONE"

cleanall:	clean
	@echo -n "Deleting preparations ... "
	@$(RM) -r $(POBJ)
	@$(RM) $(PREPARE_STAMP)
	@echo "DONE"
	@echo -n "Deleting library ... "
	@$(RM) $(LIBLINKERNAME)
	@$(RM) $(LIBSONAME)
	@echo "DONE"
	@echo -n "Deleting test binary's ... "
	@$(RM) test_*.t
	@echo "DONE"

distclean:	cleanall clean_doc

#
# special cleanings
#

clean_dep: 
	@$(RM) $(DEPFILE)
	@find . -name '*.d' -exec $(RM) '{}' ';'

clean_doc:
	@echo -n "Deleting documentation ... "
	@$(RM) -r doc/code/html
	@$(RM) -r doc/code/latex
	@echo "DONE"

############################
# test cases
############################

TESTSRC = $(wildcard test/test_*.cpp)
TESTO = $(TESTSRC:test/%.cpp=$(POBJ)/%.o)
TESTS = $(TESTSRC:test/%.cpp=%.t)

tests:  $(TESTO) $(TESTS)

%.t:	$(POBJ)/%.o
	$(LINKER) $(LINKER_FLAGS) $(LIBRARYS) -o $@ $(POBJ)/$*.o

############################
# documentaion
############################

doc: maintools.doxy
	@echo -n "Generating documentaion ... "
	@$(DOXYGEN) $<
	@echo "DONE"


############################
# compiling instructions
############################

$(POBJ)/%.o: 	%.cpp
	$(CPP) $(CPP_FLAGS) $(CPP_INCLUDES) -c -o $@ $<

%.o: 	%.cpp
	$(CPP) $(CPP_FLAGS) $(CPP_INCLUDES) -c -o $@ $<

$(POBJ)/%.yy.cpp:   %.l
	$(LEX) $(LEX_FLAGS) -o$@ $<

$(POBJ)/%.tab.cpp:  %.y
	$(YACC) $(YACC_FLAGS) -o$@ $<

############################
# creating object path
############################

$(PREPARE_STAMP): 
	$(MKDIR) $(POBJ)
	$(TOUCH) $(PREPARE_STAMP)

############################
# creating dependencies of 
# all %.cpp files
############################

$(DEPFILE):	depend

depend:	$(PREPARE_STAMP) $(patsubst %.o, $(POBJ)/%.d, $(OBJECTS)) $(TESTSRC:test/%.cpp=$(POBJ)/%.d)
	@find . -name '*.d' -exec cat '{}' > $(DEPFILE) ';'

$(POBJ)/%.d:	%.cpp
	echo -n "$(POBJ)/" > $@; $(CPP) $(CPP_INCLUDES) $(CPP_FLAGS) -MM $< >> $@

FORCE:


.obj/schema.tab.d: .obj/schema.tab.cpp
	echo -n "$(POBJ)/" > $@; $(CPP) $(CPP_INCLUDES) $(CPP_FLAGS) -MM $< >> $@

.obj/config_scanner.yy.d: .obj/config_scanner.yy.cpp
	echo -n "$(POBJ)/" > $@; $(CPP) $(CPP_INCLUDES) $(CPP_FLAGS) -MM $< >> $@

include $(DEPFILE)



