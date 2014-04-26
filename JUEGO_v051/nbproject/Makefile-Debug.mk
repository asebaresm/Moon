#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc -ansi -pedantic
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Action.o \
	${OBJECTDIR}/DialogueXMLreader.o \
	${OBJECTDIR}/Inventory.o \
	${OBJECTDIR}/Link.o \
	${OBJECTDIR}/Object.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/Reglas_dialogo.o \
	${OBJECTDIR}/Set.o \
	${OBJECTDIR}/Space.o \
	${OBJECTDIR}/UtilCadena.o \
	${OBJECTDIR}/World.o \
	${OBJECTDIR}/WorldXMLReader.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=`xml2-config --cflags` 

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juego_v0.5

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juego_v0.5: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juego_v0.5 ${OBJECTFILES} ${LDLIBSOPTIONS} `xml2-config --libs`

${OBJECTDIR}/Action.o: Action.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Action.o Action.c

${OBJECTDIR}/DialogueXMLreader.o: DialogueXMLreader.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DialogueXMLreader.o DialogueXMLreader.c

${OBJECTDIR}/Inventory.o: Inventory.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Inventory.o Inventory.c

${OBJECTDIR}/Link.o: Link.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Link.o Link.c

${OBJECTDIR}/Object.o: Object.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Object.o Object.c

${OBJECTDIR}/Player.o: Player.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.c

${OBJECTDIR}/Reglas_dialogo.o: Reglas_dialogo.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Reglas_dialogo.o Reglas_dialogo.c

${OBJECTDIR}/Set.o: Set.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Set.o Set.c

${OBJECTDIR}/Space.o: Space.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Space.o Space.c

${OBJECTDIR}/UtilCadena.o: UtilCadena.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UtilCadena.o UtilCadena.c

${OBJECTDIR}/World.o: World.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World.o World.c

${OBJECTDIR}/WorldXMLReader.o: WorldXMLReader.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WorldXMLReader.o WorldXMLReader.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juego_v0.5

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
