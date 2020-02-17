#!/usr/bin/env python3
import enum
import json
import os
import hashlib
import sys

import argparse_helper


class PreReset(enum.Enum):
    NONE = 0
    SOFT = 1
    HARD = 2

    def toJSON(self):
        return self.value


class RunSettings:
    def __init__(self, settings):
        cf = int(settings.get("clock_filter", 0))
        assert cf >= 0 and cf <= 63, "clock filter must be in range [0,63]"
        self._dict = {
            "blank_frames": settings.get("blank_frames", 0),
            "players": settings.get("players", [1]),
            "console": settings.get("console"),
            "dpcm_fix": settings.get("dpcm_fix", False),
            "pre_reset": PreReset(settings.get("pre_reset", PreReset.NONE)),
            "clock_filter": settings.get("clock_filter", 0),
            "overread": settings.get("overread", False),
            "transitions": settings.get("transitions", []),
            "latch_train": settings.get("latch_train", [])
        }

    @property
    def blank_frames(self):
        return self._dict.get("blank_frames", 0)

    @property
    def players(self):
        return self._dict.get("players", 0)

    @property
    def console(self):
        return self._dict.get("console", 0)

    @property
    def dpcm_fix(self):
        return self._dict.get("dpcm_fix", 0)

    @property
    def pre_reset(self):
        return self._dict.get("pre_reset", 0)

    @property
    def clock_filter(self):
        return self._dict.get("clock_filter", 0)

    @property
    def overread(self):
        return self._dict.get("overread", 0)

    @property
    def transitions(self):
        return self._dict.get("transitions", 0)

    @property
    def latch_train(self):
        return self._dict.get("latch_train", 0)

    def __str__(self):
        return self._dict.__str__()

    def toJSON(self):
        return self._dict

    @staticmethod
    def loadFromArguments(args):
        settings = {}
        settings["players"] = sorted(int(x) for x in args.players.split(","))
        if args.transition:
            settings["transitions"] = [(int(x[0]), x[1].encode())
                                       for x in args.transition]
        if args.latchtrain:
            settings["latch_train"] = [int(x)
                                       for x in args.latchtrain.split(",")]
        if args.hardreset:
            settings["pre_reset"] = PreReset.HARD
        elif args.softreset:
            settings["pre_reset"] = PreReset.SOFT
        else:
            settings["pre_reset"] = PreReset.NONE
        settings["clock_filter"] = int(args.clock or 0)
        settings["console"] = args.console
        settings["blank_frames"] = args.blank
        settings["dpcm_fix"] = args.dpcm
        settings["overread"] = args.overread
        return RunSettings(settings)

    @staticmethod
    def loadFromJSON(data):
        return RunSettings(data)

class MovieData():
    def __init__(self, filepath, md5=''):
        self.filepath = filepath
        with open(filepath, 'rb') as f:
            self.data = f.read()
        self.md5 = hashlib.md5(self.data).hexdigest()
        if md5 != self.md5:
            self.goodhash = False
        else:
            self.goodhash = True

    def toJSON(self):
        return {
            "filepath": self.filepath,
            "filename": os.path.split(self.filepath)[1],
            "md5": self.md5
        }

    @staticmethod
    def loadFromArguments(moviepath):
        try:
            movie = MovieData(moviepath)
            return movie
        except:
            print(f"ERROR: the specified file ({moviepath}) failed to open")
            raise

    @staticmethod
    def loadFromJSON(data):
        local = None
        try:
            path = MovieData(data['filepath'], data['md5'])
        except:
            path = None
        if path == None or not path.goodhash:
            try:
                local = MovieData(os.path.join(".", data['filename']), data['md5'])
            except:
                local = None
        if local == None and path == None:
            print(f"ERROR: unable to locate specified ({data})")
            raise FileNotFoundError
        elif path and path.goodhash:
            print(f"Loaded movie from {path.filepath}")
            return path
        elif local and local.goodhash:
            print(f"Loaded movie from {local.filepath}")
            return local
        elif local == None and not path.goodhash:
            print(f"WARN: Loaded movie from {path.filepath} with bad hash\nexpected:\t{data['md5']}\nfound:\t{path.md5}")
            return path
        elif path == None and not local.goodhash:
            print(f"WARN: Loaded movie from {local.filepath} with bad hash\nexpected:\t{data['md5']}\nfound:\t{local.md5}")
            return local
        else:
            print(f"WARN: Trying to load movie\ngood:\t{data['md5']}\n0\t{path.md5}\t{path.filepath}\n1\t{local.md5}\t{local.filepath}")
            choice = input("0/1/(Abort)")
            if choice == "0":
                return path
            elif choice == "1":
                return local
            else:
                sys.exit(0)

def save(filepath, settings, movie=None):
    _, ext = os.path.splitext(filepath)
    if ext == ".json":
        with open(filepath, "w") as f:
            if movie==None:
                json.dump(settings, f, default=lambda x: x.toJSON())
            else:
                json.dump({
                    "settings": settings,
                    "movie": movie
                }, f, default=lambda x: x.toJSON())

def load(filepath, argsmovie=''):
    _, ext = os.path.splitext(filepath)
    if argsmovie:
        movie = MovieData.loadFromArguments(argsmovie)
    if ext == ".json":
        with open(filepath, "r") as f:
            data = json.load(f)
        settings = data.get("settings", False)
        if settings:
            rs = RunSettings.loadFromJSON(settings)
        else:
            rs = RunSettings.loadFromJSON(data)
        moviedata = data.get("movie", False)
        if argsmovie == '':
            if moviedata:
                movie = MovieData.loadFromJSON(moviedata)
            else:
                print("ERROR: No movie specified")
                sys.exit(0)
        return (rs, movie)
