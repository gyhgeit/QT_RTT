#include "comboboxex.h"
#include<QAbstractItemView>
#include<QListView>
#include<Qdebug>
#include<QString>

ComboBoxEx::ComboBoxEx(QWidget *parent):
    QComboBox(parent)
{
    this->setView(new QListView());//提供样式表支持:QComboBox QAbstractItemView::item {height:20px;}

    QString styleSheet_str =
        "QComboBox QAbstractItemView {\
           border: 1px solid blue;\
           selection-background-color: red;\
           font: 9pt \"宋体\";\
        }\
        QComboBox QAbstractItemView::item {\
           height:18px;\
        }";
    this->setStyleSheet(styleSheet_str);
//rgb(134, 183, 255)
}
void ComboBoxEx::adjustItemWidth()
{
    int max_len=0;
    for(int idx=0;idx < this->count();idx++)
    {
        if(max_len < this->itemText(idx).toUtf8().size())
            max_len = this->itemText(idx).toUtf8().size();

    }

    int pt_val = this->font().pointSize();//获取字体的磅值
    //qDebug()<<"max_len="<<max_len<<",font="<<pt_val;

    this->view()->setFixedWidth(max_len*pt_val*0.75);//（字符数*每个字符的宽度(磅)*0.75）个像素
}
