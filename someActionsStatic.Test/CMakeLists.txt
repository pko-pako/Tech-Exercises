include(GoogleTest)

enable_testing()

add_executable (actionsStatic.Test
  "main.cpp"
  "actionsSt.Test.cpp"
)

target_link_libraries(actionsStatic.Test PRIVATE actionsStatic actionsDynamic)

if(MSVC)
  add_custom_command(TARGET actionsStatic.Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:actionsStatic.Test> $<TARGET_FILE_DIR:actionsStatic.Test>
    COMMAND_EXPAND_LISTS
  )
endif()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(actionsStatic.Test PRIVATE GTest::gtest GTest::gmock)

gtest_discover_tests(actionsStatic.Test DISCOVERY_TIMEOUT 30)