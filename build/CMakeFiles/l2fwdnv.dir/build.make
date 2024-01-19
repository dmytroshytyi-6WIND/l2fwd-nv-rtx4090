# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/l2fwd-nv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/l2fwd-nv/build

# Include any dependencies generated for this target.
include CMakeFiles/l2fwdnv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/l2fwdnv.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/l2fwdnv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/l2fwdnv.dir/flags.make

CMakeFiles/l2fwdnv.dir/src/kernel.cu.o: CMakeFiles/l2fwdnv.dir/flags.make
CMakeFiles/l2fwdnv.dir/src/kernel.cu.o: CMakeFiles/l2fwdnv.dir/includes_CUDA.rsp
CMakeFiles/l2fwdnv.dir/src/kernel.cu.o: /home/ubuntu/l2fwd-nv/src/kernel.cu
CMakeFiles/l2fwdnv.dir/src/kernel.cu.o: CMakeFiles/l2fwdnv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu/l2fwd-nv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CUDA object CMakeFiles/l2fwdnv.dir/src/kernel.cu.o"
	/usr/local/cuda-12.3/bin/nvcc -forward-unknown-to-host-compiler $(CUDA_DEFINES) $(CUDA_INCLUDES) $(CUDA_FLAGS) -MD -MT CMakeFiles/l2fwdnv.dir/src/kernel.cu.o -MF CMakeFiles/l2fwdnv.dir/src/kernel.cu.o.d -x cu -c /home/ubuntu/l2fwd-nv/src/kernel.cu -o CMakeFiles/l2fwdnv.dir/src/kernel.cu.o

CMakeFiles/l2fwdnv.dir/src/kernel.cu.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CUDA source to CMakeFiles/l2fwdnv.dir/src/kernel.cu.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CUDA_CREATE_PREPROCESSED_SOURCE

CMakeFiles/l2fwdnv.dir/src/kernel.cu.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CUDA source to assembly CMakeFiles/l2fwdnv.dir/src/kernel.cu.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CUDA_CREATE_ASSEMBLY_SOURCE

CMakeFiles/l2fwdnv.dir/src/main.cpp.o: CMakeFiles/l2fwdnv.dir/flags.make
CMakeFiles/l2fwdnv.dir/src/main.cpp.o: /home/ubuntu/l2fwd-nv/src/main.cpp
CMakeFiles/l2fwdnv.dir/src/main.cpp.o: CMakeFiles/l2fwdnv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu/l2fwd-nv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/l2fwdnv.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/l2fwdnv.dir/src/main.cpp.o -MF CMakeFiles/l2fwdnv.dir/src/main.cpp.o.d -o CMakeFiles/l2fwdnv.dir/src/main.cpp.o -c /home/ubuntu/l2fwd-nv/src/main.cpp

CMakeFiles/l2fwdnv.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/l2fwdnv.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/l2fwd-nv/src/main.cpp > CMakeFiles/l2fwdnv.dir/src/main.cpp.i

CMakeFiles/l2fwdnv.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/l2fwdnv.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/l2fwd-nv/src/main.cpp -o CMakeFiles/l2fwdnv.dir/src/main.cpp.s

CMakeFiles/l2fwdnv.dir/src/utils.cpp.o: CMakeFiles/l2fwdnv.dir/flags.make
CMakeFiles/l2fwdnv.dir/src/utils.cpp.o: /home/ubuntu/l2fwd-nv/src/utils.cpp
CMakeFiles/l2fwdnv.dir/src/utils.cpp.o: CMakeFiles/l2fwdnv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu/l2fwd-nv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/l2fwdnv.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/l2fwdnv.dir/src/utils.cpp.o -MF CMakeFiles/l2fwdnv.dir/src/utils.cpp.o.d -o CMakeFiles/l2fwdnv.dir/src/utils.cpp.o -c /home/ubuntu/l2fwd-nv/src/utils.cpp

CMakeFiles/l2fwdnv.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/l2fwdnv.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/l2fwd-nv/src/utils.cpp > CMakeFiles/l2fwdnv.dir/src/utils.cpp.i

CMakeFiles/l2fwdnv.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/l2fwdnv.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/l2fwd-nv/src/utils.cpp -o CMakeFiles/l2fwdnv.dir/src/utils.cpp.s

CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o: CMakeFiles/l2fwdnv.dir/flags.make
CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o: /home/ubuntu/l2fwd-nv/src/pipeline.cpp
CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o: CMakeFiles/l2fwdnv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu/l2fwd-nv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o -MF CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o.d -o CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o -c /home/ubuntu/l2fwd-nv/src/pipeline.cpp

CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/l2fwd-nv/src/pipeline.cpp > CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.i

CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/l2fwd-nv/src/pipeline.cpp -o CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.s

# Object files for target l2fwdnv
l2fwdnv_OBJECTS = \
"CMakeFiles/l2fwdnv.dir/src/kernel.cu.o" \
"CMakeFiles/l2fwdnv.dir/src/main.cpp.o" \
"CMakeFiles/l2fwdnv.dir/src/utils.cpp.o" \
"CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o"

# External object files for target l2fwdnv
l2fwdnv_EXTERNAL_OBJECTS =

l2fwdnv: CMakeFiles/l2fwdnv.dir/src/kernel.cu.o
l2fwdnv: CMakeFiles/l2fwdnv.dir/src/main.cpp.o
l2fwdnv: CMakeFiles/l2fwdnv.dir/src/utils.cpp.o
l2fwdnv: CMakeFiles/l2fwdnv.dir/src/pipeline.cpp.o
l2fwdnv: CMakeFiles/l2fwdnv.dir/build.make
l2fwdnv: CMakeFiles/l2fwdnv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ubuntu/l2fwd-nv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable l2fwdnv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/l2fwdnv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/l2fwdnv.dir/build: l2fwdnv
.PHONY : CMakeFiles/l2fwdnv.dir/build

CMakeFiles/l2fwdnv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/l2fwdnv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/l2fwdnv.dir/clean

CMakeFiles/l2fwdnv.dir/depend:
	cd /home/ubuntu/l2fwd-nv/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/l2fwd-nv /home/ubuntu/l2fwd-nv /home/ubuntu/l2fwd-nv/build /home/ubuntu/l2fwd-nv/build /home/ubuntu/l2fwd-nv/build/CMakeFiles/l2fwdnv.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/l2fwdnv.dir/depend

