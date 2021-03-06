# CMakeLists for proccontrol/gcc/64/stat/pic/none
set (CMAKE_C_FLAGS "${MUTATOR_DEFINES}  ${CFLAGS} ${MUTATEE_CFLAGS_GNU}  -m64 -g -O0 -fPIC")
set (CMAKE_C_FLAGS_DEBUG "")
set (CMAKE_C_FLAGS_RELEASE "")
set (CMAKE_C_FLAGS_RELWITHDEBINFO "")
set (CMAKE_C_COMPILER "${M_gnu_cc}")
include_directories("${PROJECT_SOURCE_DIR}/testsuite/src")
include_directories("${PROJECT_SOURCE_DIR}/testsuite/src/proccontrol")
add_definitions(-DSOLO_MUTATEE)
set (CMAKE_EXE_LINKER_FLAGS "${MUTATEE_LDFLAGS_GNU} -m64 -static")
IF (NOT ${M_gnu_cc} MATCHES "NOTFOUND")
CHECK_MUTATEE_COMPILER ("${M_gnu_cc}"
	"${MUTATOR_DEFINES}  ${CFLAGS} ${MUTATEE_CFLAGS_GNU}  -m64 -g -O0 -fPIC"
	"${MUTATEE_LDFLAGS_GNU} -m64 -static"
	"C"
	"gnu_cc 64 stat"
	MUTATEEgnucc64statC)

IF (MUTATEEgnucc64statC MATCHES "1")
include (${PROJECT_SOURCE_DIR}/ppc64_linux/srclists.cmake)
add_executable (pc_breakpoint.stat_gcc_64_pic_none ${SOURCE_LIST_34})
foreach (f ${SOURCE_LIST_34})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_breakpoint.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_breakpoint.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_detach.stat_gcc_64_pic_none ${SOURCE_LIST_12})
foreach (f ${SOURCE_LIST_12})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_detach.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_detach.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_fork.stat_gcc_64_pic_none ${SOURCE_LIST_0})
foreach (f ${SOURCE_LIST_0})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_fork.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_fork.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_fork_exec.stat_gcc_64_pic_none ${SOURCE_LIST_53})
foreach (f ${SOURCE_LIST_53})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_fork_exec.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_fork_exec.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_groups.stat_gcc_64_pic_none ${SOURCE_LIST_40})
foreach (f ${SOURCE_LIST_40})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_groups.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_groups.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_irpc.stat_gcc_64_pic_none ${SOURCE_LIST_68})
foreach (f ${SOURCE_LIST_68})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_irpc.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_irpc.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_launch.stat_gcc_64_pic_none ${SOURCE_LIST_44})
foreach (f ${SOURCE_LIST_44})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_launch.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_launch.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_singlestep.stat_gcc_64_pic_none ${SOURCE_LIST_31})
foreach (f ${SOURCE_LIST_31})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_singlestep.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_singlestep.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_stat.stat_gcc_64_pic_none ${SOURCE_LIST_10})
foreach (f ${SOURCE_LIST_10})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_stat.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_stat.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_temp_detach.stat_gcc_64_pic_none ${SOURCE_LIST_5})
foreach (f ${SOURCE_LIST_5})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_temp_detach.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_temp_detach.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_terminate.stat_gcc_64_pic_none ${SOURCE_LIST_27})
foreach (f ${SOURCE_LIST_27})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_terminate.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_terminate.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_terminate_stopped.stat_gcc_64_pic_none ${SOURCE_LIST_51})
foreach (f ${SOURCE_LIST_51})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_terminate_stopped.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_terminate_stopped.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_thread.stat_gcc_64_pic_none ${SOURCE_LIST_39})
foreach (f ${SOURCE_LIST_39})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_thread.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_thread.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_thread_cont.stat_gcc_64_pic_none ${SOURCE_LIST_20})
foreach (f ${SOURCE_LIST_20})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_thread_cont.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_thread_cont.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
add_executable (pc_tls.stat_gcc_64_pic_none ${SOURCE_LIST_58})
foreach (f ${SOURCE_LIST_58})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(pc_tls.stat_gcc_64_pic_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (pc_tls.stat_gcc_64_pic_none ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})


INSTALL (TARGETS
		pc_breakpoint.stat_gcc_64_pic_none
		pc_detach.stat_gcc_64_pic_none
		pc_fork.stat_gcc_64_pic_none
		pc_fork_exec.stat_gcc_64_pic_none
		pc_groups.stat_gcc_64_pic_none
		pc_irpc.stat_gcc_64_pic_none
		pc_launch.stat_gcc_64_pic_none
		pc_singlestep.stat_gcc_64_pic_none
		pc_stat.stat_gcc_64_pic_none
		pc_temp_detach.stat_gcc_64_pic_none
		pc_terminate.stat_gcc_64_pic_none
		pc_terminate_stopped.stat_gcc_64_pic_none
		pc_thread.stat_gcc_64_pic_none
		pc_thread_cont.stat_gcc_64_pic_none
		pc_tls.stat_gcc_64_pic_none
	DESTINATION ${INSTALL_DIR})

ENDIF()
ENDIF()
