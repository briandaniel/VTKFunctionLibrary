
# This cmake script builds a library of VTK functions 

# Standard cmake version requirement
cmake_minimum_required(VERSION 2.6)

# Inform user
MESSAGE("Configuring VTK function library.")

# Project (fortran must be enabled for OpenCMISS compatibility)
PROJECT( vtkFunctionLibrary LANGUAGES C CXX Fortran )

# Add all the local source files from the folder "src" to the makefile
file(GLOB_RECURSE VTK_FUNCTION_LIBRARY_CPP_SRC
	"*.hpp"
	"*.cpp"
)


#---- external packages ----#
# 1. MPI
find_package( MPI REQUIRED  ) 
include_directories(${MPI_INCLUDE_PATH})

# 2. VTK
find_package( VTK REQUIRED NO_MODULE ) 
include_directories(${VTK_INCLUDE_DIRS})
include(${VTK_USE_FILE})

# 3. Utility function library
# Add the paths to the utility function lib and include
find_library(UTILITYFUNCTION_LIBRARY_PATH utilityFunctionLibrary HINTS "${UtilityFunctionLibrary_INSTALL_DIR}/lib")
include_directories( ${UtilityFunctionLibrary_INSTALL_DIR}/include )


# Add the execubale using the source files in (src)
add_library(vtkFunctionLibrary SHARED
	${VTK_FUNCTION_LIBRARY_CPP_SRC}
)


#---- link and install ----#
# Set version
set_target_properties(vtkFunctionLibrary PROPERTIES SOVERSION 1)

# Link the local and external libraries to the executable
target_link_libraries( 
  vtkFunctionLibrary
  mpi
  mpi_cxx
  ${MPI_LIBRARIES}
  ${VTK_LIBRARIES}
  ${UTILITYFUNCTION_LIBRARY_PATH}
)

# Set the install location
install(TARGETS vtkFunctionLibrary
	LIBRARY DESTINATION lib
)
   
# Install the header files
INSTALL ( DIRECTORY ${CMAKE_SOURCE_DIR}/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  FILES_MATCHING PATTERN "*.hpp"
)

# Install the header files
INSTALL ( DIRECTORY ${CMAKE_SOURCE_DIR}/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  FILES_MATCHING PATTERN "*.h"
)




































