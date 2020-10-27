#ifndef USBPLAYBACK_USBPLAYBACK_H_
#define USBPLAYBACK_USBPLAYBACK_H_

#include "TASRun.h"
#include "stdbool.h"
#include "main.h"

#define TASPAD 1 // Whether or not to run as a TAS PAD

#define TASPAD_UP_Pin V1_DATA_1_Pin
#define TASPAD_RIGHT_Pin V1_DATA_0_Pin
#define TASPAD_DOWN_Pin V1_CLOCK_Pin
#define TASPAD_LEFT_Pin V1_LATCH_Pin
#define TASPAD_SELECT_Pin V2_DATA_0_Pin
#define TASPAD_START_Pin V2_DATA_1_Pin
#define TASPAD_B_Pin V2_LATCH_Pin
#define TASPAD_A_Pin V2_CLOCK_Pin

#define TASPAD_UP_GPIO_Port V1_DATA_1_GPIO_Port
#define TASPAD_RIGHT_GPIO_Port V1_DATA_0_GPIO_Port
#define TASPAD_DOWN_GPIO_Port V1_CLOCK_GPIO_Port
#define TASPAD_LEFT_GPIO_Port V1_LATCH_GPIO_Port
#define TASPAD_SELECT_GPIO_Port V2_DATA_0_GPIO_Port
#define TASPAD_START_GPIO_Port V2_DATA_1_GPIO_Port
#define TASPAD_B_GPIO_Port V2_LATCH_GPIO_Port
#define TASPAD_A_GPIO_Port V2_CLOCK_GPIO_Port
extern bool USBok;

extern NESControllerData taspad_data;
extern uint8_t taspadding = 0;

typedef enum
{
	RUNSTATE_STOPPED,
	RUNSTATE_RUNNING,
	RUNSTATE_TASPAD,
	RUNSTATE_FINISHING, // File has ended and we're just waiting for the buffer to run out
	RUNSTATE_STOPPING, // Playback is finished and state should reset
} PlaybackState;

extern PlaybackState USBPlaybackState;

uint8_t USB_Playback_Init();
void USB_Playback_Task();
void USB_Start_Tas(char *file);
void USB_Stop_TAS();
void USB_Playback_Task();
int load_tcf(char *filename);

#endif /* USBPLAYBACK_USBPLAYBACK_H_ */
