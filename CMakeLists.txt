cmake_minimum_required(VERSION 3.14)
project(lab-4-heuristic-search-DavidHoffman11)
set (EXE_NAME heuristic-search)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "")
set (input02 "")
set (input03 "")
set (input04 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp Algorithm.h RunTSP.cpp RunTSP.h GeneticAlgorithm.cpp GeneticAlgorithm.h SimulatedAnnealing.cpp SimulatedAnnealing.h Node.cpp Node.h DynamicProgramming.h DynamicProgramming.cpp NaiveBruteForce.h NaiveBruteForce.cpp)
#© 2020 GitHub, Inc.