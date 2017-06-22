import qbs

Module {
    Depends { name : "cpp" }
    cpp.treatWarningsAsErrors: true
    cpp.cxxLanguageVersion: "c++11"

    Properties {
        condition : qbs.targetOS.contains("darwin")
        cpp.minimumMacosVersion : "10.8"
        cpp.cxxFlags: ["-Wall", "-Wpedantic"]
    }

    Properties {
        condition : qbs.targetOS.contains("windows")
        cpp.cxxFlags: ["/W4"]
    }
}
