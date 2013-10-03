cmake_minimum_required(VERSION 2.6)
set(PROJECT "solitaire")
project(${PROJECT})

# Include glib
FIND_PACKAGE(GTK2 REQUIRED)



# Include OpenMP
FIND_PACKAGE(OpenMP) 

if (OPENMP_FOUND)
     set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
     set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}") 
endif()

# Require MPI for this project:
FIND_PACKAGE(MPI REQUIRED)

if (MPI_FOUND)
    set(CMAKE_CXX_COMPILE_FLAGS "${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS}")
    set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS}")
endif()


set(VAMPIR_ENABLE Ture)

IF(VAMPIR_ENABLE)
    message("[CONFIG] build program with vampir support")
    set(CMAKE_C_COMPILER "vtcc")
    set(CMAKE_CXX_COMPILER "vtc++")
    # Filter für Vampir !? (denke ich. enno)
#    set(CMAKE_CXX_INST_FILE_FILTER "stl,usr/include,libgpugrid,vector_types.h,Vector.hpp,DeviceBuffer.hpp,DeviceBufferIntern.hpp,Buffer.hpp,StrideMapping.hpp,StrideMappingMethods.hpp,MappingDescription.hpp,AreaMapping.hpp,AreaMappingMethods.hpp,ExchangeMapping.hpp,ExchangeMappingMethods.hpp,DataSpace.hpp,Manager.hpp,Manager.tpp,Transaction.hpp,Transaction.tpp,TransactionManager.hpp,TransactionManager.tpp,Vector.tpp,Mask.hpp,ITask.hpp,EventTask.hpp,EventTask.tpp,StandartAccessor.hpp,StandartNavigator.hpp,HostBuffer.hpp,HostBufferIntern.hpp")
#    set(CMAKE_CXX_INST_FUNC_FILTER "vector,Vector,dim3,GPUGrid,execute,allocator,Task,Manager,Transaction,Mask,operator,DataSpace,PitchedBox,Event,new,getGridDim,GetCurrentDataSpaces,MappingDescription,getOffset,getParticlesBuffer,getDataSpace,getInstance")
#    set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -vt:hyb -L/$ENV{VT_ROOT}/lib -finstrument-functions-exclude-file-list=${CMAKE_CXX_INST_FILE_FILTER} -finstrument-functions-exclude-function-list=${CMAKE_CXX_INST_FUNC_FILTER} -DVTRACE")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -vt:hyb -L/$ENV{VT_ROOT}/lib -finstrument-functions-exclude-file-list=${CMAKE_CXX_INST_FILE_FILTER} -finstrument-functions-exclude-function-list=${CMAKE_CXX_INST_FUNC_FILTER} -DVTRACE")

    
    set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -vt:hyb -L/$ENV{VT_ROOT}/lib -DVTRACE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -vt:hyb -L/$ENV{VT_ROOT}/lib -DVTRACE")
ENDIF(VAMPIR_ENABLE)




# Compiler definitions
add_definitions(-O2 -g -pedantic -Wall -Wextra -fopenmp -std=c99)

# Get source
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} SOURCE)

# Set additional include directories
include_directories(${GTK2_INCLUDE_DIRS} ${MPI_INCLUDE_PATH})

# Add executable
add_executable(${PROJECT} ${SOURCE})
target_link_libraries(${PROJECT} ${MPI_LIBRARIES} glib-2.0)

# Install
install(TARGETS ${PROJECT} DESTINATION bin)


