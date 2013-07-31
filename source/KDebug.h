/*
 * Copyright by yosh from Ke.mu Studio 2013
 * Contact y@ke.mu for questions
 */
#ifndef KDEBUG_H
#define KDEBUG_H

#define qDBG1() qDebug() << "[" << __FUNCTION__ << "]"
#define qDBGS1() qDBG() << "+++"
#define qDBGR1() qDBG() << "---"

#if defined(KDEBUG_ALL_ON)
    #define qDBG() qDBG1()
    #define qDBGS() qDBGS1()
    #define qDBGR() qDBGR1()
#else
    #define qDBG() QT_NO_QDEBUG_MACRO()
    #define qDBGS() QT_NO_QDEBUG_MACRO()
    #define qDBGR() QT_NO_QDEBUG_MACRO()
#endif

#endif // KDEBUG_H
