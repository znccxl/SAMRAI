set (sundials_sources
  main.C
  CVODEModel.C
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/FACjacobian2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/FACjacobian3d.f)

process_m4(NAME fortran/FACjacobian2d)
process_m4(NAME fortran/FACjacobian3d)


blt_add_executable(
  NAME sundials_test
  SOURCES ${sundials_sources}
  DEPENDS_ON
    SAMRAI_tbox
    SAMRAI_geom
    SAMRAI_mesh
    SAMRAI_hier
    SAMRAI_appu
    SAMRAI_solv)

target_include_directories( sundials_test
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/sundials)

target_compile_definitions(sundials_test PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME sundials_test
  EXECUTABLE sundials_test
  INPUTS ${test_inputs}
  PARALLEL TRUE)
