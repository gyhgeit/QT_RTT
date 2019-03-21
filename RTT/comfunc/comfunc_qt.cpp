#include "comfunc_qt.h"




const QTextCodec *codec = QTextCodec::codecForName("GBK");

/*
 * 功能： 字节数组转换为带空格的hex字符串
 * 例如：输入ByteArray=
 *
 *
*/
QString byte_num_to_hex_string_with_space(const QByteArray &ByteArray)
{
   
    QString frame_hex_str = QString(ByteArray.toHex()).toUpper();

    for(int i= frame_hex_str.count()-2;i>=2;i-=2)
    {
        frame_hex_str.insert(i,' ');
    }
    return frame_hex_str;
}

/*
 * 功能： 字节数组转换为带空格的hex字符串
 * 例如：输入ByteArray=
*/
QString byte_num_to_hex_string_with_space(uint8 *data, int len)
{
    QString frame_hex_str;

    for(uint8 i=0;i<len;i++)
    {
        frame_hex_str += QString("%1 ").arg(data[i],2,16,(QChar)'0').toUpper();
    }
    return frame_hex_str;
}
/*
 * 功能： 字节数组转换为带空格的hex字符串，可设置转换后的方向
 * 例如：输入ByteArray=
*/
QString byte_num_to_hex_string_with_space(uint8 *data, int len, bool direction_is_forward)
{
    QString frame_hex_str;

    for(uint8 i=0;i<len;i++)
    {
        if(true == direction_is_forward)
        {
            frame_hex_str += QString("%1 ").arg(data[i],2,16,(QChar)'0').toUpper();
        }
        else
        {
            frame_hex_str += QString("%1 ").arg(data[len-1-i],2,16,(QChar)'0').toUpper();
        }

    }
    //qDebug()<<"数组转HEX字符串"<<frame_hex_str;
    return frame_hex_str;
}
/*
 * 功能： 字节数组转换为带空格的hex字符串,避免传参和传返回值产生开销
*/
void byte_num_to_hex_string_with_space(QString &frame_hex_str, void *data, int len)
{
    frame_hex_str.clear();
    for(int i=0;i<len;i++)
    {
        frame_hex_str += QString("%1 ").arg(((uint8_t*)data)[i],2,16,(QChar)'0').toUpper();
    }
}
/*
 * 功能：hex字符串转为字节数组，自动去除非hex字符
 * 参数：转换后的数组正向还是反向direction_is_forward=true
 * 返回：转换后的数组的长度，若出错，返回负值
 * 举例：若direction_is_forward=true，str="03 04AB 5f"，转换后byte_arr变为{0x03,0x04,0xAB,0x5F},返回4
 *      若direction_is_forward=false，str="03 04AB 5f"，转换后byte_arr变为{0x5f, 0xab, 0x04,0x03},返回4
 * 错误举例:1、str="03 04AB 5"有效的hex字符数量为奇数，不合法。
 * 2、str="03 04gB 5D"含有非HEX字符，不合法。
 * */
int hex_str_to_byte_arr(QString &str, uint8 *byte_arr, int buff_size, bool direction_is_forward)
{
    str.remove(QRegularExpression("[^0-9a-fA-F]"));//只保留HEX字符

    if(str.count()%2 != 0 )
        return -1;//有效的hex字符数量为奇数，非法
    int count = str.count()/2;
    if( count > buff_size)
        return -3;//缓冲区无法容纳转换后的数据

    //qDebug()<<"str数目="<<str.count();
    //qDebug()<<"字节数目="<<count;
    bool ok;

    for(int i=0;i<count;i++)
    {
        if(true == direction_is_forward)//正序
            byte_arr[i] = str.mid(i<<1,2).toInt(&ok, 16);
        else//倒序
            byte_arr[count-1-i] = str.mid(i<<1,2).toInt(&ok, 16);
        if(!ok)
            return -2;//含有非HEX字符,转换失败，因为前面已经删掉了所有非hex字符，所以，这里永远不会返回-2
    }

    return count;
}
/*
功能：与另一个重载函数略有不同，只会自动去除空格，非hex字符会输出错误信息
形参：前4个形参和另一个重载函数一样，最后一个形参不同：@err_info 输出错误信息
返回值：参考另一个同名函数
用法：
QString &err_str
if(-1 == hex_str_to_byte_arr(x,xx,x,x,x))
{
    print err_str;
}
*/
int hex_str_to_byte_arr(QString &str, uint8 *byte_arr, int buff_size, bool direction_is_forward, QString &err_info)
{
    //str.remove(QRegularExpression("[^0-9a-fA-F]"));//只保留HEX字符
    str.remove(QRegularExpression("[ \t\r\n\f\v]"));//删除空白字符，例如空格、tab、换行、换页符等
    str.simplified();
    if(str.count()%2 != 0 )
    {
        err_info = QString("有效的hex字符数量为奇数，无法转换");
        qDebug()<<err_info;
        return -1;
    }

    int count = str.count()/2;
    if( count > buff_size)
    {
        err_info = QString("缓冲区无法容纳转换后的数据, 请修改程序中的缓冲区容量以便支持更多的数据");
        return -3;//
    }

    //qDebug()<<"str数目="<<str.count();
    //qDebug()<<"字节数目="<<count;
    bool ok;

    for(int i=0;i<count;i++)
    {
        if(true == direction_is_forward)//正序
            byte_arr[i] = str.mid(i<<1,2).toInt(&ok, 16);
        else//倒序
            byte_arr[count-1-i] = str.mid(i<<1,2).toInt(&ok, 16);
        if(!ok)
        {
            err_info = dy_tr("含有非HEX字符,转换失败");
            return -2;
        }

    }

    return count;
}

void print_arr(void *arr, int len)
{
    QString str ;//= byte_num_to_hex_string_with_space((uint8 *)arr, len);
    byte_num_to_hex_string_with_space(str, arr, len);
    qDebug()<<str;
}



