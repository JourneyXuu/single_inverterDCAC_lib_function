#ifndef SYSTEM_INIT_H_
#define SYSTEM_INIT_H_

void SysCtrl_Init(void);
void Function_Module_Init(void);
void DCEventTrip_Init(void);
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

#define      _FLASHOK        1

#ifdef _FLASHOK
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
extern Uint16 RamfuncsLoadSize;
#endif

#endif
