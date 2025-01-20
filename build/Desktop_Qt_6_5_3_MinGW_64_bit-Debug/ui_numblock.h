/********************************************************************************
** Form generated from reading UI file 'numblock.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMBLOCK_H
#define UI_NUMBLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NumBlock
{
public:
    QLabel *number;

    void setupUi(QWidget *NumBlock)
    {
        if (NumBlock->objectName().isEmpty())
            NumBlock->setObjectName("NumBlock");
        NumBlock->resize(100, 100);
        number = new QLabel(NumBlock);
        number->setObjectName("number");
        number->setGeometry(QRect(20, 20, 60, 60));
        QFont font;
        font.setPointSize(15);
        number->setFont(font);
        number->setAlignment(Qt::AlignCenter);

        retranslateUi(NumBlock);

        QMetaObject::connectSlotsByName(NumBlock);
    } // setupUi

    void retranslateUi(QWidget *NumBlock)
    {
        NumBlock->setWindowTitle(QCoreApplication::translate("NumBlock", "Form", nullptr));
        number->setText(QCoreApplication::translate("NumBlock", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NumBlock: public Ui_NumBlock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMBLOCK_H
