QT += core gui widgets serialport

CONFIG += qwt
LIBS += -L$$PWD/./ -L$$PWD/./lib
TEMPLATE = app

DEFINES += amd64
QMAKE_CXXFLAGS += -m64
LIBS += -lavaspecx64 -lqwt64.dll -lusb-1.0-64.dll -lfftw3-3.dll

INCLUDEPATH += $$PWD/./ $$PWD/./include

DESTDIR = $$PWD/./bin
UI_DIR = $$PWD/./build

CONFIG(debug, debug|release) {
        TARGET = oxymetry64
        OBJECTS_DIR = $$PWD/./build/debug
        MOC_DIR = $$PWD/./build/debug
}

CONFIG(release, debug|release) {
        TARGET = oxymetry64
        OBJECTS_DIR = $$PWD/./build/release
        MOC_DIR = $$PWD/./build/release
}

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
    panel_item_polarimeter.cpp \
    panel_change_averages.cpp \
    panel_change_time.cpp \
    panel_legend.cpp \
    panel_storetoram.cpp \
    panel_timepattern.cpp \
    panel_polarimeter.cpp \
    iad_configure.cpp \
    iad_configure_page01.cpp \
    iad_configure_page02.cpp \
    iad_calibrate.cpp \
    iad_calibrate_page01.cpp \
    iad_calibrate_page02.cpp \
    iad_calibrate_page03.cpp \
    iad_measure.cpp \
    fft.cpp \
    math_helper.cpp \
    timer.cpp \
    fluidic_connect.cpp \
    fluidic_control.cpp \
    light_control.cpp \
    panel_change_Wave_FFT.cpp \
    configure_Polarimeter_Measure.cpp

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
    panel_item_polarimeter.h \
    panel_change_averages.h \
    panel_change_time.h \
    panel_legend.h \
    panel_storetoram.h \
    panel_timepattern.h \
    panel_polarimeter.h \
    iad_configure.h \
    iad_configure_page01.h \
    iad_configure_page02.h \
    iad_calibrate.h \
    iad_calibrate_page01.h \
    iad_calibrate_page02.h \
    iad_calibrate_page03.h \
    iad_measure.h \
    fft.h \
    math_helper.h \
    timer.h \
    fluidic_connect.h \
    fluidic_control.h \
    light_control.h \
    panel_change_Wave_FFT.h \
    configure_Polarimeter_Measure.h

FORMS += \
    panel.ui \
    panel_about.ui \
    panel_item.ui \
    panel_item_pol.ui \
    panel_change_averages.ui \
    panel_change_time.ui \
    panel_legend.ui \
    panel_storetoram.ui \
    panel_timepattern.ui \
    panel_polarimeter.ui \
    spectrometer_config.ui \
    spectrometer_eeprom.ui \
    iad_configure_page01.ui \
    iad_configure_page02.ui \
    iad_calibrate_page01.ui \
    iad_calibrate_page02.ui \
    iad_calibrate_page03.ui \
    fluidic_connect.ui \
    fluidic_control.ui \
    light_control.ui \
    panel_change_Wave_FFT.ui \
    configure_Polarimeter_Measure.ui

DISTFILES += \
    oxymetry.rc

RC_FILE = oxymetry.rc

RESOURCES += \
    icons.qrc
