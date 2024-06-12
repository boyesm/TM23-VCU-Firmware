*** Settings ***
Suite Setup     Custom Setup
Suite Teardown  Custom Teardown



*** Variables ***
# These are the set upper and lower values of the actual APPS sensors. These are not programmable in firmware.
${LOWEST_VOLTAGE_OUTPUT_OF_APPS_1}    0.0
${HIGHEST_VOLTAGE_OUTPUT_OF_APPS_1}    5.0
${LOWEST_VOLTAGE_OUTPUT_OF_APPS_2}    0.0
${HIGHEST_VOLTAGE_OUTPUT_OF_APPS_2}    5.0

${LOWEST_INTEGER_OUTPUT_OF_APPS_1}    0
${HIGHEST_INTEGER_OUTPUT_OF_APPS_1}    0
${LOWEST_INTEGER_OUTPUT_OF_APPS_2}    0
${HIGHEST_INTEGER_OUTPUT_OF_APPS_2}    0

# This is equivalent to AVDD, maximum voltage values that ADC can read and DAC can output
${ANALOG_MAX_VOLTAGE}    5.0




*** Test Cases ***

# Pedal Causes Signal Out To Inverter

Pedal Reads Zero Travel At Rest
    # Enter mode that allows for movement
    Set APPS 1 Value    ${LOWEST_INTEGER_OUTPUT_OF_APPS_1}
    Set APPS 2 Value    ${LOWEST_INTEGER_OUTPUT_OF_APPS_2}
    Should Be Equal As Integers    Read DAC Value  0

    
*** Keywords ***
Custom Setup
    Setup
    ${out}=    Convert Voltage To 12-bit Integer    ${LOWEST_VOLTAGE_OUTPUT_OF_APPS_1}
    Set Global Variable    ${LOWEST_INTEGER_OUTPUT_OF_APPS_1}    ${out}
    ${out}=    Convert Voltage To 12-bit Integer    ${HIGHEST_VOLTAGE_OUTPUT_OF_APPS_1}
    Set Global Variable    ${HIGHEST_INTEGER_OUTPUT_OF_APPS_1}    ${out}
    ${out}=    Convert Voltage To 12-bit Integer    ${LOWEST_VOLTAGE_OUTPUT_OF_APPS_2}
    Set Global Variable    ${LOWEST_INTEGER_OUTPUT_OF_APPS_2}    ${out}
    ${out}=    Convert Voltage To 12-bit Integer    ${HIGHEST_VOLTAGE_OUTPUT_OF_APPS_2}
    Set Global Variable    ${HIGHEST_INTEGER_OUTPUT_OF_APPS_2}    ${out}

    Log    ${LOWEST_INTEGER_OUTPUT_OF_APPS_1}
    Log    ${HIGHEST_INTEGER_OUTPUT_OF_APPS_1}
    Log    ${LOWEST_INTEGER_OUTPUT_OF_APPS_2}
    Log    ${HIGHEST_INTEGER_OUTPUT_OF_APPS_2}
    
    Execute Command           set bin @${CURDIR}/../cmake-build-debug/TM23-VCU-Firmware.elf
    Execute Command           include @${CURDIR}/stm32f446nucleo.resc
    Start Emulation

    Create Terminal Tester    sysbus.usart2
    
    Wait For Line On Uart    System initialized.
    
    # Turn on the ADCs
    Enable APPS 1
    Enable APPS 2
    Enable BPS


Custom Teardown
    # custom teardown code here
    Teardown


Enable APPS 1
    Execute Command    adc1 WriteDoubleWord 0x08 0x40000401


Enable APPS 2
    Execute Command    adc2 WriteDoubleWord 0x08 0x40000401


Enable BPS
    Execute Command    adc3 WriteDoubleWord 0x08 0x40000401


Set APPS 1 Value
    [Arguments]    ${value_to_set}
    Execute Command    adc1 FeedSample ${value_to_set} 0
    Execute Command    adc1 WriteDoubleWord 0x08 0x40000401


Set APPS 2 Value
    [Arguments]    ${value_to_set}
    Execute Command    adc2 FeedSample ${value_to_set} 1
    Execute Command    adc2 WriteDoubleWord 0x08 0x40000401


Set BPS Value
    [Arguments]    ${value_to_set}
    Execute Command    adc3 FeedSample ${value_to_set} 10
    Execute Command    adc3 WriteDoubleWord 0x08 0x40000401


Read DAC Value
    ${read_dac_value}=    Execute Command    dac ReadDoubleWord 0x2C
    ${read_dac_value}=    Convert To Integer    ${read_dac_value}
    [return]    ${read_dac_value}


Convert Voltage To 12-bit Integer
    [Arguments]    ${voltage}
    ${result}=    Evaluate    ${voltage} / ${ANALOG_MAX_VOLTAGE} * 4095
    ${result}=    Convert To Integer    ${result}
    [Return]    ${result}