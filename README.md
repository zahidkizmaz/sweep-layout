# ferris/sweep QMK layout

My [ferris/sweep](https://github.com/davidphilipbarr/sweep) keyboard QMK layout.

Sweep keyboard is a 34-key split keyboard.

## Layers

- Layer 1 Base
- Layer 2 Numbers & Navigation
- Layer 3 Symbols

## How to use

#### Requirements:

Install qmk.

```
git clone https://github.com/zahidkizmaz/sweep-layout.git

# get your qmk home dir
qmk env  # this command will output your qmk env variables including the QMK_HOME

mkdir -p ${QMK_HOME}/keyboards/ferris/keymaps/mylayout
cp sweep-layout/src/* ${QMK_HOME}/keyboards/ferris/keymaps/mylayout
qmk compile -kb ferris/sweep -km mylayout
qmk flash -kb ferris/sweep -km mylayout
```
