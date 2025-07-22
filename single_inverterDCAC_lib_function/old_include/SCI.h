#ifndef SCI_H_
#define SCI_H_

#define FrameHead   0X9B//֡ͷ
#define FrameEnd    0X9D//֡β
#define FrameTrans  0x5C//ת���ַ�

#define SCI_ADRESS  0//��ַλ
#define SCI_ORDER   1//����λ
#define DC_DCADRESS 0XA0//���͸�DC_DC˫���ܵ�����
#define AC_DCADRESS 0XA1//���͸����������

#define BUFFER_SIZE 32//���������С

typedef enum
{
    IDLE = 0,//����
    RECEIVE = 1,//����
    ANALY = 2,//����
}UART_STATE_ENUM;

typedef struct
{
    unsigned int Sci_Send_Flag;//�Ƿ���Ҫ����
    volatile struct SCI_REGS* SCI_P;//��ʼ����Ӧ���ڽṹ��
    UART_STATE_ENUM UART_STATE;//���ڹ���״̬��
    char Tx_Buffer[BUFFER_SIZE];//�ַ�����
    volatile Uint16 Rx_Buffer[BUFFER_SIZE];//�ַ�����
    unsigned int Tx_Size;//��������λ����
    unsigned int Tx_Point;//����ָ��
    unsigned int Rx_Point;//����ָ��
    unsigned char Send_Cnt;//���ͼ������
}UART_STRUCT;

extern UART_STRUCT Scia_Handle;
extern UART_STRUCT Scib_Handle;

void UART_Init(unsigned long Baud_Rate);
void Uart_Send_Byte(unsigned char Send_Char);
void Uart_Send_Str(unsigned int* Str,unsigned char Leng,unsigned int Time);
unsigned int Uart_Read(volatile struct SCI_REGS* SCI_STR,char *Buf);
void Uart_Service(UART_STRUCT* Sci_STR);
#endif /* SCI_H_ */
