#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "main.h"
#include "fatfs.h"
#include "ssd1306/ssd1306.h"
#include "usbplayback/usbplayback.h"
#include "usbplayback/menu.h"
#include "usbplayback/inputs.h"
#include "usbd_cdc_if.h"
#include "n64.h"
#include "TASRun.h"
#include "stm32f4xx_it.h"
#include "serial_interface.h"

uint32_t readcount = 0;
uint32_t latchCount;
FIL TasFile;

PlaybackState USBPlaybackState = RUNSTATE_TASPAD;

char inputBuffer[512];
uint32_t inputBufferSize;

uint8_t menuNeedsUpdating = 1;
uint32_t menuNextThink = 0;
uint8_t screenOK = 0;
FATFS TASDrive;
bool USBok = 0;

uint8_t taspadding = 0;

NESControllerData taspad_data;


// Set up screen, menus etc
uint8_t USB_Playback_Init() {

	Menu_Init();
	if (TASPAD) {
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		// Set up pad inputs
		GPIO_InitStruct.Pin = TASPAD_UP_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TASPAD_UP_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = TASPAD_RIGHT_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TASPAD_RIGHT_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = TASPAD_DOWN_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TASPAD_DOWN_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = TASPAD_LEFT_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TASPAD_LEFT_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = TASPAD_SELECT_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TASPAD_SELECT_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = TASPAD_START_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TASPAD_START_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = TASPAD_B_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TASPAD_B_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = TASPAD_A_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(TASPAD_A_GPIO_Port, &GPIO_InitStruct);
		Start_TasPad();
	}
	if (!ssd1306_Init())
		return 0;
	else {
		screenOK = 1;
		return 1;
	}
	//ssd1306_TestAll();
}

// Stop the currently running TAS
void USB_Stop_TAS() {
	USBPlaybackState = RUNSTATE_STOPPING;
}

// start processing inputs
void Start_TasPad(){
	ResetRun();
	TASRunSetConsole(CONSOLE_NES);
	SetSNESMode();
	TASRunSetNumControllers(1);
	TASRunSetNumDataLanes(1);
	tasPadding = 1;
}

// Start a TAS with the specified filename
void USB_Start_Tas(char *file) {
	FRESULT res;
	char *tasfile = NULL;
	char *extension = strrchr(file, '.');
	readcount = 0;
	ResetRun();

	// Extension is tcf, grab parameters from it
	if (strcmp(extension, ".tcf") == 0) {
		if (load_tcf(file)) {
			tasfile = tasrun->inputFile;
		}
	}

	// Failing that, guess at some default parameters by the extension name. TODO maybe try and find an associated tcf?
	else if (strcmp(extension, ".r08") == 0) {

		TASRunSetConsole(CONSOLE_NES);
		tasfile = file;
		SetSNESMode();
		TASRunSetNumControllers(2);
		TASRunSetNumDataLanes(1);

	} else if (strcmp(extension, ".r16m") == 0) {

		TASRunSetConsole(CONSOLE_SNES);
		tasfile = file;
		SetSNESMode();
		TASRunSetNumControllers(2);
		TASRunSetNumDataLanes(4);

	}

	// we want to read in approx 512-byte chunks, but it has to be a multiple of the input data size
	// clamp the input buffer size to the highest integer multiple of the input data to 512
	inputBufferSize = (512 / tasrun->input_data_size) * tasrun->input_data_size;

	if (tasfile != NULL) {
		res = f_open(&TasFile, tasfile, FA_READ);
		if (res == FR_OK) {
			// Add blank frames
			while (tasrun->blank--) {
				ExtractDataAndAddFrame(NULL, tasrun->input_data_size);
			}

			USBPlaybackState = RUNSTATE_RUNNING;
		}
	}
}

// enable interrupts and setup first frame
void Initialize_Run(){
	if (tasrun->console == CONSOLE_NES
			|| tasrun->console == CONSOLE_SNES) {
		if (tasrun->dpcmFix) {
			toggleNext = 1;
		}
		if (TASRunGetClockFix()) {
			clockFix = 1;
		}

		EXTI1_IRQHandler();
	}

	tasrun->initialized = 1;

	__disable_irq();
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	if (tasrun->multitap)
		HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	__enable_irq();
}

// Handle all the menus and buffer stuffing, etc
void USB_Playback_Task() {
	static UINT br;
	static uint8_t buffer[512];
	static FRESULT res;

	if (!USBok){
		res = f_mount(&TASDrive, (TCHAR const*) USBHPath, 1);
		if (res == FR_OK) {
			USBok = 1;

		}
	}

	switch (USBPlaybackState) {

	case RUNSTATE_RUNNING:

		// Fill buffer up to the last inputBufferSize
		while (tasrun->size * tasrun->input_data_size
				< (1024 * tasrun->input_data_size) - inputBufferSize) {
			res = f_read(&TasFile, buffer, inputBufferSize, &br);
			if (res == FR_OK && br >= tasrun->input_data_size) {
				readcount += br;
				for (int k = 0; k < br; k += tasrun->input_data_size) {
					ExtractDataAndAddFrame(&buffer[k], tasrun->input_data_size);
				}
			} else { // we ran out of data
				USBPlaybackState = RUNSTATE_FINISHING;
				break;
			}

			// run once per run
			if (!tasrun->initialized && tasrun->size > 0)
				Initialize_Run();
		}
		break;

	case RUNSTATE_TASPAD:

		NESControllerData nes_data;
		nes_data.up = ~HAL_GPIO_ReadPin(TASPAD_UP_GPIO_Port, TASPAD_UP_Pin);
		nes_data.down = ~HAL_GPIO_ReadPin(TASPAD_DOWN_GPIO_Port, TASPAD_DOWN_Pin);
		nes_data.left = ~HAL_GPIO_ReadPin(TASPAD_LEFT_GPIO_Port, TASPAD_LEFT_Pin);
		nes_data.right = ~HAL_GPIO_ReadPin(TASPAD_RIGHT_GPIO_Port, TASPAD_RIGHT_Pin);
		nes_data.select = ~HAL_GPIO_ReadPin(TASPAD_SELECT_GPIO_Port, TASPAD_SELECT_Pin);
		nes_data.start = ~HAL_GPIO_ReadPin(TASPAD_START_GPIO_Port, TASPAD_START_Pin);
		nes_data.a = ~HAL_GPIO_ReadPin(TASPAD_A_GPIO_Port, TASPAD_A_Pin);
		nes_data.b = ~HAL_GPIO_ReadPin(TASPAD_B_GPIO_Port, TASPAD_B_Pin);



		// secret code to run a TAS - hold all buttons and a d-pad direction
		if (nes_data.a && nes_data.b && nes_data.select && nes_data.start){
			if (nes_data.up) USB_Start_Tas("taspad1.tcf");
			if (nes_data.right) USB_Start_Tas("taspad2.tcf");
			if (nes_data.down) USB_Start_Tas("taspad3.tcf");
			if (nes_data.left) USB_Start_Tas("taspad4.tcf");
			tasPadding = 0;
			break;

		}
		// run once per run
		if (!tasrun->initialized && tasrun->size > 0)
			Initialize_Run();


		break;

	case RUNSTATE_FINISHING:
		if (tasrun->size == 0) {
			USBPlaybackState = RUNSTATE_STOPPING;
		} else
			break;

	case RUNSTATE_STOPPING:
		f_close(&TasFile);
		ResetRun();
		USBPlaybackState = RUNSTATE_STOPPED;
		break;

	default:
		break;

	}
	if (screenOK && (menuNeedsUpdating || uwTick >= menuNextThink)) {
		menuNextThink = uwTick + DISPLAYUPDATEFREQ;
		Menu_Display();
	}

}

