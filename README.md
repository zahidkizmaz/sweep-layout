# ferris/sweep QMK layout

My [ferris/sweep](https://github.com/davidphilipbarr/sweep) keyboard QMK layout.

## Layers

Sweep keyboard is a 34-key split keyboard. That is why we need multiple layers:

- Layer 1 Base
- Layer 2 Numbers & Navigation
- Layer 3 Symbols
- Layer 4 Board control

## How to use

### Requirements:

#### Install

- [QMK](https://docs.qmk.fm/#/newbs_getting_started)
- [Just (Optional)](https://github.com/casey/just)

### Setup

##### Clone the repository

```sh
git clone https://github.com/zahidkizmaz/sweep-layout.git
```

##### With just

```sh
just create-env
just setup
```

##### Without just

```sh
# get your qmk home dir
qmk env  # this command will output your qmk env variables including the QMK_HOME

mkdir -p ${QMK_HOME}/keyboards/ferris/keymaps/mylayout
cp sweep-layout/src/* ${QMK_HOME}/keyboards/ferris/keymaps/mylayout
qmk compile -kb ferris/sweep -km mylayout
qmk flash -kb ferris/sweep -km mylayout
```
