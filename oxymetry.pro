QT += core gui widgets serialport

CONFIG += qwt
LIBS += -L$$PWD/./ -L$$PWD/./lib

CONFIG(32bit) {
    TARGET = oxymetry
    DEFINES += i686
    QMAKE_CXXFLAGS += -m32
    LIBS += -lavaspec -lqwt.dll -lusb-1.0.dll
}

CONFIG(64bit) {
    TARGET = oxymetry64
    DEFINES += amd64
    QMAKE_CXXFLAGS += -m64
    LIBS += -lavaspecx64 -lqwt64.dll -lusb-1.0-64.dll
}

TEMPLATE = app

INCLUDEPATH += $$PWD/./ $$PWD/./include

SOURCES += \
    main.cpp \
    application.cpp \
    messages.cpp \
    splash.cpp \
    spectrometer.cpp \
    spectrometer_config.cpp \
    spectrometer_eeprom.cpp \
    clickablelabel.cpp \
    plot.cpp \
    measurementstable.cpp \
    panel.cpp \
    panel_about.cpp \
    panel_item.cpp \
    panel_change_averages.cpp \
    panel_change_time.cpp \
    panel_legend.cpp \
    panel_storetoram.cpp \
    panel_timepattern.cpp \
    iad_configure.cpp \
    iad_configure_page01.cpp \
    iad_configure_page02.cpp \
    iad_calibrate.cpp \
    iad_calibrate_page01.cpp \
    iad_calibrate_page02.cpp \
    iad_calibrate_page03.cpp \
    iad_measure.cpp \
    math_helper.cpp \
    timer.cpp \
    fluidic_connect.cpp \
    fluidic_control.cpp \
    light_control.cpp

HEADERS += \
    application.h \
    messages.h \
    splash.h \
    spectrometer.h \
    spectrometer_config.h \
    spectrometer_eeprom.h \
    clickablelabel.h \
    plot.h \
    measurementstable.h \
    panel.h \
    panel_about.h \
    panel_item.h \
    panel_change_averages.h \
    panel_change_time.h \
    panel_legend.h \
    panel_storetoram.h \
    panel_timepattern.h \
    iad_configure.h \
    iad_configure_page01.h \
    iad_configure_page02.h \
    iad_calibrate.h \
    iad_calibrate_page01.h \
    iad_calibrate_page02.h \
    iad_calibrate_page03.h \
    iad_measure.h \
    math_helper.h \
    timer.h \
    fluidic_connect.h \
    fluidic_control.h \
    light_control.h

FORMS += \
    panel.ui \
    panel_about.ui \
    panel_item.ui \
    panel_change_averages.ui \
    panel_change_time.ui \
    panel_legend.ui \
    panel_storetoram.ui \
    panel_timepattern.ui \
    spectrometer_config.ui \
    spectrometer_eeprom.ui \
    iad_configure_page01.ui \
    iad_configure_page02.ui \
    iad_calibrate_page01.ui \
    iad_calibrate_page02.ui \
    iad_calibrate_page03.ui \
    fluidic_connect.ui \
    fluidic_control.ui \
    light_control.ui

DISTFILES += \
    oxymetry.rc

RC_FILE = oxymetry.rc

RESOURCES += \
    icons.qrc
