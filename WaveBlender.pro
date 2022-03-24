TARGET = WaveBlender
TEMPLATE = app

include(../../Base/PatchImposterApp.pri)

HEADERS += \
    CvMapping.h \
    OverlayCv.h \
    PageChannel.h \
    PageOverview.h \
    RandomWalkTables.h \
    CustomTable.h \
    WaveBlender.h

SOURCES += \
    CvMapping.cpp \
    OverlayCv.cpp \
    PageChannel.cpp \
    PageOverview.cpp \
    RandomWalkTables.cpp \
    CustomTable.cpp \
    WaveBlender.cpp

