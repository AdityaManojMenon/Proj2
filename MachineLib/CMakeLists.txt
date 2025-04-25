project(MachineLib)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

set(SOURCE_FILES
        pch.h
        IMachineSystem.h
        MachineSystemFactory.cpp MachineSystemFactory.h
        MachineDialog.cpp MachineDialog.h
        MachineSystemStandin.h MachineSystemStandin.cpp
        MachineStandin.cpp MachineStandin.h
        Polygon.cpp Polygon.h
        Machine.cpp Machine.h
        MachineSystem.cpp MachineSystem.h
        Component.cpp Component.h
        Motor.cpp Motor.h
        Pulley.cpp Pulley.h
        Shape.cpp Shape.h
        Source.cpp Source.h
        Sink.cpp Sink.h
        MachineFactory1.cpp MachineFactory1.h
        MachineFactory2.cpp MachineFactory2.h
        Bubble.cpp Bubble.h
        BubbleBlower.cpp BubbleBlower.h
        Const.cpp Const.h
        FlappingBelt.cpp FlappingBelt.h
)



find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
