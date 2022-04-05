# Issues

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

For initial project setup just the original config file should be stored under name `.ConfigFile.h@1.2.0`.  See #1 under https://github.com/Open-CMSIS-Pack/devtools/blob/main/tools/projmgr/docs/Manual/Overview.md#plm-of-configuration-files

### Proposed Directories (IntDir, OutDir)

Just in the project directory that stores the local `*.cproject.yml` file with this structure
.\IntDir
.\IntDir\.Debug+Board            // holds all intermediated files including the `.o` files
.\OutDir\Board                   // holds the output binary including map files.  All builds share same so that Project1 debug can be intermixed with Project2 release (testing different build combinations when required)


## MDK Importer Issues

For \*.cprj files   -> C99 should be default (as it is also default for project generation)
Question: why is AC5-like warning required to compile correctly, CBuild seems to work without it
Add-Paths should be not required for header files, CBuild does not require it
For the header file `MBEDTLS_CONFIG_FILE="aws_mbedtls_config.h"` remove the requirement to define it as `\"aws_mbedtls_config.h"\` (importer should add `\` to #define strings)
