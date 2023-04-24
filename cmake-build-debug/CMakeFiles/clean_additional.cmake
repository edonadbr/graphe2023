# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/graphe2023_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/graphe2023_autogen.dir/ParseCache.txt"
  "graphe2023_autogen"
  )
endif()
