TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    app/main.c \
    app/app.c \
    service/service_test.c \
    middle/drv_rs232.c

HEADERS += \
    app/app.h \
    func/tpos/tpos_data_type.h \
    service/service_test.h \
    middle/drv_rs232.h


CONFIG(debug,debug|release){
DEFINES += PC
LIBS += -lpthread
}else{
DEFINES += ARM
LIBS += -lpthread
}

INCLUDEPATH += \
    app/ \
    service/ \
    func/ \
    func/tpos/ \
    middle/
