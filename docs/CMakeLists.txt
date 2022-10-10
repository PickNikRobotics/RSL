find_package(Doxygen REQUIRED)

set(DOXYGEN_GENERATE_TREEVIEW TRUE)
doxygen_add_docs(docs ${PROJECT_SOURCE_DIR}/include)
