#ifndef COMBOBOXEX_H
#define COMBOBOXEX_H
#pragma execution_character_set("utf-8")


#include<QComboBox>

class ComboBoxEx : public QComboBox
{

public:
    explicit ComboBoxEx(QWidget *parent = 0);

void adjustItemWidth();

};

#endif // COMBOBOXEX_H


