AUX_SOURCE_DIRECTORY(. BGMLISTDECODER_SRC)
ADD_EXECUTABLE(bgmlistdecoder ${BGMLISTDECODER_SRC})
ADD_DEPENDENCIES(bgmlistdecoder mir2x_3rds)

TARGET_INCLUDE_DIRECTORIES(bgmlistdecoder PRIVATE ${MIR2X_COMMON_SOURCE_DIR})
TARGET_INCLUDE_DIRECTORIES(bgmlistdecoder PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
TARGET_INCLUDE_DIRECTORIES(bgmlistdecoder PRIVATE ${CMAKE_CURRENT_LIST_DIR})

TARGET_LINK_LIBRARIES(bgmlistdecoder common)

INSTALL(TARGETS bgmlistdecoder DESTINATION tools/bgmlistdecoder)
