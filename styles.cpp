#include "styles.h"

void setStyles(QString stylesList[stylesAmount])
{
    //стили кнопок PushButton  в классе MainWindow
    stylesList[0] = "QPushButton {"
                    "   background-color: #4477e4;"
                    "   border: none;"
                    "   font-size:  16px;"
                    "   max-width: 200px;"
                    "   min-width: 80px;"
                    "   min-height: 20px;"
                    "   padding: 5px;"
                    "   color: #fff"
                    "}"
                    "QPushButton:disabled {"
                    "   background-color: #989898;"
                    "   color: #fff;"
                    " }"
                    "QPushButton:hover {"
                    "   background-color: #6696ef;"
                    " }"
                    "QPushButton:pressed {"
                    "   background-color: #54dff0;"
                    " }";

    //style for LineEdit
    stylesList[1] = "QLineEdit {"
                    "   background-color: #b02e45a3;"
                    "   border-radius: 3px;"
                    "   border: 2px solid #1e3593;"
                    "   font-size:  14px;"
                    "   max-width: 300px;"
                    "   min-width: 80px;"
                    "   min-height: 20px;"
                    "   padding: 3px;"
                    "   color: #fff;"

                    "}"
                    "QLineEdit:disabled {"
                    "   background-color: #5d7ab4;"
                    "   color: #fff;"
                    " }";

    //style for RadioButton
    stylesList[2] = "QRadioButton {"
                    "   color: #fff;"
                    "   font: 12px;"
                    "   cursor: pointer;"
                    "   }";

    //style for PushButton in Dialog window
    stylesList[3] = "QPushButton {"
                    "   color: #fff;"
                    "   background-color: #4477e4;"
                    "   border: none;"
                    "   font-size:  12px;"
                    "   max-width: 200px;"
                    "   min-width: 80px;"
                    "   min-height: 20px;"
                    "   padding: 5px;"
                    "}"
                    "QPushButton:hover {"
                    "   background-color: #6696ef;"
                    " }"
                    "QPushButton:pressed {"
                    "   background-color: #54dff0;"
                    " }";
}
