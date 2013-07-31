# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += \
    KMainApp.cpp \
    kmainwindow.cpp

OTHER_FILES +=

HEADERS += \
    KDebug.h \
    kmainwindow.h

FORMS += \
    kmainwindow.ui

# manual changes by yosh
QT += widgets webkitwidgets

