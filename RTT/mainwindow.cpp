#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "seggerop.h"

#include "gfifo.h"
#include "comfunc_qt.h"
#include <QByteArray>

#include <QTextCodec>
#include <QSettings>

SeggerOp *pRtt;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pRtt = new SeggerOp();
//    QString str;
//    pRtt->load_dll_and_get_api(str, 2000);
//    this->op_show(str);
//    this->op_show("注意，卸载dll之后，才能使用keil下载程序\r\n");

    timer_rtt = new QTimer();
    QObject::connect(timer_rtt, &QTimer::timeout, this, &MainWindow::when_timer_rtt_timeout);
    timer_rtt->setSingleShot(true);


    QStringList items;

    items.clear();
    items << QString("20000000") << QString("自定义");
    ui->comboBox_RamBaseAddr->clear();
    ui->comboBox_RamBaseAddr->setInsertPolicy(QComboBox::NoInsert);//输入的内容不要自动保存
    ui->comboBox_RamBaseAddr->addItems(items);
    ui->comboBox_RamBaseAddr->setCurrentText("20000000");

    items.clear();
    items << "6" << "10" << "20" << "48" << "60" << "自定义";
    ui->comboBox_RamSize->clear();
    ui->comboBox_RamSize->setInsertPolicy(QComboBox::NoInsert);//输入的内容不要自动保存
    ui->comboBox_RamSize->addItems(items);
    ui->comboBox_RamSize->setCurrentText("20");
    ui->comboBox_RamSize->adjustItemWidth();

    this->save_or_restore_configure_file(false);


}

MainWindow::~MainWindow()
{
    this->save_or_restore_configure_file(true);
    delete ui;
}


void MainWindow::when_timer_rtt_timeout()
{
    static QByteArray ba;
    static QString str;

    if(!pRtt->api_is_available())//如果dll已被卸载
    {        
        timer_rtt->stop();
        this->op_show("dll已卸载，连接已断开");
        return;
    }
    if(!pRtt->seggerIsOpen()  || !pRtt->seggerIsConnect())
    {
        timer_rtt->stop();
        this->op_show("连接已断开");
        return;
    }

    timer_rtt->start(1);

    uint8_t buf[1000];
    int16_t real_len = pRtt->read_fifoUp_from_arm(buf, 1000);

    if(real_len > 0)
    {
        ba.clear();
        ba.append((const char*)buf, real_len);
        str.clear();
        str.append(ba);

        if(ui->checkBox_timeStamp->isChecked())
        {
            QString timeStamp = QString(" [%1:%2:%3.%4]\r")
                    .arg(QTime::currentTime().hour())
                    .arg(QTime::currentTime().minute(),2,10,(QChar)'0')
                    .arg(QTime::currentTime().second(),2,10,(QChar)'0')
                    .arg(QTime::currentTime().msec(),2,10,(QChar)'0');
            str.replace("\r", timeStamp);
        }
        ui->textBrowser_show->moveCursor(QTextCursor::End);
        ui->textBrowser_show->insertPlainText(str);
        ui->textBrowser_show->moveCursor(QTextCursor::End);

    }
}



void MainWindow::op_show(QString tipInfo)
{
    ui->textBrowser_show->moveCursor(QTextCursor::End);
    ui->textBrowser_show->append(tipInfo);
    ui->textBrowser_show->moveCursor(QTextCursor::End);
}



void MainWindow::on_action_help_triggered()
{
    QMessageBox::about(this,"帮助",
                      QString("注意：\r\n")+
                      + "1、只有断开连接以后，才能用keil下载程序或者在线调试\r\n"
                      + "2、MCU中的RTT驱动，必须与本上位机配套\r\n"
                      + "3、下位机发送的换行符必须是\\r或者\\r\\n，否则上位机无法添加时间戳\r\n"
                      + "\r\n--------------------------------2018.08.16 gyh 创建"
                      );
}

void MainWindow::on_pushButton_send_clicked()
{
    if(!pRtt->api_is_available())
    {
        this->op_show("未连接MCU");
        return;
    }

    QString input = ui->textEdit_input->toPlainText();
    int ret;
    uint16_t real_len;
    if(ui->checkBox_hex->isChecked())
    {
        uint8_t buf[1000];
        QString convert_info;

        ret = hex_str_to_byte_arr(input, buf, sizeof(buf), true, convert_info);
        if(ret < 0)
        {
            this->op_show("错误：" + convert_info);
            return;
        }
        real_len = pRtt->write_fifoDown_of_arm(buf, ret);
    }
    else
    {
        char*  ch;
        QByteArray ba = input.toLatin1(); // must
        ch=ba.data();
        ret = ba.size();
        real_len = pRtt->write_fifoDown_of_arm((uint8_t*)ch, ret);
    }

    if(ret == real_len)
    {
        this->op_show(QString("成功发送%1个字节").arg(real_len));
    }
    else
    {
        this->op_show(QString("输入的字节数=%1, 发出的字节数=%1").arg(ret).arg(real_len));
    }



    //qDebug("输入的字节数=%d， 发出的字节数=%d\r\n", ret, real_len);

}

void MainWindow::on_pushButton_link_clicked()
{
    QString str;
    if(!pRtt->api_is_available())
    {
        pRtt->load_dll_and_get_api(str);
        this->op_show(str);
    }
    bool ok;
    uint32_t arm_ram_base_addr = ui->comboBox_RamBaseAddr->currentText().toInt(&ok, 16);
    if(!ok)
    {
        this->op_show("错误：设置的RAM起始地址不是有效的十六进制数字");
        return;
    }
    uint32_t arm_ram_size = ui->comboBox_RamSize->currentText().toInt(&ok, 10);
    if(!ok)
    {
        this->op_show("错误：设置的RAM大小不是有效的十进制数字");
        return;
    }
    str.clear();
    if(true == pRtt->locateToArm(str, arm_ram_base_addr, arm_ram_size*1024))
    {
        timer_rtt->start();
    }

    this->op_show(str);
}

void MainWindow::on_pushButton_unlink_clicked()
{
    if(pRtt->unload_dll())
    {
        qDebug()<<"dll卸载成功";
    }
    else
    {
        qDebug()<<"dll无法卸载/";
    }
    this->op_show("已与MCU断开连接，keil可以使用jlink了");
}

void MainWindow::on_pushButton_clearShow_clicked()
{
    ui->textBrowser_show->clear();
}

void MainWindow::save_or_restore_configure_file(bool isSave)
{
    QSettings *IniFile = new QSettings("config.ini", QSettings::IniFormat);
    IniFile->setIniCodec("UTF-8"); ;
    QString RamBaseAddr_str, RamSize_str;
    if(isSave == true)
    {
        RamBaseAddr_str = ui->comboBox_RamBaseAddr->currentText();
        RamSize_str = ui->comboBox_RamSize->currentText();

        IniFile->setValue("RamBaseAddr", RamBaseAddr_str);
        IniFile->setValue("RamSize", RamSize_str);
        qDebug()<<"配置信息已保存";
    }
    else
    {
        RamBaseAddr_str = IniFile->value("RamBaseAddr",(QVariant)"20000000").toString();
        RamSize_str = IniFile->value("RamSize",(QVariant)"20").toString();
        ui->comboBox_RamBaseAddr->setCurrentText("自定义");
        ui->comboBox_RamBaseAddr->setCurrentText(RamBaseAddr_str);
        ui->comboBox_RamSize->setCurrentText("自定义");
        ui->comboBox_RamSize->setCurrentText(RamSize_str);
        qDebug()<<"配置信息已读出";
    }

    delete IniFile;
}

void MainWindow::on_comboBox_RamBaseAddr_currentIndexChanged(const QString &text)
{
    if(text == QString("自定义"))
    {
        ui->comboBox_RamBaseAddr->setEditable(true);
    }
    else
    {
        ui->comboBox_RamBaseAddr->setEditable(false);
    }
}

void MainWindow::on_comboBox_RamSize_currentIndexChanged(const QString &text)
{
    if(text == QString("自定义"))
    {
        ui->comboBox_RamSize->setEditable(true);
    }
    else
    {
        ui->comboBox_RamSize->setEditable(false);
    }
}

void MainWindow::on_pushButton_clearInput_clicked()
{

}
