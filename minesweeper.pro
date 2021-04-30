QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

CONFIG += c++11

TARGET = VideoMinesweeper

DESTDIR = $$_PRO_FILE_PWD_/
OBJECTS_DIR = $$_PRO_FILE_PWD_/Objects

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/matrix.cpp \
    Sources/tile.cpp

HEADERS += \
    Headers/mainwindow.h \
    Headers/matrix.h \
    Headers/tile.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

INCLUDEPATH += /usr/include/opencv4

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_shape -lopencv_videoio -lopencv_imgproc
