#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#
# NO_SMDH: if set to anything, no SMDH file is generated.
# APP_TITLE is the name of the app stored in the SMDH file (Optional)
# APP_DESCRIPTION is the description of the app stored in the SMDH file (Optional)
# APP_AUTHOR is the author of the app stored in the SMDH file (Optional)
# ICON is the filename of the icon (.png), relative to the project folder.
#   If not set, it attempts to use one of the following (in this order):
#     - <Project name>.png
#     - icon.png
#     - <libctru folder>/default_icon.png
#---------------------------------------------------------------------------------
TARGET		:=	z26-3ds
BUILD		:=	build
SOURCES		:=	src
DATA		:=	data
INCLUDES	:=	src

APP_TITLE		:= z26 3ds
APP_DESCRIPTION	:= z26 3ds - ATARI 2600 emulator
APP_AUTHOR		:= NOP90

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard

CFLAGS	:=	-g -Wall -O2 -mword-relocations \
			-fomit-frame-pointer -ffast-math \
			$(ARCH) -DANSI_GCC

CFLAGS	+=	$(INCLUDE) -DARM11 

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
#CXXFLAGS	:= $(CFLAGS) -fno-rtti -std=gnu++11

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS	:=  -lz -lsf2d -lctru -lm

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(CTRULIB) 


#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:= $(CURDIR)/$(SOURCES)/z26.c \
	$(CURDIR)/$(SOURCES)/2600core.c		$(CURDIR)/$(SOURCES)/c_cpujam.c		$(CURDIR)/$(SOURCES)/palette.c \
	$(CURDIR)/$(SOURCES)/c_banks.c		$(CURDIR)/$(SOURCES)/pcx.c			$(CURDIR)/$(SOURCES)/c_soundq.c \
	$(CURDIR)/$(SOURCES)/gui_sort.c		$(CURDIR)/$(SOURCES)/c_pitfall2.c	$(CURDIR)/$(SOURCES)/c_starpath.c \
	$(CURDIR)/$(SOURCES)/c_tialine.c	$(CURDIR)/$(SOURCES)/carts.c		$(CURDIR)/$(SOURCES)/position.c	\
	$(CURDIR)/$(SOURCES)/text.c 		$(CURDIR)/$(SOURCES)/c_catchuppixels.c	$(CURDIR)/$(SOURCES)/c_trace.c \
	$(CURDIR)/$(SOURCES)/c_riot.c 		$(CURDIR)/$(SOURCES)/genclr.c		$(CURDIR)/$(SOURCES)/flip.c \
	$(CURDIR)/$(SOURCES)/c_tiasnd.c 	$(CURDIR)/$(SOURCES)/c_tiawrite.c	$(CURDIR)/$(SOURCES)/globals.c \
	$(CURDIR)/$(SOURCES)/cli.c			$(CURDIR)/$(SOURCES)/controls.c		$(CURDIR)/$(SOURCES)/c_init.c \
	$(CURDIR)/$(SOURCES)/pixcopy.c 		$(CURDIR)/$(SOURCES)/c_cpu.c		$(CURDIR)/$(SOURCES)/kidvid.c	\
	$(CURDIR)/$(SOURCES)/c_cpuhand.c	$(CURDIR)/$(SOURCES)/srv.c			$(CURDIR)/$(SOURCES)/video.c \
	$(CURDIR)/$(SOURCES)/guigame.c		$(CURDIR)/$(SOURCES)/guiinterface.c	$(CURDIR)/$(SOURCES)/guisound.c	\
	$(CURDIR)/$(SOURCES)/guitweaks.c	$(CURDIR)/$(SOURCES)/guiutil.c		$(CURDIR)/$(SOURCES)/guiabout.c	\
	$(CURDIR)/$(SOURCES)/guivideo.c	  	$(CURDIR)/$(SOURCES)/gui.c			$(CURDIR)/$(SOURCES)/guidebug.c	\
	$(CURDIR)/$(SOURCES)/guifilelist.c	$(CURDIR)/$(SOURCES)/sdlsound.c 	$(CURDIR)/$(SOURCES)/sdlmouse.c
	
# sdlicon.c	 

CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
			$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

#ifeq ($(strip $(ICON)),
#	icons := $(wildcard *.png)
#	ifneq (,$(findstring $(TARGET).png,$(icons)))
#		export APP_ICON := $(TOPDIR)/$(TARGET).png
#	else
#		ifneq (,$(findstring icon.png,$(icons)))
			export APP_ICON := $(TOPDIR)/icon.png
#		endif
#	endif
#else
#	export APP_ICON := $(TOPDIR)/$(ICON)
#endif

ifeq ($(strip $(NO_SMDH)),)
	export _3DSXFLAGS += --smdh=$(CURDIR)/$(TARGET).smdh
endif

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).3dsx $(OUTPUT).smdh $(TARGET).elf $(TARGET)-strip.elf $(TARGET).cia $(TARGET).3ds
#---------------------------------------------------------------------------------
$(TARGET)-strip.elf: $(BUILD)
	@$(STRIP) $(TARGET).elf -o $(TARGET)-strip.elf
#---------------------------------------------------------------------------------
cci: $(TARGET)-strip.elf
	@makerom -f cci -rsf resources/$(TARGET).rsf -target d -exefslogo -elf $(TARGET)-strip.elf -o $(TARGET).3ds
	@echo "built ... 3ds"
#---------------------------------------------------------------------------------
cia: $(TARGET)-strip.elf
	@makerom -f cia -o $(TARGET).cia -elf $(TARGET)-strip.elf -rsf resources/$(TARGET).rsf -icon resources/icon.bin -banner resources/banner.bin -exefslogo -target t
	@echo "built ... cia"
#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
ifeq ($(strip $(NO_SMDH)),)
$(OUTPUT).3dsx	:	$(OUTPUT).elf $(OUTPUT).smdh
else
$(OUTPUT).3dsx	:	$(OUTPUT).elf
endif

$(OUTPUT).elf	:	$(OFILES)

#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.ttf.o	:	%.ttf
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

# WARNING: This is not the right way to do this! TODO: Do it right!
#---------------------------------------------------------------------------------
%.vsh.o	:	%.vsh
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@python $(AEMSTRO)/aemstro_as.py $< ../$(notdir $<).shbin
	@bin2s ../$(notdir $<).shbin | $(PREFIX)as -o $@
	@echo "extern const u8" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"_end[];" > `(echo $(notdir $<).shbin | tr . _)`.h
	@echo "extern const u8" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" >> `(echo $(notdir $<).shbin | tr . _)`.h
	@echo "extern const u32" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(notdir $<).shbin | tr . _)`.h
	@rm ../$(notdir $<).shbin

-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
