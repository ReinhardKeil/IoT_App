# Issues

- [Issues](#issues)
  - [Project Structure](#project-structure)
  - [clayer files.](#clayer-files)
    - [Interface Layer](#interface-layer)
    - [App Layer](#app-layer)
    - [Device configuration (Board specific)](#device-configuration-board-specific)
  - [CSolution Issues](#csolution-issues)
    - [PROBLEM: Handling of *.clayer.yml file references](#problem-handling-of-clayeryml-file-references)
    - [Proposed Directories (IntDir, OutDir)](#proposed-directories-intdir-outdir)
    - [MINOR: Config files in RTE Directory](#minor-config-files-in-rte-directory)
    - [MINOR: Suggest to remove warning](#minor-suggest-to-remove-warning)
  - [MDK Importer Issues](#mdk-importer-issues)
    - [Other MDK problems](#other-mdk-problems)

## Project Structure

This are suggestions on how to rework the project structure for VS Code and KSC project management

## clayer files.

`*.clayer.yml` files should be in local directories that represent the layer

All \*.md files co-located with \*.clayer.yml with name README.MD  -> KSC Project Manager could generate a complete README info file (not a task of CSolution)

### Interface Layer

Directory Name
.\Interfaces -> .\Interfaces

The AWS specific interfaces should go into .\Interface\AWS  (currently it is just .\Interfaces to avoid huge rework)
Local Socket `config` files of Interfaces should move to related interface directory under directory name .\config

### App Layer

Since App is the actual application, it is not using sub-directories.  Not sure if this is the best method?

Should be the App Layer included in the project file itself -> (AWS_MQTT_Proposed.cproject.yml) ?


### Device configuration (Board specific)

This should go under the related `.\Board` directory (in this case the NXP `*.MEX` file)

## CSolution Issues

### PROBLEM: Handling of *.clayer.yml file references

The `.\Board\VHT_MPS2_Cortex-M7\Board.clayer.yml` contains just references to local files, but is included with
```
    - layer: ./Board/VHT_MPS2_Cortex-M7/Board.clayer.yml
```

Instead of creating local path, the output should have paths to the source files that relate to the project structure.

**Current:**
```
    <group name="Board">
      <file category="header" name="./main.h"/>
      <file category="sourceC" name="./main.c"/>
      <file category="sourceC" name="./retarget_stdio.c"/>
      <file category="sourceC" name="./vio_vht.c"/>
      <file category="header" name="./ETH_LAN91C111.h"/>
      <file category="sourceC" name="./ETH_LAN91C111.c"/>
      <file category="doc" name="./fvp_config.txt"/>
    </group>
```

**New:**
```
    <group name="Board">
      <file category="header" name="./Board/VHT_MPS2_Cortex-M7/main.h"/>
      <file category="sourceC" name="./Board/VHT_MPS2_Cortex-M7/main.c"/>
      <file category="sourceC" name="./Board/VHT_MPS2_Cortex-M7/retarget_stdio.c"/>
      <file category="sourceC" name="./Board/VHT_MPS2_Cortex-M7/vio_vht.c"/>
      <file category="header" name="./Board/VHT_MPS2_Cortex-M7/ETH_LAN91C111.h"/>
      <file category="sourceC" name="./Board/VHT_MPS2_Cortex-M7/ETH_LAN91C111.c"/>
      <file category="doc" name="./Board/VHT_MPS2_Cortex-M7/fvp_config.txt"/>
    </group>
```

### Proposed Directories (IntDir, OutDir)

Just in the project directory that stores the local `*.cproject.yml` file with this structure
```
.\IntDir
.\IntDir\.Debug+Board            // holds all intermediated files including the `.o` files
.\OutDir\Board                   // holds the output binary including map files.  All builds share same so that Project1 debug can be intermixed with Project2 release (testing different build combinations when required)
```

### MINOR: Config files in RTE Directory

For initial project setup just the original config file should be stored under name `.ConfigFile.h@1.2.0`.  See #1 under https://github.com/Open-CMSIS-Pack/devtools/blob/main/tools/projmgr/docs/Manual/Overview.md#plm-of-configuration-files

It appears that each `csolution convert` copies config files, but instead a version check should happen.  Only if the version mis-matches a copy and a user info should be issued.

### MINOR: Suggest to remove warning

Attempt to convert with:
``` 
.\IoT_App>csolution convert -s IoT_AppProposed.csolution.yml
```

This issues several warnings:
```
warning csolution: output option was not specified, files won't be copied for context 'AWS_MQTT_Proposed.Debug+Board-WiFi'
```

Alternatively this could be issued just once as 'info'


## MDK Importer Issues

1. For \*.cprj files   -> C99 should be default (as it is also default for project generation)
2. Question: why is AC5-like warning required to compile correctly, CBuild seems to work without it
3. Add-Paths should be not required for header files, CBuild does not require it
4. For the header file `MBEDTLS_CONFIG_FILE="aws_mbedtls_config.h"` remove the requirement to define it as `\"aws_mbedtls_config.h"\` (importer should add `\` to #define strings)

### Other MDK problems

- Why warning here:
```
Rebuild started: Project: AWS_MQTT_MutualAuth_Demo.Debug+Board-TCP
*** Using Compiler 'V6.16', folder: 'C:\Keil_v5\ARM\ARMCLANG\Bin'

Interfaces/FreeRTOS+TCP/iot_secure_sockets.c(33): warning: In file included from...
./amazon-freertos/libraries/abstractions/secure_sockets/include\iot_secure_sockets.h(67): warning: redefinition of typedef 'Socket_t' is a C11 feature [-Wtypedef-redefinition]
typedef struct xSOCKET * Socket_t; /**< @brief Socket handle data type. */
                         ^
C:/Keil_v5/ARM/PACK/AWS/FreeRTOS-Plus-TCP/2.3.2-Beta/libraries/standard/freertos_plus_tcp/include\FreeRTOS_Sockets.h(219): note: previous definition is here
    typedef struct xSOCKET         * Socket_t;
                                     ^
```

- Do we really need that many file groups in `App.clayer.yml`?

- Do we need to add every header file to the project; should this be reduced?

- Not sure why we add the NXP `*.MEX` file to the project.  What is the intention here?  Could we explain this in README?