#!/usr/bin/env python3
import serial, sys, time, os, gc
import serial_helper
import argparse_helper
import tastm32
import psutil
import struct
import mido
import time

if(os.name == 'nt'):
    psutil.Process().nice(psutil.REALTIME_PRIORITY_CLASS)
else:
    psutil.Process().nice(20)

gc.disable()

parser = argparse_helper.audio_parser()
args = parser.parse_args()

DEBUG = args.debug

# try and connect to the TAStm32
if args.serial == None:
    dev = tastm32.TAStm32(serial_helper.select_serial_port())
else:
    dev = tastm32.TAStm32(args.serial)
ser = dev

# TODO: MAP TO CORRECT MIDI NOTES
bmap = {
  64: 0x00000050, # analog up
  51: 0x000000B0, # analog down
  49: 0x0000B000, # analog left
  65: 0x00005000, # analog right
  5: 0x01000000, # d-pad up
  6: 0x02000000, # d-pad down
  7: 0x04000000, # d-pad left
  0: 0x08000000, # d-pad right
  72: 0x80000000, # A
  58: 0x40000000, # B
  76: 0x20000000, # Z
  56: 0x10000000, # Start
  10: 0x00080000, # C-up 
  11: 0x00040000, # C-down
  12: 0x00020000, # C-left
  13: 0x00010000, # C-right
  62: 0x00200000, # L
  74: 0x00100000 # R
}

int_to_byte_struct = struct.Struct('B')
def int_to_byte(interger):
    return int_to_byte_struct.pack(interger)

ser.write(b'R')
time.sleep(0.1)
cmd = ser.read(2)
print(bytes(cmd))

# set up the N64 correctly
ser.write(b'SAM\x80\x00')
time.sleep(0.1)
cmd = ser.read(2)
print(bytes(cmd))

ser.write(b'QA0')
time.sleep(0.1)

ser.ser.reset_input_buffer()

# might not be needed
#ser.write(bytes([65,0,0,0,0]))

# try and connect to the MIDI drumset
device_list = mido.get_input_names()

if len(device_list) == 1:
    choice = 0
else:
    for i in range(len(device_list)):
        print(f"{i}) {device_list[i]}")
    choice = input("Which device is your drumset (please enter the number and hit <enter>)? ")

frame_start = time.time()
data_to_tastm32 = 0
sentBlankLastTime = 0

with mido.open_input(device_list[int(choice)]) as midi_device:
    while True:
        #data_to_tastm32 = 0 # originally reset every frame
        # process the midi message
        for message in midi_device.iter_pending():
            # only the message we care about
            if message.type == "note_on":
                try:
                    data_to_tastm32 |= bmap[message.note]
                except KeyError:
                    pass
            elif message.type == "note_off":
                try:
                    data_to_tastm32 = data_to_tastm32 & ~bmap[message.note]
                except KeyError:
                    pass
        # prepare and send message to the replay device
        new_time = time.time()
        if new_time > frame_start+(1/30):
            if data_to_tastm32 == 0:
                if sentBlankLastTime == 0:
                    output_string = b'A' + data_to_tastm32.to_bytes(4, "big")
                    ser.write(output_string)
                    frame_start = new_time
                    sentBlankLastTime = 1
                else:
                    pass
            else:
                output_string = b'A' + data_to_tastm32.to_bytes(4, "big")
                ser.write(output_string)
                frame_start = new_time
                sentBlankLastTime = 0