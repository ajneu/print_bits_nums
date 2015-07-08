CC := gcc

SRCEXTS := .c
SRC_DIRS := src
SOURCES := $(foreach d,$(SRC_DIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))

INCLUDE_DIRS := include

LDLIBS := 



PROGRAM_NAME := prog


ifdef debug # e.g.     make debug=1
  PROGRAM_NAME := $(PROGRAM_NAME)Debug
  LDFLAGS := 
  OBJ_DIR := obj_debug
  CFLAGS := -g
else
  LDFLAGS := -s
  OBJ_DIR := obj
  CFLAGS := -O2
endif
# note: LDFLAGS is used in $(LINK.o)    -- do:  make -p > out.txt    ... to see this
# see http://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html for details on -g -s -O2 etc


BIN_DIR := bin
PROGRAM := $(addprefix $(BIN_DIR)/,$(PROGRAM_NAME))



# $(call object-file-name,src-file)
define object-file-name
 $(dir $1)$(OBJ_DIR)/$(basename $(notdir $1)).o
endef

OBJECTS := $(foreach f,$(SOURCES), $(call object-file-name,$(f)))
OBJ_SUBDIRS := $(sort $(dir $(OBJECTS)))




# $(call depend-file-name,object-file)
define depend-file-name
 $(dir $1)$(DEPEND_NAME)/$(basename $(notdir $1)).d
endef

DEPEND_NAME := depend
DEPEND_DIRS := $(addsuffix $(DEPEND_NAME),$(OBJ_SUBDIRS))
DEPENDENCIES := $(foreach f,$(OBJECTS), $(call depend-file-name,$(f)))



DIRS := $(OBJ_SUBDIRS) $(DEPEND_DIRS) $(BIN_DIR)



MKDIR := mkdir -p
_MKDIRS := $(shell $(MKDIR) $(DIRS))






CPPFLAGS += $(addprefix -I,$(INCLUDE_DIRS))

vpath %.c $(SRC_DIRS)
vpath %.h $(INCLUDE_DIRS)






# $(call make-depend,source-file,object-file,depend-file)
define make-depend
 $(CC)  -MM \
        -MF $3 \
        -MP \
        -MT $2 \
        $(CFLAGS) \
        $(CPPFLAGS) \
        $(TARGET_ARCH) \
        $1
endef



.SUFFIXES: 

.PHONY: all

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
# compare with:      make -p > out



# $(OBJ_NAME)/%.o: %.c
# 	$(call make-depend,$<,$@,$(call depend-file-name,$@))
# 	$(COMPILE.c) $(OUTPUT_OPTION) $<




# $(call compile-to-o,c-file,o-file)
define compile-to-o
	$(call make-depend,$1,$2,$(call depend-file-name,$2))
	$(COMPILE.c) $(OUTPUT_OPTION) $1
endef
# compare with:      make -p > out


$(foreach c_file,$(SOURCES),$(eval $(call object-file-name,$(c_file)): $(c_file) ; $$(call compile-to-o,$$<,$$@)))




ifneq "$(MAKECMDGOALS)" "clean"
 -include $(DEPENDENCIES)
endif



RM := rm -fr



.PHONY: clean
clean:
	$(RM) $(DIRS)
