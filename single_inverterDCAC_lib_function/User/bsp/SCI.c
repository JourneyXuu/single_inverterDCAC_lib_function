
#include "DSP28x_Project.h"
#include "SCI.h"
#include <string.h>
#include <stdint.h>

UART_STRUCT Scia_Handle;
UART_STRUCT Scib_Handle;

/**************************************
 * 测试程序
 * 添加UART串口打印数据功能
 * UARTInit(9600);
 * ***********************************/

void UART_Init(unsigned long Baud_Rate)
{
    unsigned int Baud = 0;
    Baud = (90000000/4/8/Baud_Rate)-1;

    EALLOW;
    /*引脚初始化*/
    //UART
    //GPIO28 <-> A-RX    //GPIO15 <-> B-RX
    //GPIO12 <-> A-TX    //GPIO58 <-> B-TX
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;//使能上拉
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;//使能上拉
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;//使能上拉
    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;//使能上拉
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;//配置为
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;

    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;//复用为ATX
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;//复用为BRX
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;//复用为ARX
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 2;//复用为BRX

    GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;//TX 配置为输出
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;//RX 配置为输出
    GpioDataRegs.GPACLEAR.bit.GPIO7=1;//清除锁存
    GpioDataRegs.GPACLEAR.bit.GPIO12=1;
    /*SCIA初始化*/
    SciaRegs.SCICCR.bit.STOPBITS = 0;//1位结束位
    SciaRegs.SCICCR.bit.PARITYENA = 0;//取消奇偶校验
    SciaRegs.SCICCR.bit.SCICHAR = 0x07;//8位长度位

    SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;//通讯模式：0：空闲模式 1：地址模式
    SciaRegs.SCICTL1.bit.RXENA = 0x1;//使能RX接收端
    SciaRegs.SCICTL1.bit.TXENA = 0x1;//使能TX发送端
    SciaRegs.SCIHBAUD = Baud >> 8;//设置波特率 (60M/4/BAUD/8)-1 103 124
    SciaRegs.SCILBAUD = Baud & 0XFF;
    SciaRegs.SCICTL1.bit.SWRESET = 0x1;

    SciaRegs.SCIFFTX.all = 0XE040;//FIFO配置
    SciaRegs.SCIFFRX.all = 0X2040;
    SciaRegs.SCIPRI.bit.SOFT = 1;//软件仿真完成发送或接收后可暂停
    /*SCIB初始化*/
    ScibRegs.SCICCR.bit.STOPBITS = 0;//1位结束位
    ScibRegs.SCICCR.bit.PARITYENA = 0;//取消奇偶校验
    ScibRegs.SCICCR.bit.SCICHAR = 0x07;//8位长度位

    ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0;//通讯模式：0：空闲模式 1：地址模式
    ScibRegs.SCICTL1.bit.RXENA = 0x1;//使能RX接收端
    ScibRegs.SCICTL1.bit.TXENA = 0x1;//使能TX发送端
    ScibRegs.SCIHBAUD = Baud >> 8;//设置波特率 (90M/4/BAUD/8)-1 123
    ScibRegs.SCILBAUD = Baud & 0XFF;
    ScibRegs.SCICTL1.bit.SWRESET = 0x1;

    ScibRegs.SCIFFTX.all = 0XE040;//FIFO配置
    ScibRegs.SCIFFRX.all = 0X2040;
    ScibRegs.SCIPRI.bit.SOFT = 1;//软件仿真完成发送或接收后可暂停

    EDIS;
    /*结构体变量初始化*/
    memset(&Scia_Handle,0,sizeof(UART_STRUCT));
    memset(&Scib_Handle,0,sizeof(UART_STRUCT));
    Scia_Handle.SCI_P = &SciaRegs;
    Scib_Handle.SCI_P = &ScibRegs;

    ////////////////////串口调试////////////////////
    Scib_Handle.Tx_Buffer[0] = 0X03;Scib_Handle.Tx_Buffer[1] = 0XFC;Scib_Handle.Tx_Buffer[6] = 0XFC;Scib_Handle.Tx_Buffer[7] = 0X03;
}

/***************************
 * 串口发送单个字节
 * Send_Char:需要发送的字符
 * 示例：//Uart_Send_Byte(0XAA);
 ****************************/
void Uart_Send_Byte(unsigned char Send_Char)
{
    if (SciaRegs.SCICTL2.bit.TXEMPTY == 1)//发送寄存器为空
    {
        SciaRegs.SCICTL1.bit.TXWAKE = 1;
        SciaRegs.SCITXBUF = Send_Char;
    }
}

/*串口FIFO接收函数*/
unsigned int Uart_Read(volatile struct SCI_REGS* SCI_STR,char *Buf)
{
    //unsigned int Long;//返回长度

    if(SCI_STR->SCIFFRX.bit.RXFFST != 0)//FIFO中有数据
    {
        *Buf = SCI_STR->SCIRXBUF.bit.RXDT;//取出数据
    }
    return 0;//可返回长度
}
/*串口FIFO发送函数*/
void Uart_Send(volatile struct SCI_REGS* SCI_STR,Uint16 *Buf)
{
    if(SCI_STR->SCIFFTX.bit.TXFFST < 4)//发送FIFO 有空余
    {
        SCI_STR->SCITXBUF = *Buf;//写入数据
    }
}

/************************************************
 * 串口发送字符串
 * Str：字符串首地址 Leng：字符串长度 Time:发送间隔
 * 示例：Uart_Send_Str(Uart_Tx.Tx_Buffer,4,200);
 * **********************************************/
void Uart_Send_Str(unsigned int* Str,unsigned char Leng,unsigned int Time)
{
    /*
    static unsigned char Str_Leng;

    if(++Uart_Tx.Send_Cnt >= Time)//调整发送间隔
    {
        if(!Uart_Tx.Send_Flag)
        {
            Uart_Tx.Send_Flag = 1;
            Uart_Tx.Send_Cnt = 0;
        }
    }

    //Uart_Tx.Tx_Buffer[3] = (((unsigned int)Mppt_Handle.Vpv)>>8) & 0xff;//低位在前 高位 高位再后
    //Uart_Tx.Tx_Buffer[2] = ((unsigned int)Mppt_Handle.Vpv) & 0xff;

    Uart_Tx.Tx_Buffer[5] = (((unsigned int)Sys_State.Ctr_Value.Phase)>>8) & 0xff;//低位在前 高位 高位再后 Sys_State.Ctr_Value.Phase
    Uart_Tx.Tx_Buffer[4] = (unsigned int)Sys_State.Ctr_Value.Phase & 0xff;

    Uart_Tx.Tx_Buffer[3] = (((unsigned int)Adc_Value.VAvg)>>8) & 0xff;//低位在前 高位 高位再后 Sys_State.Ctr_Value.Phase
    Uart_Tx.Tx_Buffer[2] = (unsigned int)Adc_Value.VAvg & 0xff;

    if(Uart_Tx.Send_Flag)//处于发送状态
    {
        if (SciaRegs.SCICTL2.bit.TXEMPTY == 1)//发送寄存器为空
        {
            SciaRegs.SCICTL1.bit.TXWAKE = 1;
            SciaRegs.SCITXBUF = *(Str+Str_Leng);

            Str_Leng ++;
            if(Str_Leng >= Leng)//发送完毕
            {
                Str_Leng = 0;
                Uart_Tx.Send_Flag = 0;
            }
        }
    }
    */
}

void Uart_Handle(UART_STRUCT* Sci_STR)
{
    if(Sci_STR->Rx_Buffer[SCI_ADRESS] == DC_DCADRESS)//直接转发数据
    {

    }
    else
    {
        if(Sci_STR->Rx_Buffer[SCI_ADRESS] == AC_DCADRESS)//需要处理数据
        {
            switch(Sci_STR->Rx_Buffer[SCI_ORDER])//解析命令位
            {
            case 0x01://获取电网端口参数
                break;
            case 0x02://获取逆变输出参数
                break;
            case 0x03://获取BACKUP
                break;
            case 0x04:
                break;
            default:
                break;
            }
        }
    }
}

/*串口处理服务函数*/
void Uart_Service(UART_STRUCT* Sci_STR)
{
    /*发送*/
    if(Sci_STR->Sci_Send_Flag)
    {
        if(Sci_STR->SCI_P->SCIFFTX.bit.TXFFST < 4)//发送FIFO 有空余
        {
            Sci_STR->SCI_P->SCITXBUF = Sci_STR->Tx_Buffer[Sci_STR->Tx_Point];//写入数据
            Sci_STR->Tx_Point++;
            if(Sci_STR->Tx_Point >= Sci_STR->Tx_Size)//发送完毕
            {
                Sci_STR->Tx_Point = 0;
                Sci_STR->Sci_Send_Flag = 0;
            }
        }
    }
    /*接收*/
    switch(Sci_STR->UART_STATE)
    {
        case IDLE://空闲
            if(Sci_STR->SCI_P->SCIFFRX.bit.RXFFST != 0)//查询接收缓存是否有数据
            {
                Sci_STR->UART_STATE = RECEIVE;
            }
            break;
        case RECEIVE://接收
            if(Sci_STR->SCI_P->SCIFFRX.bit.RXFFST != 0)//查询接收缓存是否有数据
            {
                Sci_STR->Rx_Buffer[Sci_STR->Rx_Point] = Sci_STR->SCI_P->SCIRXBUF.bit.RXDT;//取出数据
                Sci_STR->Rx_Point++;if(Sci_STR->Rx_Point >= BUFFER_SIZE)Sci_STR->Rx_Point = 0;
            }
            if(Sci_STR->Rx_Buffer[Sci_STR->Rx_Point - 1] == FrameEnd && Sci_STR->Rx_Buffer[Sci_STR->Rx_Point - 2] != FrameTrans)//接收完毕
            {
                Sci_STR->UART_STATE = ANALY;//切换为解析状态
            }
            //通过判断数组末尾是否为帧尾防止数据溢出
            break;
        case ANALY://解析
            /*CRC校验*/

            /*内容解析处理*/
            Uart_Handle(Sci_STR);
            /*状态切换*/
            Sci_STR->Rx_Point = 0;
            Sci_STR->UART_STATE = IDLE;
            break;
        default:
            break;
    }
}
