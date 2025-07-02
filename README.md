# alac-conf

**alac-conf** is a program that allows you to adjust your Alacritty configuration directly from the command line. The program is written entirely in C.

## Installation
1. Clone this repository to your local machine and navigate into the directory:
```bash
git clone https://github.com/diandraistazar/alac-conf.git
cd alac-conf
```
2. Build the program using ```make```, or use ```make install``` to install it to your system (requires root privileges):
```bash
make                # Build program
sudo make install   # Build program and install to your system
```
3. Run the program:
```bash
alac-conf
```

## Configuration
You can modify the configuration paths and others in ```config.h```:
```
char *config_path = "/home/diandra/.config/alacritty/configurations";
char *config_name[] = {
	"window",
	"font",
	"color",
};
char *alac_conf = "/home/diandra/.config/alacritty/alacritty.toml";
...
```

## Usage
To see all available options for ```alac-conf```, run
```
alac-conf help
```
Example output:
```
alac-conf version 0.1
Created by Diandra

list [window/color/font/all]                # List available configs
select [window-cfg, color-cfg, font-cfg]    # Select specific configs to use 
reload                                      # Reload Alacritty config after changes
...
```

### Examples:
1. List all available configs:
```
alac-conf list all
```
or list all specific ones like ```window```, ```color```, ```font```, etc.
```
alac-conf list window
```

3. Select configuration files to apply:
```
alac-conf select window1.toml anonymous-pro.toml onedark.toml
```

5. If you have modified the current config (in config_path) and want to apply it. Simply run:
```
alac-conf reload
```

## Uninstallation
To uninstall the program from your system, simply run (requires root privileges):
```
sudo make uninstall
```
