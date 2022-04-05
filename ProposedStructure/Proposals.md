# Proposal for Layer Support

## Example Project 

The example project has this structure

### Software Stack

Layer               | Board-TCP              | Board-WiFi            | AVH
:-------------------|:-----------------------|:----------------------|:--------------------------
App                 | MQTT Demo              | MQTT Demo             | MQTT Demo
Interface           | AWS FreeRTOS+TCP       | AWS WiFi              | AWS Socket
<Other>             |                        | Module ESP8266        | Socket VSocket
Board               | MIMXRT1050-EVKB        | MIMXRT1050-EVKB       | AVH_Cortex-M7


# References to Layers stored in Packs

It should be possible to reference Layers that are store in packs using *Access Sequences*

```yml
project:

  layers:
    - layer: ./App.clayer.yml

    - layer: ./Module/ESP8266/Module.clayer.yml
      for-type: 
        - +Board-WiFi

    - layer: ./Interfaces/FreeRTOS+TCP/Interface.clayer.yml   # should be ./Interface/AWS/FreeRTOS+TCP/Interface.clayer.yml
      for-type:
        - +Board-TCP

    - layer: ./Interfaces/Socket/Interface.clayer.yml         # should be ./Interface/AWS/Socket/Interface.clayer.yml
      for-type:
        - +VHT

    - layer: ./Interfaces/WiFi/Interface.clayer.yml           # should be ./Interface/AWS/WiFi/Interface.clayer.yml
      for-type:
        - +Board-WiFi

    - layer: ./Socket/VSocket/Socket.clayer.yml               # should this go to the VHT Board Layer?
      for-type:
        - +VHT

   - layer: {Board}
```

## Changes to the *.PDSC file

It should be possible to register several layers in a `*.PDSC file.  The actual layer
```xml
  <layers>
    <layer type="Board" name="./Board/MIMXRT1050-EVKB/Board.clayer.yml" directory="./clayers/Board/Basic"/>
    <layer type="Board" name="./Board/MIMXRT1050-EVKB/Board.clayer.yml" directory="./clayers/Board/AudioIO" condition="AudioIO"/>
    <layer type="Board" name="./Board/MIMXRT1050-EVKB/Board.clayer.yml" directory="./clayers/Board/SensorIO"/>
  </layers>
```
The required layer could be identified based on the `provided:` interfaces.


# RTE Directory

The RTE directory could be configurable

  target-types:
    - type: Board-WiFi         # for NXP EVKB_IMXRT1050 with ESP8266
      # board: EVKB-IMXRT1050_MDK
      device: MIMXRT1052DVL6B
      RTE-component-class:
       - Device: RT1052-WiFi   # ./RTE/Device/RT1052-WiFi

    - type: Board-TCP          # for NXP EVKB_IMXRT1050 with FreeRTOS_TCP wired Ethernet
      # board: EVKB-IMXRT1050_MDK
      device: MIMXRT1052DVL6B
      RTE-component-class:     # RTE Directory for config files for this target
       - Device: RT1052        # ./RTE/Device/RT1052
       - RTOS: Board-TCP       # ./RTE/Device/Board-TCP   (default could be target-type name)
