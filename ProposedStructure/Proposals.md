# Proposal for Layer Support

This contains some proposals the [**Project Setup for Multiple Targets and Builds**](https://github.com/Open-CMSIS-Pack/devtools/blob/main/tools/projmgr/docs/Manual/Overview.md#project-setup-for-multiple-targets-and-builds).


## Example Project 

The current AWS example project has this structure.  It is basically configurable to three different interfaces: Ethernet, WiFi, Socket.


Layer               | Board-TCP              | Board-WiFi            | AVH
:-------------------|:-----------------------|:----------------------|:--------------------------
App                 | MQTT Demo              | MQTT Demo             | MQTT Demo
Interface           | AWS FreeRTOS+TCP       | AWS WiFi              | AWS Socket
\<Other\>           |                        | Module ESP8266        | Socket VSocket
Board               | MIMXRT1050-EVKB        | MIMXRT1050-EVKB       | AVH_Cortex-M7

Could the layers be further simplified, for example to:

Layer               | Ethernet               | WiFi                           | Socket
:-------------------|:-----------------------|:-------------------------------|:--------------------------
App                 | MQTT Demo              | MQTT Demo                      | MQTT Demo
Interface           | AWS FreeRTOS+TCP       | AWS WiFi                       | AWS Socket
Board               | MIMXRT1050-EVKB        | MIMXRT1050-EVKB (+ESP8266)     | AVH_Cortex-M7 (+VSocket)

When `{Board}` layers are stored in packs, the encoded features could indicate if a configuration would work or not.

Potentially, the `{Board}` layer `provided:` interfaces could be reduced to:
  - Communication: Ethernet, WiFi, Socket
  - Input: Audio, Sensor
  - Output: Audio


## References to Layers stored in Packs

It should be possible to reference Layers that are store in packs using *Access Sequences*, in this proposal using `{` `}`.
A project could then look like:

```yml
project:

# insert content from layer: ./App.clayer.yml

  layers:

    - layer: ./Interfaces/FreeRTOS+TCP/Interface.clayer.yml   # should be ./Interface/AWS/FreeRTOS+TCP/Interface.clayer.yml
      for-type:
        - +Ethernet

    - layer: ./Interfaces/Socket/Interface.clayer.yml         # should be ./Interface/AWS/Socket/Interface.clayer.yml
      for-type:
        - +Socket

    - layer: ./Interfaces/WiFi/Interface.clayer.yml           # should be ./Interface/AWS/WiFi/Interface.clayer.yml
      for-type:
        - +WiFi

   - layer: {Board}
```

The `csolution` tool would issue an error when a `{Board}` layer does not exist that covers the `required:` interfaces.

## Changes to the *.PDSC file

It should be possible to register several layers in a `*.PDSC` file.  The actual layers could look like:
```xml
  <csolution>
    <clayer type="Board" name="./Board/MIMXRT1050-EVKB/Board.clayer.yml" directory="./clayers/Board/Basic"/>
    <clayer type="Board" name="./Board/MIMXRT1050-EVKB/Board.clayer.yml" directory="./clayers/Board/WiFi"/>
    <clayer type="Board" name="./Board/MIMXRT1050-EVKB/Board.clayer.yml" directory="./clayers/Board/Ethernet"/>
    <clayer type="Board" name="./Board/MIMXRT1050-EVKB/Board.clayer.yml" directory="./clayers/Board/AudioIO" condition="AudioIO"/>
    <clayer type="Board" name="./Board/MIMXRT1050-EVKB/Board.clayer.yml" directory="./clayers/Board/SensorIn"/>
  </csolution>
```
The required layer could be identified based on the `provided:` interfaces.

The `<csolution>` element could also contain different types with:
  - `cproject` a generic example projects
  - `cimage` a pre-build image that should be added to a csolution
  - `clayer` a software layer 
  

```xml
  <csolution>
    <cproject type="Blinky" name="./Blinky.cproject.yml" directory="./Examples/Blinky"/>
    <cimage type="TFM" name="./TFM/TFM.axf" directory="./Security/TFM" condition="Secure"/>
    <clayer .../>
  </csolution>
```

### Board Layer from Pack to Project

The directory structure of a board layer in the software pack could be:
```
./clayers/Board/WiFi/                          # base directory of the WiFi configuration
./clayers/Board/WiFi/Board/MIMXRT1050-EVKB     # clayer.yml and other source files
./clayers/Board/WiFi/RTE                       # component configurations of the Baord layer
```

A {Board} layer is copied by the `csolution` tool to the project with this structure:
```
./RTE                                          # component configurations of the Baord layer
./Board/MIMXRT1050-EVKB                        # clayer.yml and other source files
```

When it is copied a file `Board.clayer.txt` is created that contains information about:
  - the original pack that contained the layer.
  - the variant of the layer that is copied.
  - optionally some version information.
  
The `csolution` tool does not copy the layer when:
  - there is already a `Board.clayer.txt` in the target directory
  - a existing file in the `RTE` directory would be overwritten
  
The `csolution` tool issues no warning when the `Board.clayer.txt` indicates that the selected layer has the same variant/version.

The *Access Sequence* `{Board}` in the `*.cproject.yml` is replaced by `name` of the selected `*.PDSC` file element:
```
./Board/MIMXRT1050-EVKB/Board.clayer.yml
```


## RTE Directory

### RTE Component directories configurable

In the current proposal, all components share the same configuration across the different `target-types`. This is normally ideal
as the configuration is in many cases shared and identical.  

However there might be situations where the configuration of components, for example for the `Board` should be different.  
This could be supported by adding the node `RTE-component-class:` to the `target-types:` list in the `*.csolution.yml` file as shown below.

```yml
  target-types:
    - type: Board-WiFi         # for NXP EVKB_IMXRT1050 with ESP8266
      board: EVKB-IMXRT1050_MDK
      RTE-component-class:
       - Board: RT1052-WiFi   # ./RTE/Board/RT1052-WiFi

    - type: Board-TCP          # for NXP EVKB_IMXRT1050 with FreeRTOS_TCP wired Ethernet
      board: EVKB-IMXRT1050_MDK
      RTE-component-class:     # RTE Directory for config files for this target
       - Device: RT1052        # ./RTE/Device/RT1052
       - RTOS: Board-TCP       # ./RTE/Device/Board-TCP   (default could be target-type name)
```

### RTE Base Directory

Likewise the RTE Base directory could be configurable, but currently the use case for this is unclear.  For example:
```yml
   RTE-base:  .\RTE2           # change the default .\RTE directory to .\RTE2
```

