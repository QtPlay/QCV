import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        Depends { name: "Qt.core" }
        Depends { name: "Qt.quick" }
        Depends { name: "Qt.multimedia" }

        // Additional import path used to resolve QML modules in Qt Creator's code model
        property pathList qmlImportPaths: []

        cpp.cxxLanguageVersion: "c++17"

        cpp.defines: [
            // The following define makes your compiler emit warnings if you use
            // any feature of Qt which as been marked deprecated (the exact warnings
            // depend on your compiler). Please consult the documentation of the
            // deprecated API in order to know how to port your code away from it.
            "QT_DEPRECATED_WARNINGS",

            // You can also make your code fail to compile if you use deprecated APIs.
            // In order to do so, uncomment the following line.
            // You can also select to disable deprecated APIs only up to a certain version of Qt.
            //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
        ]

        cpp.includePaths:[
            ".",
            "D:/DevelopmentKit/opencv/build/include",
            "D:/DevelopmentKit/range-v3"
        ]

        cpp.libraryPaths:[
            "D:/DevelopmentKit/opencv/build/x64/vc14/lib"
        ]

        cpp.cxxFlags:["-openmp"]

        Properties {
            condition: qbs.buildVariant.contains("debug")
            cpp.dynamicLibraries:"opencv_world330d"
        }

        Properties {
            condition: qbs.buildVariant.contains("release")
            cpp.dynamicLibraries:"opencv_world330"
        }

        cpp.dynamicLibraries:["-openmp"]

//        cpp.dynamicLibraries:"opencv_world330"

        files: [
            "imageshowitem.cpp",
            "imageshowitem.h",
            "imageshowrenderer.cpp",
            "imageshowrenderer.h",
            "main.cpp",
            "qml.qrc",
            "simageservice.cpp",
            "simageservice.h",
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }

        Group{
            name:"imgOperation"
            files: [
                "transformimage.cpp",
                "transformimage.h",
                "simage.cpp",
                "simage.h",
                "imagesplit.cpp",
                "imagesplit.h",
                "imageutil.cpp",
                "imageutil.h",
                "imageoperaparam.cpp",
                "imageoperaparam.h",
                "util.cpp",
                "util.h",
            ]
        }

        Group{
            name:"grayBinary"
            files: [
                "bopencvhandle.cpp",
                "bopencvhandle.h",
                "bostuopencvhandle.cpp",
                "bostuopencvhandle.h",
                "btriangleopencvhandle.cpp",
                "btriangleopencvhandle.h",
                "gopencvhandle.cpp",
                "gopencvhandle.h",
                "vgbhandle.cpp",
                "vgbhandle.h",
            ]
        }

        Group{
            name:"trimBorder"
            files: [
                "boundmattrimborder.cpp",
                "boundmattrimborder.h",
                "partitiontrimborder.cpp",
                "partitiontrimborder.h",
                "scannyerodetrimborder.cpp",
                "scannyerodetrimborder.h",
                "scannyerodiltrimborder.cpp",
                "scannyerodiltrimborder.h",
                "simplecannytrimborder.cpp",
                "simplecannytrimborder.h",
                "simpletrimborder.cpp",
                "simpletrimborder.h",
                "itrimingborder.cpp",
                "itrimingborder.h",
            ]
        }

        Group{
            name:"camera"
            files: [
                "camerafilter.cpp",
                "camerafilter.h",
                "camerafilterrunnable.cpp",
                "camerafilterrunnable.h",
            ]
        }

//        Group{
//            name:"undoGroup"
//            files:[
//            ]
//        }
    }
}
