#ifndef SCI_H_
#define SCI_H_

#define FrameHead   0X9B//帧头
#define FrameEnd    0X9D//帧尾
#define FrameTrans  0x5C//转义字符

#define SCI_ADRESS  0//地址位
#define SCI_ORDER   1//命令位
#define DC_DCADRESS 0XA0//发送给DC_DC双向储能的数据
#define AC_DCADRESS 0XA1//发送给逆变板的数据

#define BUFFER_SIZE 32//缓存数组大小

typedef enum
{
    IDLE = 0,//空闲
    RECEIVE = 1,//接收
    ANALY = 2,//解析
}UART_STATE_ENUM;

typedef struct
{
    unsigned int Sci_Send_Flag;//是否需要发送
    volatile struct SCI_REGS* SCI_P;//初始化对应串口结构体
    UART_STATE_ENUM UART_STATE;//串口工作状态机
    char Tx_Buffer[BUFFER_SIZE];//字符缓存
    volatile Uint16 Rx_Buffer[BUFFER_SIZE];//字符缓存
    unsigned int Tx_Size;//发送数据位个数
    unsigned int Tx_Point;//发送指针
    unsigned int Rx_Point;//接收指针
    unsigned char Send_Cnt;//发送计数间隔
}UART_STRUCT;

extern UART_STRUCT Scia_Handle;
extern UART_STRUCT Scib_Handle;

void UART_Init(unsigned long Baud_Rate);
void Uart_Send_Byte(unsigned char Send_Char);
void Uart_Send_Str(unsigned int* Str,unsigned char Leng,unsigned int Time);
unsigned int Uart_Read(volatile struct SCI_REGS* SCI_STR,char *Buf);
void Uart_Service(UART_STRUCT* Sci_STR);
#endif /* SCI_H_ */
