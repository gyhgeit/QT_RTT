/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <comboboxex.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_testRTT;
    QAction *action_help;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame_4;
    QGridLayout *gridLayout_5;
    QLabel *label_3;
    ComboBoxEx *comboBox_RamBaseAddr;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    ComboBoxEx *comboBox_RamSize;
    QLabel *label_2;
    QLabel *label_4;
    QCheckBox *checkBox_timeStamp;
    QPushButton *pushButton_link;
    QPushButton *pushButton_unlink;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_clearShow;
    QTextBrowser *textBrowser_show;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox_hex;
    QPushButton *pushButton_clearInput;
    QPushButton *pushButton_send;
    QTextEdit *textEdit_input;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(585, 433);
        action_testRTT = new QAction(MainWindow);
        action_testRTT->setObjectName(QStringLiteral("action_testRTT"));
        action_help = new QAction(MainWindow);
        action_help->setObjectName(QStringLiteral("action_help"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_4);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(frame_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(15, 16777215));

        gridLayout_5->addWidget(label_3, 0, 0, 1, 1);

        comboBox_RamBaseAddr = new ComboBoxEx(frame_4);
        comboBox_RamBaseAddr->setObjectName(QStringLiteral("comboBox_RamBaseAddr"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_RamBaseAddr->sizePolicy().hasHeightForWidth());
        comboBox_RamBaseAddr->setSizePolicy(sizePolicy);
        comboBox_RamBaseAddr->setMinimumSize(QSize(73, 0));

        gridLayout_5->addWidget(comboBox_RamBaseAddr, 0, 1, 1, 1);


        gridLayout->addWidget(frame_4, 1, 1, 1, 1);

        frame = new QFrame(frame_2);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        comboBox_RamSize = new ComboBoxEx(frame);
        comboBox_RamSize->setObjectName(QStringLiteral("comboBox_RamSize"));
        comboBox_RamSize->setMaximumSize(QSize(40, 16777215));

        gridLayout_4->addWidget(comboBox_RamSize, 0, 1, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_4->addWidget(label_4, 0, 2, 1, 1);


        gridLayout->addWidget(frame, 2, 1, 1, 1);

        checkBox_timeStamp = new QCheckBox(frame_2);
        checkBox_timeStamp->setObjectName(QStringLiteral("checkBox_timeStamp"));

        gridLayout->addWidget(checkBox_timeStamp, 3, 1, 1, 1);

        pushButton_link = new QPushButton(frame_2);
        pushButton_link->setObjectName(QStringLiteral("pushButton_link"));
        pushButton_link->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(pushButton_link, 4, 1, 1, 1);

        pushButton_unlink = new QPushButton(frame_2);
        pushButton_unlink->setObjectName(QStringLiteral("pushButton_unlink"));
        pushButton_unlink->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(pushButton_unlink, 5, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 6, 1, 1, 1);

        pushButton_clearShow = new QPushButton(frame_2);
        pushButton_clearShow->setObjectName(QStringLiteral("pushButton_clearShow"));
        pushButton_clearShow->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(pushButton_clearShow, 7, 1, 1, 1);

        textBrowser_show = new QTextBrowser(frame_2);
        textBrowser_show->setObjectName(QStringLiteral("textBrowser_show"));

        gridLayout->addWidget(textBrowser_show, 0, 0, 8, 1);


        gridLayout_3->addWidget(frame_2, 0, 0, 1, 1);

        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMaximumSize(QSize(10000, 120));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        checkBox_hex = new QCheckBox(frame_3);
        checkBox_hex->setObjectName(QStringLiteral("checkBox_hex"));

        gridLayout_2->addWidget(checkBox_hex, 1, 1, 1, 1);

        pushButton_clearInput = new QPushButton(frame_3);
        pushButton_clearInput->setObjectName(QStringLiteral("pushButton_clearInput"));
        pushButton_clearInput->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(pushButton_clearInput, 2, 1, 1, 1);

        pushButton_send = new QPushButton(frame_3);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setMinimumSize(QSize(108, 30));

        gridLayout_2->addWidget(pushButton_send, 3, 1, 1, 1);

        textEdit_input = new QTextEdit(frame_3);
        textEdit_input->setObjectName(QStringLiteral("textEdit_input"));
        textEdit_input->setMinimumSize(QSize(0, 100));
        textEdit_input->setMaximumSize(QSize(10000, 10000));

        gridLayout_2->addWidget(textEdit_input, 0, 0, 4, 1);


        gridLayout_3->addWidget(frame_3, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 585, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(action_help);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RTT\344\270\212\344\275\215\346\234\272  (\345\217\257\345\214\271\351\205\215segger v5.02\357\274\214\345\205\266\344\275\231\347\211\210\346\234\254\346\234\252\346\265\213\350\257\225)", Q_NULLPTR));
        action_testRTT->setText(QApplication::translate("MainWindow", "RTT\346\265\213\350\257\225", Q_NULLPTR));
        action_help->setText(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "RAM\350\265\267\345\247\213\345\234\260\345\235\200:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "0x", Q_NULLPTR));
        comboBox_RamBaseAddr->clear();
        comboBox_RamBaseAddr->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "20000000", Q_NULLPTR)
        );
        comboBox_RamSize->clear();
        comboBox_RamSize->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211", Q_NULLPTR)
        );
        comboBox_RamSize->setCurrentText(QApplication::translate("MainWindow", "64", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "RAM\345\244\247\345\260\217:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", " KB", Q_NULLPTR));
        checkBox_timeStamp->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\346\210\263", Q_NULLPTR));
        pushButton_link->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245MCU", Q_NULLPTR));
        pushButton_unlink->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_clearShow->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\346\230\276\347\244\272", Q_NULLPTR));
        checkBox_hex->setText(QApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", Q_NULLPTR));
        pushButton_clearInput->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\345\217\221\351\200\201", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
