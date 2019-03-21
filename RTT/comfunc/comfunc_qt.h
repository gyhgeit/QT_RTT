#ifndef COMFUNC_QT_H
#define COMFUNC_QT_H
#pragma execution_character_set("utf-8")

//#include "comfunc_qt.h"
#include <qglobal.h>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QRegularExpression>
#include <stdio.h>
#include <stdint.h>
#include <QTextCodec>
#include "comfunc.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


#define uint8 quint8

#define TR(str)   (QString::fromLocal8Bit(str))  //源文件编码为非UTF8时，将其转换为正确的QString
//#define TR2(str)   (QString::fromUtf8(str))
//#define TR3(str)   (QStringLiteral(str))
extern const QTextCodec *codec;
#define dy_tr(...)   codec->toUnicode(__VA_ARGS__)  //动态转换dynamic trans,返回值为QString，例如串口读出的中文字串、用户输入的中文路径等
#define dy_tr2(...)   codec->fromUnicode(__VA_ARGS__).data()  //动态转换dynamic trans,返回值为char*，例如串口读出的中文字串、用户输入的中文路径等


QString byte_num_to_hex_string_with_space(const QByteArray &ByteArray);
QString byte_num_to_hex_string_with_space(uint8 *data, int len);
QString byte_num_to_hex_string_with_space(uint8 *data, int len, bool direction_is_forward);
void byte_num_to_hex_string_with_space(QString &frame_hex_str, void *data, int len);
int hex_str_to_byte_arr(QString &str, uint8 *byte_arr, int buff_size, bool direction_is_forward);
int hex_str_to_byte_arr(QString &str, uint8 *byte_arr, int buff_size, bool direction_is_forward, QString &err_str);
quint64 get_le_val(void * p, uint8_t bytes);
quint64 get_be_val(uint8_t * p, uint8_t bytes);
void print_arr(void *arr, int len);

#endif // COMFUNC_H
