# Wave
# Makefile receipes file

include Makefile.conf
include Makefile.res

LIBRARIES	= $(addprefix $(SRC)/,$(filter %.a,$(SOURCE)))
SOURCE_C	= $(addprefix $(SRC)/,$(filter %.c,$(SOURCE)))
SOURCE_CXX	= $(addprefix $(SRC)/,$(filter %.cpp,$(SOURCE)))
DEPENDS_C	= $(addprefix $(OBJ)/,$(patsubst %.c,%.d,$(filter %.c,$(SOURCE))))
DEPENDS_CXX	= $(addprefix $(OBJ)/,$(patsubst %.cpp,%.d,$(filter %.cpp,$(SOURCE))))
OBJECT_C	= $(addprefix $(OBJ)/,$(patsubst %.c,%.o,$(filter %.c,$(SOURCE))))
OBJECT_CXX	= $(addprefix $(OBJ)/,$(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCE))))

$(TARGET): $(LIBRARIES) $(OBJECT_C) $(OBJECT_CXX)
	$(LD) -o "$@" $(OBJECT_C) $(OBJECT_CXX) $(LIBRARIES) $(LDFLAGS)

build: $(TARGET)

clean:
ifneq ($(DEPENDS_C),)
	$(RM) $(RMFLAGS) $(DEPENDS_C)
endif
ifneq ($(DEPENDS_CXX),)
	$(RM) $(RMFLAGS) $(DEPENDS_CXX)
endif
ifneq ($(OBJECT_C),)
	$(RM) $(RMFLAGS) $(OBJECT_C)
endif
ifneq ($(OBJECT_CXX),)
	$(RM) $(RMFLAGS) $(OBJECT_CXX)
endif

distclean: clean
ifneq ($(OBJ),)
	$(RMDIR) $(RMDIRFLAGS) $(OBJ)
endif
ifneq ($(TARGET),)
	$(RM) $(RMFLAGS) $(TARGET)
endif

rebuild: clean build

run: build
	$(TARGET)

-include $(DEPENDS_C)
-include $(DEPENDS_CXX)

$(OBJ)/%.d: $(SRC)/%.c
#	-cd . $(foreach d,$(subst /, ,${@D}), ; $(MKDIR) $(MKDIRFLAGS) $d 2> Makefile.err ;  $(RM) $(RMFLAGS) Makefile.err ; cd $d)
	-$(MKDIR) $(MKDIRFLAGS) "${@D}"
	$(CC) $(CFLAGS) -MM -MP -MF "$@" -MT "$(@:.d=.o)" "$<"

$(OBJ)/%.d: $(SRC)/%.cpp
#	-cd . $(foreach d,$(subst /, ,${@D}), ; $(MKDIR) $(MKDIRFLAGS) $d 2> Makefile.err ;  $(RM) $(RMFLAGS) Makefile.err ; cd $d)
	-$(MKDIR) $(MKDIRFLAGS) "${@D}"
	$(CXX) $(CXXFLAGS) -MM -MP -MF "$@" -MT "$(@:.d=.o)" "$<"

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)/%.d
	$(CC) $(CFLAGS) -c "$<" -o "$@"

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ)/%.d
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"

.PHONY: build clean depends distclean rebuild run
