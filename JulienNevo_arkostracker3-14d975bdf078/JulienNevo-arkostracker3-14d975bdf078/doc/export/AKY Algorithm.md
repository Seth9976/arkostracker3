# Arkos Tracker YM (AKY)

## Description

The goal of this format is to, contrary to "stupid" YM, agglomerate the registers related to each music note (including all their effect), and stores their YM list, possibly in an optimized way (differences).

The music still refers to Tracks, which refers to a list of YM blocks and the duration they should play.



**Important encoding note:** the format can be either encoded in little endian or big endian according to the header.



## Applied optimizations	

- When a RegisterBlock is part of another one, a "goto" is generated and the rest is cleared. It helps gain about 1kb per song, or more. But it was tricky to do: since diffs are encoded, the comparison can't be done on the "C++" object using the YM registers. It had to be done on the raw bytes of every line.

  ​



## Discarded optimizations ideas

- An optimization concerns the volume: it is easy to add a volume change (volume effect or even glide. **Not** Volume table). Maybe as another volume effect list? **No...**
- Encodes difference. This will not encode smaller blocks, but probably increase their compatibility! If a vibrato exists, it can be shared. **Drawback**: slower, if volume, limit must be tested, plus the sign management (4 bits->8bits). **Too slow**.


- Software period could be indexed (one bit if index). But first, one pass to see what frequencies are mostly used. **Too slow on Z80.** Too bad, it was interesting.

- The same for hardware period (or could use a ratio, but slower). Since the hardware period is very rarely >0x7fff, we can use one bit to put some other data + use an escape code. **Too slow on Z80.** 

- What about an RLE on duration on the Track listing? Maybe manage two lists:

  - One for the duration (go back to 128), one bit for isUnique?, and have 7 bits for the sequence size + 1 byte for the value.

  - One for the Block address (not RLEd).

    **Interesting, but too slow on Z80!**

- Track listing: index (word) of duration/BlockAddress.

  **Works but only 100 bytes won in general, even on long music.** Lose a bit for DiaEnd. About 15 cycles lost in all. So, idea probably not really worth it.

- After one RegisterBlock is created, at the same place of the (discarded) idea to remove the silence at its end, browse the RB and if long sequences of same data is found, cut it in two so that a loop can be performed. One initial test could be to find same-byte strings. If this string is >=6 long (for example), it is worth cutting it. **Only a few bytes saved** (B&B, in other song the result is catastrophic (#400 more)). The Blocks are well cut, but there are more references in the Tracks, swallowing the gain).




## To improve

- See "Difference - no software no hardware or loop" about the noise, but I don't think there is anything to do. Probably no big loss anyway.



## Encoding algorithm

The algorithm should be quite simple, compared to the AYx solutions on CPC.

Note: this algorithm has changed from the possibilities offered by the `SongPlayer` and `ChannelPlayer` classes. This may have added some more complexities.

#### Building the Blocks and Tracks

- Stores a YM list for the empty sound.


- For each Track
  - A trailing note may be there (no new note, instrument >0). If that's the case, consider it a note.
  - The same for silence.
  - For each note
    - Plays the note, including the effects it encounters on its way. Stores all the values on an YM list (volume, software period, etc.).
    - This stops when the Track has ended or when another note is encountered. There is no easy way to check if the instrument has stopped, so for this pass, empty registers will be added at the end.
    - On stop (new note, end of Track):
      - Stores the YM list in `RegisterBlock`s, with an easy way to get the duration, in frames.

When it is done, we have output Tracks (called `AkyTrack`s with their `RegisterBlock`s, linked to an YM list.

#### Removing trailing silence (DISCARDED)

Another pass is performed on each output Track to remove the possible "silence" at the end of each Block, creating another empty block instead. After this, it is easy to know what Blocks are fully silent or not.

**NOT USED ANYMORE!** Incredibly enough, by removing this, we actually save space, because there is no more silence block, which, in every track, eat up quite a lot of room. This also removes one test and allows a duration of RegisterBlock of 256.

#### Blocks in common

The next goal is to optimize the YM list count by checking if some can be put in common (we hope they can!).

- Sorts the list by size.
- From TS in smallest to largest:
  - Browses TL from *largest* to *smallest*.
  - Exits the loop if TS == TL.
  - Else, sees if TS fits in TL. If yes, fills a map linking the ID of TS to the ID of TL.

#### Encoding of Blocks

- For all the YM list inside the YM lists
  - Dismisses the lists which ID is inside the map, as they won't be directly used.
  - According to the registers (Mixer and volume), make a first pass with the registers that are used.
  - Make a second pass with the differences, and encodes it as source.

#### Encoding of Tracks

- For all the output Tracks
  - Encode the Blocks as source, using the possible reference to another YM list than the original, thanks to the map.






