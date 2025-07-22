
#include "DSP28x_Project.h"
#include "DMA.h"
#include <string.h>
#include <stdint.h>
#include "SCI.h"

//volatile Uint16 DMABuf1[1024];
//volatile Uint16 DMABuf2[1024];

void DMA_Init(void)
{
    volatile Uint16 *DMADest;
    volatile Uint16 *DMASource;
    DMADest = Scib_Handle.Tx_Buffer;//Rx_Buffer
    DMASource = Scib_Handle.Rx_Buffer;//Scib_Handle.SCI_P->SCIRXBUF.bit.RXDT;
    DMAInitialize();
    DMACH1AddrConfig(DMADest,DMASource);//����Ŀ�꣬����Դ
    DMACH1BurstConfig(31,2,2);//���ݴ�С��ÿ�δ������������Դ��ַ������Ŀ���ַ����
    DMACH1TransferConfig(31,2,2);
    DMACH1WrapConfig(0xFFFF,0,0xFFFF,0);
    DMACH1ModeConfig(DMA_TINT0,PERINT_ENABLE,ONESHOT_ENABLE,CONT_DISABLE,SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,THIRTYTWO_BIT,CHINT_END,CHINT_ENABLE);
    /*����DMA�ж�*/
    DMAInitialize();

    IER |= M_INT7 ;
    /*����DMA*/
    StartDMACH1();
}

__interrupt void DMA_CH1_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
}
