/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *camera_state;
    QLabel *label;
    QPushButton *if_right;
    QFrame *detect_state;
    QLabel *label_4;
    QPushButton *if_right_2;
    QFrame *img_tran_state;
    QLabel *label_5;
    QPushButton *if_right_3;
    QFrame *tran_state;
    QLabel *label_6;
    QPushButton *if_right_5;
    QFrame *other_state;
    QLabel *label_7;
    QPushButton *if_right_4;
    QFrame *none_state;
    QLabel *label_8;
    QPushButton *if_right_6;
    QSpacerItem *verticalSpacer;
    QPushButton *reopen_cam_button;
    QPushButton *re_trans_button;
    QPushButton *restart_button;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *viedo_area;
    QLabel *video_plays;
    QLabel *label_state;
    QLabel *label_video;
    QLabel *time_sum;
    QLCDNumber *lcdNumber;
    QTimeEdit *timeEdit;
    QToolButton *toolButton;
    QPushButton *camera_model;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(812, 612);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(640, 70, 160, 451));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        camera_state = new QFrame(verticalLayoutWidget);
        camera_state->setObjectName(QStringLiteral("camera_state"));
        camera_state->setFrameShape(QFrame::StyledPanel);
        camera_state->setFrameShadow(QFrame::Raised);
        label = new QLabel(camera_state);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 81, 21));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);
        if_right = new QPushButton(camera_state);
        if_right->setObjectName(QStringLiteral("if_right"));
        if_right->setGeometry(QRect(110, 10, 41, 21));

        verticalLayout->addWidget(camera_state);

        detect_state = new QFrame(verticalLayoutWidget);
        detect_state->setObjectName(QStringLiteral("detect_state"));
        detect_state->setFrameShape(QFrame::StyledPanel);
        detect_state->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(detect_state);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 10, 81, 21));
        label_4->setFont(font);
        if_right_2 = new QPushButton(detect_state);
        if_right_2->setObjectName(QStringLiteral("if_right_2"));
        if_right_2->setGeometry(QRect(110, 10, 41, 21));

        verticalLayout->addWidget(detect_state);

        img_tran_state = new QFrame(verticalLayoutWidget);
        img_tran_state->setObjectName(QStringLiteral("img_tran_state"));
        img_tran_state->setFrameShape(QFrame::StyledPanel);
        img_tran_state->setFrameShadow(QFrame::Raised);
        label_5 = new QLabel(img_tran_state);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 10, 71, 21));
        label_5->setFont(font);
        if_right_3 = new QPushButton(img_tran_state);
        if_right_3->setObjectName(QStringLiteral("if_right_3"));
        if_right_3->setGeometry(QRect(110, 10, 41, 21));

        verticalLayout->addWidget(img_tran_state);

        tran_state = new QFrame(verticalLayoutWidget);
        tran_state->setObjectName(QStringLiteral("tran_state"));
        tran_state->setFrameShape(QFrame::StyledPanel);
        tran_state->setFrameShadow(QFrame::Raised);
        label_6 = new QLabel(tran_state);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(0, 10, 101, 21));
        label_6->setFont(font);
        if_right_5 = new QPushButton(tran_state);
        if_right_5->setObjectName(QStringLiteral("if_right_5"));
        if_right_5->setGeometry(QRect(110, 10, 41, 21));

        verticalLayout->addWidget(tran_state);

        other_state = new QFrame(verticalLayoutWidget);
        other_state->setObjectName(QStringLiteral("other_state"));
        other_state->setFrameShape(QFrame::StyledPanel);
        other_state->setFrameShadow(QFrame::Raised);
        label_7 = new QLabel(other_state);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 10, 91, 21));
        label_7->setFont(font);
        if_right_4 = new QPushButton(other_state);
        if_right_4->setObjectName(QStringLiteral("if_right_4"));
        if_right_4->setGeometry(QRect(110, 10, 41, 21));

        verticalLayout->addWidget(other_state);

        none_state = new QFrame(verticalLayoutWidget);
        none_state->setObjectName(QStringLiteral("none_state"));
        none_state->setFrameShape(QFrame::StyledPanel);
        none_state->setFrameShadow(QFrame::Raised);
        label_8 = new QLabel(none_state);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 10, 61, 21));
        label_8->setFont(font);
        if_right_6 = new QPushButton(none_state);
        if_right_6->setObjectName(QStringLiteral("if_right_6"));
        if_right_6->setGeometry(QRect(110, 10, 41, 21));

        verticalLayout->addWidget(none_state);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        reopen_cam_button = new QPushButton(verticalLayoutWidget);
        reopen_cam_button->setObjectName(QStringLiteral("reopen_cam_button"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(reopen_cam_button->sizePolicy().hasHeightForWidth());
        reopen_cam_button->setSizePolicy(sizePolicy);
        reopen_cam_button->setSizeIncrement(QSize(10, 40));

        verticalLayout->addWidget(reopen_cam_button);

        re_trans_button = new QPushButton(verticalLayoutWidget);
        re_trans_button->setObjectName(QStringLiteral("re_trans_button"));
        sizePolicy.setHeightForWidth(re_trans_button->sizePolicy().hasHeightForWidth());
        re_trans_button->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(re_trans_button);

        restart_button = new QPushButton(verticalLayoutWidget);
        restart_button->setObjectName(QStringLiteral("restart_button"));
        sizePolicy.setHeightForWidth(restart_button->sizePolicy().hasHeightForWidth());
        restart_button->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(restart_button);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(30, 70, 576, 432));
        viedo_area = new QVBoxLayout(verticalLayoutWidget_2);
        viedo_area->setObjectName(QStringLiteral("viedo_area"));
        viedo_area->setContentsMargins(0, 0, 0, 0);
        video_plays = new QLabel(verticalLayoutWidget_2);
        video_plays->setObjectName(QStringLiteral("video_plays"));

        viedo_area->addWidget(video_plays);

        label_state = new QLabel(centralwidget);
        label_state->setObjectName(QStringLiteral("label_state"));
        label_state->setGeometry(QRect(660, 30, 131, 31));
        QFont font1;
        font1.setPointSize(15);
        label_state->setFont(font1);
        label_video = new QLabel(centralwidget);
        label_video->setObjectName(QStringLiteral("label_video"));
        label_video->setGeometry(QRect(210, 30, 201, 31));
        label_video->setFont(font1);
        time_sum = new QLabel(centralwidget);
        time_sum->setObjectName(QStringLiteral("time_sum"));
        time_sum->setGeometry(QRect(570, 540, 111, 21));
        QFont font2;
        font2.setFamily(QStringLiteral("aakar"));
        font2.setPointSize(12);
        time_sum->setFont(font2);
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(700, 540, 71, 21));
        timeEdit = new QTimeEdit(centralwidget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setGeometry(QRect(410, 540, 118, 26));
        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(40, 20, 71, 24));
        camera_model = new QPushButton(centralwidget);
        camera_model->setObjectName(QStringLiteral("camera_model"));
        camera_model->setGeometry(QRect(10, 510, 131, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 812, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", " Camera", Q_NULLPTR));
        if_right->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Detection", Q_NULLPTR));
        if_right_2->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Tracking", Q_NULLPTR));
        if_right_3->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "   Data Trans", Q_NULLPTR));
        if_right_5->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Video Trans", Q_NULLPTR));
        if_right_4->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Other", Q_NULLPTR));
        if_right_6->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
        reopen_cam_button->setText(QApplication::translate("MainWindow", "Restart Camera", Q_NULLPTR));
        re_trans_button->setText(QApplication::translate("MainWindow", "Reconect", Q_NULLPTR));
        restart_button->setText(QApplication::translate("MainWindow", "Reboot", Q_NULLPTR));
        video_plays->setText(QString());
        label_state->setText(QApplication::translate("MainWindow", "Moudle  State", Q_NULLPTR));
        label_video->setText(QApplication::translate("MainWindow", "Video Playback Area", Q_NULLPTR));
        time_sum->setText(QApplication::translate("MainWindow", "Runing Time", Q_NULLPTR));
        toolButton->setText(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        camera_model->setText(QApplication::translate("MainWindow", "Camera Model", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
