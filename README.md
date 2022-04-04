# IoT_App (AWS_MQTT_MutualAuth_Demo)

This is WiP and shows a project that uses clayers and creates there different targets:
- Board-WiFi: IMXRT1050 board with ESP8266 module connecting via WiFi using built-in sockets
- Board-TCP: IMXRT1050 board connecting via Ethernet using FreeRTOS+ TCP for sockets
- VHT: VHT for Cortex-M using VSocket

Trying out the demo:

>NOTE:  RQUIRED ARE EXACTLY THIS VERSIONS OF THE NXP PACKS (These are not yet checked by the tool):
>   - pack: NXP::MIMXRT1052_DFP@13.1.0
>   - pack: NXP::EVKB-IMXRT1050_BSP@13.1.0
>   - pack: Keil::IMXRT1050-EVKB_BSP@1.0.0
>   - pack: Keil::iMXRT105x_MWP@1.4.0

1. Ensure that you have installed all the required packs (packs are listed as comments in the relevant clayer.yml file). It is required to use the exact pack versions at least for the IMXRT1051 related packs.

2. Ensure that CMSIS-Toolbox 0.9.3 is installed

3. Check-out the repo IoT_App into a local directory

4. Run bash terminal in the root directory of the repo

5. Setup CMSIS-Toolbox (adjust example bellow to your installation)
$ source /c/CMSIS-Toolbox/etc/setup

6. Create the .cprj files using csolution (in test directory)
$ csolution convert -s IoT_App.csolution.yml -o test

7. Two ways to generate the project: 
    - Variant A: Build .cprj in the created directories if desired – each project has its own fully contained directory (example below)
    $ cbuild.sh test/AWS_MQTT_MutualAuth_Demo.Release+VHT/AWS_MQTT_MutualAuth_Demo.Debug+VHT.cprj

    - Variant B: Build .cprj from a combined directory
    Manually create a directory (ex: AWS_MQTT_MutualAuth_Demo) and copy all other project directories (AWS_MQTT_MutualAuth_Demo.\*) to it - skip identical files.
    Now all project are in the combined directory and can be built using cbuid (for example):
    $ cbuild.sh test/AWS_MQTT_MutualAuth_Demo/AWS_MQTT_MutualAuth_Demo.Debug+VHT.cprj

>Note about warnings during build:
- 2 warnings are expected related to missing credentials  
