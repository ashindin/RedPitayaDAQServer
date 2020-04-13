#ifndef RP_DAQ_LIB_H
#define RP_DAQ_LIB_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ioctl.h>


#define BASE_FREQUENCY 125000000
#define ADC_BUFF_NUM_BITS 24 
#define ADC_BUFF_SIZE (1 << (ADC_BUFF_NUM_BITS+1)) 
#define ADC_BUFF_MEM_ADDRESS 0x18000000 // 0x1E000000  

#define PDM_BUFF_SIZE 128  

#define DAC_MODE_RASTERIZED 1
#define	DAC_MODE_STANDARD   0

#define SIGNAL_TYPE_SINE 0
#define SIGNAL_TYPE_SQUARE 1
#define SIGNAL_TYPE_TRIANGLE 2
#define SIGNAL_TYPE_SAWTOOTH 3

#define ADC_MODE_CONTINUOUS 0
#define ADC_MODE_TRIGGERED 1

#define TRIGGER_MODE_INTERNAL 0
#define	TRIGGER_MODE_EXTERNAL 1

#define OFF 0
#define ON 1

extern bool verbose;

extern int mmapfd;
extern volatile uint32_t *slcr, *axi_hp0;
// FPGA registers that are memory mapped
extern void *adc_sts, *pdm_sts, *reset_sts, *cfg, *ram, *buf;
extern char *pdm_cfg, *dac_cfg;

extern uint16_t dac_channel_A_modulus[4];
extern uint16_t dac_channel_B_modulus[4];

// init routines
extern int init();
extern void loadBitstream();

// fast DAC
extern uint16_t getAmplitude(int, int);
extern int setAmplitude(uint16_t, int, int);
extern int16_t getOffset(int);
extern int setOffset(int16_t, int);
extern double getFrequency(int, int);
extern int setFrequency(double, int, int);
extern int getModulusFactor(int, int);
extern int setModulusFactor(uint32_t, int, int);
extern double getPhase(int, int);
extern int setPhase(double, int, int);
extern int setDACMode(int);
extern int getDACMode();
extern int reconfigureDACModulus(int, int, int);
extern int getDACModulus(int, int);
extern int getSignalType(int);
extern int setSignalType(int, int);

// fast ADC
extern int setDecimation(uint16_t decimation);
extern uint16_t getDecimation();
extern uint32_t getWritePointer();
extern uint64_t getTotalWritePointer();
extern uint32_t getInternalWritePointer(uint64_t wp);
extern uint32_t getWritePointerOverflows();
extern uint32_t getWritePointerDistance(uint32_t start_pos, uint32_t end_pos);
extern void readADCData(uint32_t wp, uint32_t size, uint32_t* buffer);
extern int resetRamWriter();
extern int enableRamWriter();

// slow IO
extern int getPDMClockDivider();
extern int setPDMClockDivider(int);
extern int setPDMRegisterValue(uint64_t, int);
extern int setPDMRegisterAllValues(uint64_t);
extern int setPDMValue(uint16_t, int, int);
extern int setPDMAllValues(uint16_t, int);
extern int setPDMValueVolt(float, int, int);
extern int setPDMAllValuesVolt(float, int);
extern uint64_t getPDMRegisterValue();
extern uint64_t getPDMWritePointer();
extern uint64_t getPDMTotalWritePointer();
extern int* getPDMNextValues();
extern int getPDMNextValue();
extern uint32_t getXADCValue(int);
extern float getXADCValueVolt(int);

// misc
extern int setTriggerMode(int);
extern int getTriggerMode();
extern int getWatchdogMode();
extern int setWatchdogMode(int);
extern int getRAMWriterMode();
extern int setRAMWriterMode(int);
extern int getKeepAliveReset();
extern int setKeepAliveReset(int);
extern int getMasterTrigger();
extern int setMasterTrigger(int);
extern int getInstantResetMode();
extern int setInstantResetMode(int);
extern int getPeripheralAResetN();
extern int getFourierSynthAResetN();
extern int getPDMAResetN();
extern int getWriteToRAMAResetN();
extern int getXADCAResetN();
extern int getTriggerStatus();
extern int getWatchdogStatus();
extern int getInstantResetStatus();
extern void stopTx();

#endif /* RP_DAQ_LIB_H */
