# README
Coffee Shop is an ambient noise player. It plays realistic and natural sounds to help focus while working.

![Coffee Shop](https://cloud.githubusercontent.com/assets/25088746/23506805/fbdfbf36-ff41-11e6-95b8-d128928c02ef.png)

## DEPENDENCIES
- gcc
- sdl2
- sdl2_mixer
- gtk3

## COMPILATION
This should work:

gcc `pkg-config --cflags gtk+-3.0` -o Coffee-Shop -lSDL_mixer -lSDL `pkg-config --libs gtk+-3.0` main.c interface.c audio.c


## CREDITS

- Restaurant sound - https://youtu.be/uL7eVZtUFvs (licensed under CC BY-SA 3.0)
- Waves - https://youtu.be/0s5GmDrKrjk (licensed under CC BY 3.0)
- Fire - https://youtu.be/lQPdYRh3CME (licensed under CC BY 3.0)
- Rain - http://freesound.org/people/causative/sounds/102674/ (licensed under CC0 1.0)
- Thunder - https://youtu.be/CnJ_1nTaRUw (licensed under CC0 1.0)
- Wind - https://youtu.be/whegxuQGERw (licensed under CC BY-SA 3.0)

Sounds used have been modified in such a way as to make them appropriate for the usage (in particular, cropping and amplification).

### LICENSES
- CC BY-SA 3.0 - https://creativecommons.org/licenses/by-sa/3.0/
- CC BY 3.0 - https://creativecommons.org/licenses/by/3.0/
- CC0 1.0 - https://creativecommons.org/publicdomain/zero/1.0/
