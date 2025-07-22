
#include "DSP28x_Project.h"
#include "SCI.h"
#include <string.h>
#include <stdint.h>

UART_STRUCT Scia_Handle;
UART_STRUCT Scib_Handle;

/**************************************
 * ���Գ���
 * ���UART���ڴ�ӡ���ݹ���
 * UARTInit(9600);
 * ***********************************/

void UART_Init(unsigned long Baud_Rate)
{
    unsigned int Baud = 0;
    Baud = (90000000/4/8/Baud_Rate)-1;

    EALLOW;
    /*���ų�ʼ��*/
    //UART
    //GPIO28 <-> A-RX    //GPIO15 <-> B-RX
    //GPIO12 <-> A-TX    //GPIO58 <-> B-TX
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;//ʹ������
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;//ʹ������
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;//ʹ������
    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;//ʹ������
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;//����Ϊ
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;

    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;//����ΪATX
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;//����ΪBRX
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;//����ΪARX
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 2;//����ΪBRX

    GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;//TX ����Ϊ���
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;//RX ����Ϊ���
    GpioDataRegs.GPACLEAR.bit.GPIO7=1;//�������
    GpioDataRegs.GPACLEAR.bit.GPIO12=1;
    /*SCIA��ʼ��*/
    SciaRegs.SCICCR.bit.STOPBITS = 0;//1λ����λ
    SciaRegs.SCICCR.bit.PARITYENA = 0;//ȡ����żУ��
    SciaRegs.SCICCR.bit.SCICHAR = 0x07;//8λ����λ

    SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;//ͨѶģʽ��0������ģʽ 1����ַģʽ
    SciaRegs.SCICTL1.bit.RXENA = 0x1;//ʹ��RX���ն�
    SciaRegs.SCICTL1.bit.TXENA = 0x1;//ʹ��TX���Ͷ�
    SciaRegs.SCIHBAUD = Baud >> 8;//���ò����� (60M/4/BAUD/8)-1 103 124
    SciaRegs.SCILBAUD = Baud & 0XFF;
    SciaRegs.SCICTL1.bit.SWRESET = 0x1;

    SciaRegs.SCIFFTX.all = 0XE040;//FIFO����
    SciaRegs.SCIFFRX.all = 0X2040;
    SciaRegs.SCIPRI.bit.SOFT = 1;//���������ɷ��ͻ���պ����ͣ
    /*SCIB��ʼ��*/
    ScibRegs.SCICCR.bit.STOPBITS = 0;//1λ����λ
    ScibRegs.SCICCR.bit.PARITYENA = 0;//ȡ����żУ��
    ScibRegs.SCICCR.bit.SCICHAR = 0x07;//8λ����λ

    ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0;//ͨѶģʽ��0������ģʽ 1����ַģʽ
    ScibRegs.SCICTL1.bit.RXENA = 0x1;//ʹ��RX���ն�
    ScibRegs.SCICTL1.bit.TXENA = 0x1;//ʹ��TX���Ͷ�
    ScibRegs.SCIHBAUD = Baud >> 8;//���ò����� (90M/4/BAUD/8)-1 123
    ScibRegs.SCILBAUD = Baud & 0XFF;
    ScibRegs.SCICTL1.bit.SWRESET = 0x1;

    ScibRegs.SCIFFTX.all = 0XE040;//FIFO����
    ScibRegs.SCIFFRX.all = 0X2040;
    ScibRegs.SCIPRI.bit.SOFT = 1;//���������ɷ��ͻ���պ����ͣ

    EDIS;
    /*�ṹ�������ʼ��*/
    memset(&Scia_Handle,0,sizeof(UART_STRUCT));
    memset(&Scib_Handle,0,sizeof(UART_STRUCT));
    Scia_Handle.SCI_P = &SciaRegs;
    Scib_Handle.SCI_P = &ScibRegs;

    ////////////////////���ڵ���////////////////////
    Scib_Handle.Tx_Buffer[0] = 0X03;Scib_Handle.Tx_Buffer[1] = 0XFC;Scib_Handle.Tx_Buffer[6] = 0XFC;Scib_Handle.Tx_Buffer[7] = 0X03;
}

/***************************
 * ���ڷ��͵����ֽ�
 * Send_Char:��Ҫ���͵��ַ�
 * ʾ����//Uart_Send_Byte(0XAA);
 ****************************/
void Uart_Send_Byte(unsigned char Send_Char)
{
    if (SciaRegs.SCICTL2.bit.TXEMPTY == 1)//���ͼĴ���Ϊ��
    {
        SciaRegs.SCICTL1.bit.TXWAKE = 1;
        SciaRegs.SCITXBUF = Send_Char;
    }
}

/*����FIFO���պ���*/
unsigned int Uart_Read(volatile struct SCI_REGS* SCI_STR,char *Buf)
{
    //unsigned int Long;//���س���

    if(SCI_STR->SCIFFRX.bit.RXFFST != 0)//FIFO��������
    {
        *Buf = SCI_STR->SCIRXBUF.bit.RXDT;//ȡ������
    }
    return 0;//�ɷ��س���
}
/*����FIFO���ͺ���*/
void Uart_Send(volatile struct SCI_REGS* SCI_STR,Uint16 *Buf)
{
    if(SCI_STR->SCIFFTX.bit.TXFFST < 4)//����FIFO �п���
    {
        SCI_STR->SCITXBUF = *Buf;//д������
    }
}

/************************************************
 * ���ڷ����ַ���
 * Str���ַ����׵�ַ Leng���ַ������� Time:���ͼ��
 * ʾ����Uart_Send_Str(Uart_Tx.Tx_Buffer,4,200);
 * **********************************************/
void Uart_Send_Str(unsigned int* Str,unsigned char Leng,unsigned int Time)
{
    /*
    static unsigned char Str_Leng;

    if(++Uart_Tx.Send_Cnt >= Time)//�������ͼ��
    {
        if(!Uart_Tx.Send_Flag)
        {
            Uart_Tx.Send_Flag = 1;
            Uart_Tx.Send_Cnt = 0;
        }
    }

    //Uart_Tx.Tx_Buffer[3] = (((unsigned int)Mppt_Handle.Vpv)>>8) & 0xff;//��λ��ǰ ��λ ��λ�ٺ�
    //Uart_Tx.Tx_Buffer[2] = ((unsigned int)Mppt_Handle.Vpv) & 0xff;

    Uart_Tx.Tx_Buffer[5] = (((unsigned int)Sys_State.Ctr_Value.Phase)>>8) & 0xff;//��λ��ǰ ��λ ��λ�ٺ� Sys_State.Ctr_Value.Phase
    Uart_Tx.Tx_Buffer[4] = (unsigned int)Sys_State.Ctr_Value.Phase & 0xff;

    Uart_Tx.Tx_Buffer[3] = (((unsigned int)Adc_Value.VAvg)>>8) & 0xff;//��λ��ǰ ��λ ��λ�ٺ� Sys_State.Ctr_Value.Phase
    Uart_Tx.Tx_Buffer[2] = (unsigned int)Adc_Value.VAvg & 0xff;

    if(Uart_Tx.Send_Flag)//���ڷ���״̬
    {
        if (SciaRegs.SCICTL2.bit.TXEMPTY == 1)//���ͼĴ���Ϊ��
        {
            SciaRegs.SCICTL1.bit.TXWAKE = 1;
            SciaRegs.SCITXBUF = *(Str+Str_Leng);

            Str_Leng ++;
            if(Str_Leng >= Leng)//�������
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
    if(Sci_STR->Rx_Buffer[SCI_ADRESS] == DC_DCADRESS)//ֱ��ת������
    {

    }
    else
    {
        if(Sci_STR->Rx_Buffer[SCI_ADRESS] == AC_DCADRESS)//��Ҫ��������
        {
            switch(Sci_STR->Rx_Buffer[SCI_ORDER])//��������λ
            {
            case 0x01://��ȡ�����˿ڲ���
                break;
            case 0x02://��ȡ����������
                break;
            case 0x03://��ȡBACKUP
                break;
            case 0x04:
                break;
            default:
                break;
            }
        }
    }
}

/*���ڴ��������*/
void Uart_Service(UART_STRUCT* Sci_STR)
{
    /*����*/
    if(Sci_STR->Sci_Send_Flag)
    {
        if(Sci_STR->SCI_P->SCIFFTX.bit.TXFFST < 4)//����FIFO �п���
        {
            Sci_STR->SCI_P->SCITXBUF = Sci_STR->Tx_Buffer[Sci_STR->Tx_Point];//д������
            Sci_STR->Tx_Point++;
            if(Sci_STR->Tx_Point >= Sci_STR->Tx_Size)//�������
            {
                Sci_STR->Tx_Point = 0;
                Sci_STR->Sci_Send_Flag = 0;
            }
        }
    }
    /*����*/
    switch(Sci_STR->UART_STATE)
    {
        case IDLE://����
            if(Sci_STR->SCI_P->SCIFFRX.bit.RXFFST != 0)//��ѯ���ջ����Ƿ�������
            {
                Sci_STR->UART_STATE = RECEIVE;
            }
            break;
        case RECEIVE://����
            if(Sci_STR->SCI_P->SCIFFRX.bit.RXFFST != 0)//��ѯ���ջ����Ƿ�������
            {
                Sci_STR->Rx_Buffer[Sci_STR->Rx_Point] = Sci_STR->SCI_P->SCIRXBUF.bit.RXDT;//ȡ������
                Sci_STR->Rx_Point++;if(Sci_STR->Rx_Point >= BUFFER_SIZE)Sci_STR->Rx_Point = 0;
            }
            if(Sci_STR->Rx_Buffer[Sci_STR->Rx_Point - 1] == FrameEnd && Sci_STR->Rx_Buffer[Sci_STR->Rx_Point - 2] != FrameTrans)//�������
            {
                Sci_STR->UART_STATE = ANALY;//�л�Ϊ����״̬
            }
            //ͨ���ж�����ĩβ�Ƿ�Ϊ֡β��ֹ�������
            break;
        case ANALY://����
            /*CRCУ��*/

            /*���ݽ�������*/
            Uart_Handle(Sci_STR);
            /*״̬�л�*/
            Sci_STR->Rx_Point = 0;
            Sci_STR->UART_STATE = IDLE;
            break;
        default:
            break;
    }
}
