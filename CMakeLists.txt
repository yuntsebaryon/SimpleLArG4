cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

############ Make your changes here ############ 
project(LArG4)
set(useROOT true)
find_package(ROOT)
include_directories(/Users/yuntse/opt/root-master/include) 

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
 
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
 
#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(SimpleLArG4 SimpleLArG4.cc ${sources} ${headers})
if(useROOT)
	EXECUTE_PROCESS(OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND root-config --libs)
	set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
	message(${ROOT_LD_FLAGS})
endif(useROOT)
#Edited RR 6 Oct 2017
target_link_libraries(SimpleLArG4 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this example standalone
#
# add_custom_target(${myproj} DEPENDS ${myexe})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS SimpleLArG4 DESTINATION bin)
