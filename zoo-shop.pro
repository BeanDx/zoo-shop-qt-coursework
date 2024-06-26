QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminpanel.cpp \
    authorizationwindow.cpp \
    cartwindow.cpp \
    create_accountwindow.cpp \
    createproduct.cpp \
    load_images.cpp \
    main.cpp \
    mainwindow.cpp \
    productitem.cpp

HEADERS += \
    UserSession.h \
    adminpanel.h \
    authorizationwindow.h \
    cartwindow.h \
    create_accountwindow.h \
    createproduct.h \
    dbconnection.h \
    load_images.h \
    mainwindow.h \
    productitem.h

FORMS += \
    adminpanel.ui \
    authorizationwindow.ui \
    cartwindow.ui \
    create_accountwindow.ui \
    createproduct.ui \
    mainwindow.ui \
    productitem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
