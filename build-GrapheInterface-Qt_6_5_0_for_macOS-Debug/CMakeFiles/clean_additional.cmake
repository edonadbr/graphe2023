# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/GrapheInterface_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/GrapheInterface_autogen.dir/ParseCache.txt"
  "GrapheInterface_autogen"
  )
endif()
