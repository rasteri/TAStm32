#!/usr/bin/env python3
import struct
import sys

# Header format
#   000 16-byte signature and format version: "Gens Movie TEST9"
#   00F ASCII-encoded GMV file format version. The most recent is 'A'. (?)
#   010 4-byte little-endian unsigned int: rerecord count
#   014 ASCII-encoded controller config for player 1. '3' or '6'.
#   015 ASCII-encoded controller config for player 2. '3' or '6'.
#   016 special flags (Version A and up only):
#      bit 7(most significant): if "1", movie runs at 50 frames per second; if "0", movie runs at 60 frames per second
#      bit 6: if "1", movie requires a savestate.
#      bit 5: if "1", movie is 3-player movie; if "0", movie is 2-player movie
#   018 40-byte zero-terminated ASCII movie name string
#   040 frame data

def read_header(data):
    signature, = struct.unpack('<15s', data[:0xf])
    if signature != b'Gens Movie TEST':
        print(signature)
        print(len(signature))
        raise RuntimeError('Bad movie signature')
    header = {'signature': signature}
    values = struct.unpack('<cIccB40s', data[0xf:0x3f])
    header["version"] = values[0]
    header["rerecord_count"] = values[1]
    header["p1"] = values[2]
    header["p2"] = values[3]
    header["fps"] = "50" if (bool(int(values[4]) & 0x80)) else "60"
    header["savestate_required"] = bool(int(values[4]) & 0x40)
    header["3players"] = (bool(int(values[4]) & 0x20))
    header["movie_name"] = values[5].decode("ascii'").rstrip()
    return header

def read_input(data, header=None):
    if header == None:
        header = read_header(data)
    start = 0x40
    input_struct = struct.Struct('3s')
    input_iter = input_struct.iter_unpack(data[start:])
    input_data = []
    for frame in input_iter:
        input_data.append(_process_input(frame[0], header))
    return input_data

def _process_input(data, header):
    if header.get("3players"):
        raise NotImplementedError("3 Player Runs not Implemented for Genesis")
    else:
        new = bytearray(4)
    c1 = data[0] ^ 0xff
    c2 = data[1] ^ 0xff
    c3 = data[2] ^ 0xff

    new[0] += (c1 & 0x01) # P1 Up
    new[0] += (c1 & 0x02) # P1 Down
    new[0] += (c1 & 0x04) # P1 Left
    new[0] += (c1 & 0x08) # P1 Right
    new[0] += (c1 & 0x10) # P1 A
    new[0] += (c1 & 0x20) # P1 B
    new[0] += (c1 & 0x40) # P1 C
    new[0] += (c1 & 0x80) # P1 Start

    new[1] += (c3 & 0x01) # P1 X
    new[1] += (c3 & 0x02) # P1 Y
    new[1] += (c3 & 0x04) # P1 Z
    new[1] += (c3 & 0x08) # P1 Mode

    new[2] += (c2 & 0x01) # P2 Up
    new[2] += (c2 & 0x02) # P2 Down
    new[2] += (c2 & 0x04) # P2 Left
    new[2] += (c2 & 0x08) # P2 Right
    new[2] += (c2 & 0x10) # P2 A
    new[2] += (c2 & 0x20) # P2 B
    new[2] += (c2 & 0x40) # P2 C
    new[2] += (c2 & 0x80) # P2 Start

    new[3] += (c3 & 0x10) # P2 X
    new[3] += (c3 & 0x20) # P2 Y
    new[3] += (c3 & 0x40) # P2 Z
    new[3] += (c3 & 0x80) # P2 Mode

    return new

def main():
    try:
        file = sys.argv[1]
    except:
        print(f'Usage {sys.argv[0]} <movie file>')
        sys.exit()
    with open(file, 'rb') as f:
        data = f.read()
    header = read_header(data)
    for k, v in header.items():
        if 'unused' in k:
            continue
        else:
            print('{}: {}'.format(k, v))
    inputs = read_input(data, header)
    print(inputs[:20])

if __name__ == '__main__':
    main()