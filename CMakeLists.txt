cmake_minimum_required(VERSION 2.8.9)
project (MathSolver)
add_executable(MathSolver main.cpp Fraction.cpp Term.cpp Part.cpp Expression.cpp)
set_property(TARGET MathSolver PROPERTY CXX_STANDARD 20)