QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_class.cpp \
    admin.cpp \
    main.cpp \
    mainwindow.cpp \
    course_info.cpp \
    login.cpp \
    messagebox.cpp \
    registered.cpp \
    reminder.cpp \
    searchwindow.cpp \
    searchwindow2.cpp \
    func/jsoncpp.cpp \
    src/affairslist.cpp \
    src/schedule.cpp \
    src/clock.cpp \
    Qguide.cpp \
    src/log.cpp \
    $$files("guide/*.cpp",true)

HEADERS += \
    add_class.h \
    admin.h \
    mainwindow.h \
    course_info.h \
    messagebox.h \
    registered.h \
    reminder.h \
    searchwindow.h \
    searchwindow2.h \
    login.h \
    func/json/json.h \
    func/json/json-forwards.h \
    func/hashmap.h \
    func/vector.h \
    func/trie.h \
    func/usertrie.h \
    src/affairslist.h \
    src/schedule.h \
    func/trie.h \
    src/clock.h \
    func/mysort.h \
    func/queue.h \
    Qguide.h \
    src/log.h

FORMS += \
    add_class.ui \
    admin.ui \
    mainwindow.ui \
    course_info.ui \
    login.ui \
    messagebox.ui \
    registered.ui \
    reminder.ui \
    searchwindow.ui \
    qguide.ui \
    searchwindow2.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
