import qbs

Module {
    Depends { name : "cpp" }
    cpp.warningLevel: "all"
    cpp.treatWarningsAsErrors: true
    cpp.cxxLanguageVersion: "c++11"

    Properties {
        condition : qbs.targetOS.contains("darwin")
        cpp.minimumMacosVersion : "10.8"
    }
}
