#  Copyright (c) 2014-2016 Hartmut Kaiser
#  Copyright (c) 2011 Thomas Heller
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_subdirectory(components)

set(tests
    action_invoke_no_more_than
    copy_component
    distribution_policy_executor
    get_gid
    get_ptr
    inheritance_2_classes_abstract
    inheritance_2_classes_concrete
    inheritance_3_classes_1_abstract
    inheritance_3_classes_2_abstract
    inheritance_3_classes_concrete
    launch_process
    local_new
    migrate_component
    migrate_component_to_storage
    new_
    new_binpacking
    new_colocated
    unordered_map
    partitioned_vector_view
    partitioned_vector_view_iterator
    partitioned_vector_subview
    coarray
    coarray_all_reduce
   )

if(HPX_WITH_EXECUTOR_COMPATIBILITY)
  set(tests ${tests}
      distribution_policy_executor_v1
     )
endif()

# add executable needed for launch_process_test
add_hpx_executable(launched_process_test
  SOURCES launched_process.cpp
  EXCLUDE_FROM_ALL
  HPX_PREFIX ${HPX_BUILD_PREFIX}
  FOLDER "Tests/Unit/Components"
  COMPONENT_DEPENDENCIES launch_process_test_server)

set(action_invoke_no_more_than_PARAMETERS
    THREADS_PER_LOCALITY 4)
set(action_invoke_no_more_than_FLAGS
    DEPENDENCIES iostreams_component)

set(colocated_distribution_policy_PARAMETERS
    LOCALITIES 2
    THREADS_PER_LOCALITY 2)

set(copy_component_PARAMETERS
    LOCALITIES 2
    THREADS_PER_LOCALITY 2)

set(get_ptr_PARAMETERS
    LOCALITIES 2
    THREADS_PER_LOCALITY 2)

set(launch_process_FLAGS
    DEPENDENCIES iostreams_component process_component
                 launch_process_test_server_component)
set(launch_process_PARAMETERS
  --launch=$<TARGET_FILE:launched_process_test_exe>
)

set(migrate_component_PARAMETERS
    LOCALITIES 2
    THREADS_PER_LOCALITY 2)
set(migrate_component_FLAGS
    DEPENDENCIES iostreams_component)

set(inheritance_2_classes_abstract_FLAGS
    DEPENDENCIES iostreams_component)

set(inheritance_2_classes_concrete_FLAGS
    DEPENDENCIES iostreams_component)

set(inheritance_3_classes_1_abstract_FLAGS
    DEPENDENCIES iostreams_component)

set(inheritance_3_classes_2_abstract_FLAGS
    DEPENDENCIES iostreams_component)

set(inheritance_3_classes_concrete_FLAGS
    DEPENDENCIES iostreams_component)

set(unordered_map_FLAGS
    DEPENDENCIES unordered_component)
set(unordered_map_PARAMETERS
    LOCALITIES 2
    THREADS_PER_LOCALITY 2)

set(migrate_component_to_storage_FLAGS
    DEPENDENCIES unordered_component component_storage_component)

set(new__PARAMETERS LOCALITIES 2)
set(new_binpacking_PARAMETERS LOCALITIES 2)
set(new_colocated_PARAMETERS LOCALITIES 2)

set(partitioned_vector_view_FLAGS DEPENDENCIES partitioned_vector_component)
set(partitioned_vector_view_PARAMETERS THREADS_PER_LOCALITY 4)

set(partitioned_vector_view_iterator_FLAGS DEPENDENCIES partitioned_vector_component)
set(partitioned_vector_view_iterator_PARAMETERS THREADS_PER_LOCALITY 4)

set(partitioned_vector_subview_FLAGS DEPENDENCIES partitioned_vector_component)
set(partitioned_vector_subview_PARAMETERS THREADS_PER_LOCALITY 4)

set(coarray_FLAGS DEPENDENCIES partitioned_vector_component)
set(coarray_PARAMETERS THREADS_PER_LOCALITY 4)

set(coarray_all_reduce_FLAGS DEPENDENCIES partitioned_vector_component)
set(coarray_all_reduce_PARAMETERS THREADS_PER_LOCALITY 4)

foreach(test ${tests})
  set(sources
      ${test}.cpp)

  source_group("Source Files" FILES ${sources})

  set(folder_name "Tests/Unit/Components")
  string(FIND ${test} "_v1" _is_v1_test)

  if(NOT (_is_v1_test EQUAL -1))
    set(folder_name "Tests/Unit/Components/V1")
  endif()

  # add example executable
  add_hpx_executable(${test}_test
                     SOURCES ${sources}
                     ${${test}_FLAGS}
                     EXCLUDE_FROM_ALL
                     HPX_PREFIX ${HPX_BUILD_PREFIX}
                     FOLDER ${folder_name})

  add_hpx_unit_test("components" ${test} ${${test}_PARAMETERS})

  # add a custom target for this example
  add_hpx_pseudo_target(tests.unit.component.${test})

  # make pseudo-targets depend on master pseudo-target
  add_hpx_pseudo_dependencies(tests.unit.component
                              tests.unit.component.${test})

  # add dependencies to pseudo-target
  add_hpx_pseudo_dependencies(tests.unit.component.${test}
                              ${test}_test_exe)

endforeach()

add_hpx_pseudo_dependencies(tests.unit.component.launch_process launched_process_test_exe)
