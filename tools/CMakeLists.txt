cmake_minimum_required(VERSION 3.5)


add_executable(bt3_log_cat         bt_log_cat.cpp )
target_link_libraries(bt3_log_cat  ${BEHAVIOR_TREE_LIBRARY} )
install(TARGETS bt3_log_cat
        DESTINATION ${BEHAVIOR_TREE_BIN_DESTINATION} )



add_executable(bt3_plugin_manifest         bt_plugin_manifest.cpp )
target_link_libraries(bt3_plugin_manifest  ${BEHAVIOR_TREE_LIBRARY} )
install(TARGETS bt3_plugin_manifest
        DESTINATION ${BEHAVIOR_TREE_BIN_DESTINATION} )



