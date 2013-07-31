/*
 * Copyright by yosh from Ke.mu Studio 2013
 * Contact y@ke.mu for questions
 */

#include "kmainwindow.h"
#include "ui_kmainwindow.h"

#include <QtWidgets>
#include <QWebFrame>

//#define KDEBUG_ALL_ON
#include "KDebug.h"

#define MULTI_LINE_STRING(a) #a

#define MAIL_CHECK_INTERVAL_MS (3 * 60 * 1000)

class KWebPage: public QWebPage
{
public:
    KWebPage(QObject * parent = 0)
        :QWebPage(parent) {};

protected:
    virtual void javaScriptConsoleMessage(const QString & message, int lineNumber, const QString & sourceID)
    {
        Q_UNUSED(lineNumber);
        Q_UNUSED(sourceID);
        qDebug() << "[JS]" << message;
    }
};

KMainWindow::KMainWindow(QWidget *parent) :
    QMainWindow(parent),
    isMailButton(false),
    isMailButtonClickingOn(true),
    timeOfLastMailCheck(1),
    ui(new Ui::KMainWindow)
{
    ui->setupUi(this);

    KWebPage* kWebPage = new KWebPage(); // TODO: never destroyed
    ui->mainWebView->setPage(kWebPage);

    QWebFrame* mainFrame = ui->mainWebView->page()->mainFrame();
    connect(mainFrame, SIGNAL(loadFinished(bool)), this, SLOT(onFrameLoadFinished(bool)));
    ui->mainWebView->load(QUrl("http://google.com"));
    log("Loading http://google.com ...");

    /* setup UI */
    ui->mailButtonDetected->setEnabled(false);
    ui->mailButtonDetected->setChecked(false);

    QTimer *timer1s = new QTimer(this); // TODO: never destroyed
    connect(timer1s, SIGNAL(timeout()), this, SLOT(onTimer1s()));
    timer1s->start(2000);
}

KMainWindow::~KMainWindow()
{
    delete ui;
}

void KMainWindow::onFrameLoadFinished(bool ok)
{
    Q_UNUSED(ok);
    qDBGS();

    log(QString("Frame load finished %1").arg(ok));

    checkForMailButton();
    uiUpdate();
}

void KMainWindow::uiUpdate()
{
    ui->mailButtonDetected->setChecked(isMailButton);
}

bool KMainWindow::checkForMailButton()
{
    QWebFrame* mainFrame = ui->mainWebView->page()->mainFrame();
    const char* theJavaScriptCodeToInject = MULTI_LINE_STRING(
        function checkForMailButton()
        {
            var rv = 0;
            var allSpans = document.getElementsByTagName("span");
            for (theSpan in allSpans)
            {
                if (allSpans[theSpan].innerHTML == "Check mail now")
                {
                    console.log("Found !!!");
                    rv = 1;
                }
            }
            return rv;
        }
        checkForMailButton();
    );
    QVariant jsReturn = mainFrame->evaluateJavaScript(theJavaScriptCodeToInject);

    isMailButton = (jsReturn != 0);

    return isMailButton;
}

void KMainWindow::onTimer1s()
{
    checkForMailButton();

    /* if we are able to "click" on webpage */
    if (isMailButton && isMailButtonClickingOn)
    {
        qint64 now = QDateTime::currentMSecsSinceEpoch();
        if (timeOfLastMailCheck == 0)
        {
            timeOfLastMailCheck = now;
            log("Mail-check timer started !");
        }

        if (now - timeOfLastMailCheck > MAIL_CHECK_INTERVAL_MS)
        {
            tryClickingMailCheck();
            timeOfLastMailCheck = 0;
            log("Mail-check timer = 0");
        }

        ui->uiNextCheckProgress->setRange(0, MAIL_CHECK_INTERVAL_MS);
        int progressValue = (int)(now - timeOfLastMailCheck);
        if (progressValue < 0) progressValue = 0;
        if (progressValue > MAIL_CHECK_INTERVAL_MS) progressValue = MAIL_CHECK_INTERVAL_MS;
        ui->uiNextCheckProgress->setValue(progressValue);
        log(QString("Waiting for next click. [%1 / %2]").arg(QString::number(progressValue), QString::number(MAIL_CHECK_INTERVAL_MS)));
    }
    else
    {
        ui->uiNextCheckProgress->setValue(0);
        log(QString("Waiting for \"Check mail now\" button to appear on website."));
    }
}

bool KMainWindow::tryClickingMailCheck()
{
    QWebFrame* mainFrame = ui->mainWebView->page()->mainFrame();
    const char* theJavaScriptCodeToInject = MULTI_LINE_STRING(
        function clickMailButton()
        {
            var rv = 0;
            var allSpans = document.getElementsByTagName("span");
            for (theSpan in allSpans)
            {
                if (allSpans[theSpan].innerHTML == "Check mail now")
                {
                    allSpans[theSpan].click();
                    console.log("Clicked !!!");
                    rv = 1;
                }
            }
            return rv;
        }
        clickMailButton();
    );
    log("Clicking Mail-Check-Button...");
    QVariant jsReturn = mainFrame->evaluateJavaScript(theJavaScriptCodeToInject);
    if (jsReturn != 0)
    {
        timeOfLastMailCheck = 0;
        log("Mail-Check-Button clicked successfully");
    }

    uiUpdate();
    return jsReturn != 0;
}

void KMainWindow::log(QString msg)
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    QString out("[" + QString::number(now) + "] ");
    ui->uiLog->append(out + msg);
}
