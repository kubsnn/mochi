add_executable(TEST_mochi_app main.cpp
        services/device_service.cpp
        controllers/device_controller.cpp
        controllers/test_controller.cpp)

target_link_libraries(TEST_mochi_app PRIVATE mochi_lib)