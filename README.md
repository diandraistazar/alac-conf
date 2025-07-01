# alacritty-conf-selector

**alacritty-conf-selector** is a program that allows you to adjust your Alacritty configuration directly from the command line. The program is written entirely in C, including the configuration logic.

## Installation
1. Clone this repository to your local machine and navigate into the directory:
```bash
git clone https://github.com/diandraistazar/alacritty-conf-selector.git
cd alacritty-conf-selector
```
2. Build the program using ```make```, or use ```make install``` to install it to your system (requires root privileges):
```bash
make                # Build program
sudo make install   # Build program and install to your system
```
3. Run the program:
```bash
alacritty-conf-selector
```

## Configuration
You can modify the configuration paths and their corresponding labels in ```main.c```:
```
// Config paths
static char *config_path[]  = {
	"/home/diandra/.config/alacritty/configurations/windows",
	"/home/diandra/.config/alacritty/configurations/fonts",
	"/home/diandra/.config/alacritty/configurations/colors",
};
// Label
static char *name[] = {
	"window",
	"font",
	"color",
};
...
```

## Usage
To see all available options for ```alacritty-conf-selector```, run
```
alacritty-conf-selector help
```
Example output:
```
alacritty-conf-selector version 0.1
Created by Diandra

list [window/color/font/all]                # List available configs
select [window-cfg, color-cfg, font-cfg]    # Select specific configs to use 
reload                                      # Reload Alacritty config after changes
...
```

### Examples:
1. List all available configs:
```
alacritty-conf-selector list all
```
or list all specific ones like ```window```, ```color```, ```font```, etc.
```
alacritty-conf-selector list window
```

3. Select configuration files to apply:
```
alacritty-conf-selector select window1.toml anonymous-pro.toml onedark.toml
```

5. If you have modified the current config (in config_path) and want to apply it. Simply run:
```
alacritty-conf-selector reload
```

## Uninstallation
To uninstall the program from your system, simply run (requires root privileges):
```
sudo make uninstall
```
