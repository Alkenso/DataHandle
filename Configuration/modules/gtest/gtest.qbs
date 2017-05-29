import qbs

Module {
    Depends {name : "cpp"}
    cpp.includePaths: [project.GTEST_INCLUDE_PATH]

    Properties {
        condition: product.type.contains("application")
        cpp.libraryPaths: [project.GTEST_LIB_PATH]
        cpp.staticLibraries: ["gtest", "gtest_main"]
    }
}