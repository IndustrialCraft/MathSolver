add_library(MathSolver Fraction.cpp Term.cpp Variable.cpp Expression.cpp ExpressionPair.cpp ExpressionReader.cpp EquationSystem.cpp)

target_include_directories (MathSolver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})