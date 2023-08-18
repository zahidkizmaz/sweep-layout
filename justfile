set dotenv-load

layout_name := env_var_or_default('LAYOUT_NAME', 'zahid')

# List commands
default:
	@just --list

# Create QMK keymap for ferris/sweep
create-keymap:
	qmk new-keymap -kb ferris/sweep -km {{layout_name}}

# Remove QMK keymap for ferris/sweep
delete-keymap:
	rm -vrf $LAYOUT_PATH

# QMK compile for ferris/sweep
compile:
	qmk compile -kb ferris/sweep -km {{layout_name}}

# QMK flash for ferris/sweep
flash:
	qmk flash -kb ferris/sweep -km {{layout_name}}

# QMK lint for ferris/sweep
lint:
	qmk lint -kb ferris/sweep -km {{layout_name}}

# Create .env file fomr qmk env command
create-env:
	qmk env > .env
	echo "LAYOUT_PATH=$QMK_HOME/keyboards/ferris/keymaps/{{layout_name}}" >> .env

# This requires .env file to be have QMK_HOME to be set
reset-qmk-keymap-folder:
	rm -v $LAYOUT_PATH/*

# Create symlinks for src folder to qmk folder
stow:
	stow -vS -t $LAYOUT_PATH src

# Create keymap and compile
setup: create-keymap reset-qmk-keymap-folder stow compile
