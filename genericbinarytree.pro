QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
CONFIG+= staticlib
OBJECTS_DIR = temp/
MOC_DIR = $$OBJECTS_DIR
RCC_DIR = $$OBJECTS_DIR
UI_DIR = $$OBJECTS_DIR


SOURCES += view/textposition.cpp

HEADERS  +=  model/genericnode.h \
    model/genericnodeimplementation.h \
    view/textposition.h \
    view/treeviewer.h \
    view/treeviewerimplementation.h

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    README.md
