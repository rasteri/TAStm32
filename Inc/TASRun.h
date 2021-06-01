#ifndef __TASRUN__H
#define __TASRUN__H

#include <stdint.h>
#include "n64.h"
#include "snes.h"
#include "gen.h"
#include "stm32f4xx_hal.h"
#include "main.h"

#define MAX_SIZE 1024
#define MAX_CONTROLLERS 2
#define MAX_DATA_LANES 4
#define MAX_TRANSITIONS 5

//#define BOARDV3
#define BOARDV4

#ifdef BOARDV3

#define SWITCH1_Pin PA6_Pin
#define SWITCH1_GPIO_Port PA6_GPIO_Port

#define SWITCH2_Pin PA7_Pin
#define SWITCH2_GPIO_Port PA7_GPIO_Port

#define SWITCH3_Pin PC14_Pin
#define SWITCH3_GPIO_Port PC14_GPIO_Port

#define SWITCH4_Pin PC13_Pin
#define SWITCH4_GPIO_Port PC13_GPIO_Port

#endif //BOARDV3

#ifdef BOARDV4

#define SWITCH1_Pin PB12_Pin
#define SWITCH1_GPIO_Port PB12_GPIO_Port

#define SWITCH2_Pin PB13_Pin
#define SWITCH2_GPIO_Port PB13_GPIO_Port

#define SWITCH3_Pin PA8_Pin
#define SWITCH3_GPIO_Port PA8_GPIO_Port

#define SWITCH4_Pin PA10_Pin
#define SWITCH4_GPIO_Port PA10_GPIO_Port

#endif //BOARDV4


typedef enum
{
	CONSOLE_N64,
	CONSOLE_SNES,
	CONSOLE_NES,
	CONSOLE_GC,
	CONSOLE_GEN
} Console;


typedef union
{
	N64ControllerData n64_data;
	SNESControllerData snes_data;
	NESControllerData nes_data;
	GCControllerData gc_data;
	GENControllerData gen_data;
} RunData;

typedef enum
{
	TRANSITION_NORMAL,
	TRANSITION_ACE,
	TRANSITION_RESET_SOFT,
	TRANSITION_RESET_HARD
} TransitionType;

typedef struct
{
	TransitionType type;
	uint32_t frameno;
} Transition;

typedef RunData RunDataArray[MAX_CONTROLLERS][MAX_DATA_LANES];

typedef struct
{
	Console console;
	uint8_t numControllers;
	uint8_t numDataLanes;
	RunDataArray runData[MAX_SIZE];
	RunDataArray *buf; // points to the next place the received serial data will be stored
	RunDataArray *end; // points to the end of the array for bounds checking
	RunDataArray *current; // points to what the console will read next
	volatile uint16_t size;
	uint8_t dpcmFix;
	uint8_t clockFix;
	uint8_t overread;
	uint8_t initialized;
	volatile uint32_t frameCount;
	Transition transitions_dpcm[MAX_TRANSITIONS];
	uint8_t console_data_size;
	uint8_t input_data_size;

	uint8_t multitap;
	int32_t blank;
	char inputFile[256];
} TASRun;

extern TASRun *tasrun;
extern TASRun tasruns;

// This file includes a load of static functions with definitions to make
// inlining easier

#define maybe_unused  __attribute__((unused))

maybe_unused static void SetN64InputMode()
{

	// Buffer disable P1D2 in case it was enabled for some reason
	//HAL_GPIO_WritePin(ENABLE_P1D2D3_GPIO_Port, ENABLE_P1D2D3_Pin, GPIO_PIN_SET);

	// Buffer direction in
	//HAL_GPIO_WritePin(DIR_P1P2D2D3_GPIO_Port, DIR_P1P2D2D3_Pin, GPIO_PIN_RESET);

	// MCU P1D2 input, triggered on falling edge
	SetupPin(P1_DATA_2_GPIO_Port, P1_DATA_2_Pin, GPIO_MODE_IT_FALLING, GPIO_NOPULL, GPIO_PIN_RESET);

	// Buffer Enable P1D2
	//HAL_GPIO_WritePin(ENABLE_P1D2D3_GPIO_Port, ENABLE_P1D2D3_Pin, GPIO_PIN_RESET);

	// port C4 to input mode
	/*const uint32_t MODER_SLOT = (P1_DATA_2_Pin*P1_DATA_2_Pin);
	const uint32_t MODER_MASK = 0b11 * MODER_SLOT;
	const uint32_t MODER_NEW_VALUE = GPIO_MODE_INPUT * MODER_SLOT;

	P1_DATA_2_GPIO_Port->MODER = (P1_DATA_2_GPIO_Port->MODER & ~MODER_MASK) | MODER_NEW_VALUE;*/
}

maybe_unused static void SetN64OutputMode()
{
	// Disable buffer output - we're pretending to be open drain
	//HAL_GPIO_WritePin(ENABLE_P1D2D3_GPIO_Port, ENABLE_P1D2D3_Pin, GPIO_PIN_SET);

	// Buffer direction out
	//HAL_GPIO_WritePin(DIR_P1P2D2D3_GPIO_Port, DIR_P1P2D2D3_Pin, GPIO_PIN_SET);

	// Make MCU pin output and LOW
	SetupPin(P1_DATA_2_GPIO_Port, P1_DATA_2_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_PIN_RESET);


	// port C4 to output mode
	/*const uint32_t MODER_SLOT = (P1_DATA_2_Pin*P1_DATA_2_Pin);
	const uint32_t MODER_MASK = 0b11 * MODER_SLOT;
	const uint32_t MODER_NEW_VALUE = GPIO_MODE_OUTPUT_PP * MODER_SLOT;
	P1_DATA_2_GPIO_Port->MODER = (P1_DATA_2_GPIO_Port->MODER & ~MODER_MASK) | MODER_NEW_VALUE;*/
}

// Functions below here are complex enough to not try to inline

uint8_t AddTransition(TransitionType type, uint32_t frameNumber);
void ResetTASRuns();


void TASRunSetClockFix(uint8_t cf);
uint8_t TASRunGetClockFix();


// These three functions update the cached 'input_data_size'
void TASRunSetNumControllers(uint8_t numControllers);
void TASRunSetNumDataLanes(uint8_t numDataLanes);
void TASRunSetConsole(Console console);

uint8_t TASRunIncrementFrameCount();
uint8_t AddFrame(RunDataArray frame);
void ExtractDataAndAdvance(RunDataArray rd, uint8_t* Buf, int *byteNum);
RunDataArray *GetNextFrame();
int ExtractDataAndAddFrame(uint8_t *buffer, uint32_t n);

void SetN64Mode();
void SetNESMode();
void SetSNESMode();
void SetGENMode();
void SetMultitapMode();
void ResetRun();
void ResetGPIO(void);
void SetupPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t Mode, uint32_t Pull, GPIO_PinState PinState);
#endif
