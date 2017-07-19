import qbs
import qbs.FileInfo

Project {
    minimumQbsVersion: "1.6"
    qbsSearchPaths: ["Configuration"]

    property path GTEST_PATH: "/Users/alk/Dropbox/3rdPartySDK"
    property path GTEST_INCLUDE_PATH: FileInfo.joinPaths(GTEST_PATH, "include")
    property path GTEST_LIB_PATH: FileInfo.joinPaths(GTEST_PATH, "lib", qbs.buildVariant.contains("debug") ? "Debug" : "Release")

    StaticLibrary {
        name: "DataHandle"
        Depends { name : "BuildConfig" }
        Group {
            name : "Public Headers"
            files : ["*.h"]
            prefix : "DataHandle/include/DataHandle/"
        }

        Group {
            name : "Private Headers"
            files : ["*.h", "*.pch"]
            prefix : "DataHandle/include/DataHandle/internal/"
        }

        cpp.useCxxPrecompiledHeader : true
        FileTagger {
            patterns : "PrefixHeader.pch"
            fileTags : ["cpp_pch_src"]
        }

        Group {
            name : "Sources"
            files : ["*.cpp"]
            prefix : "DataHandle/src/"
        }

        cpp.includePaths : {
            var publicInc = FileInfo.joinPaths("DataHandle", "include")
            var projectInc = FileInfo.joinPaths(publicInc, "DataHandle")
            var projectInternalInc = FileInfo.joinPaths(projectInc, "internal")
            var inc = [publicInc, projectInc, projectInternalInc]
            return inc
        }

        Export {
               Depends {name : "cpp"}
               cpp.includePaths: FileInfo.joinPaths("DataHandle", "include")
           }
    }

    StaticLibrary {
        name: "DataHandleTests"
        Depends { name : "BuildConfig" }
        Depends { name : "DataHandle" }
        Depends { name : "gtest" }

        files: ["DataHandleTests/*"]

        cpp.includePaths : {
            var publicInc = FileInfo.joinPaths("DataHandle", "include")
            var projectInc = FileInfo.joinPaths(publicInc, "DataHandle")
            var projectInternalInc = FileInfo.joinPaths(projectInc, "internal")
            var inc = [publicInc, projectInc, projectInternalInc]
            return inc
        }

        cpp.useCxxPrecompiledHeader : true
        FileTagger {
            patterns : "PrefixHeader.pch"
            fileTags : ["cpp_pch_src"]
        }

        Properties {
            condition: qbs.targetOS.contains("darwin")
            cpp.cxxFlags: ["-Wno-sign-compare"]
        }
    }

    CppApplication {
        name: "DataHandleTestsRunner"
        Depends { name : "BuildConfig" }
        Depends { name : "DataHandleTests" }
        Depends { name : "gtest" }

        cpp.linkerFlags: ["-all_load"] // test this with other platforms

        consoleApplication: true
        files: ["DataHandleTestsRunner/*"]
    }
}
