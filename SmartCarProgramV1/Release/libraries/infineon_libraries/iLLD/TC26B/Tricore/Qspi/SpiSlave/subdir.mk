################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.c" 

COMPILED_SRCS += \
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.src" 

C_DEPS += \
"./libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.d" 

OBJS += \
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.o" 


# Each subdirectory must supply rules for building sources it contributes
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.src":"../libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.c" "libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.o":"libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.src" "libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Qspi-2f-SpiSlave

clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Qspi-2f-SpiSlave:
	-$(RM) ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.d ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.o ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.src

.PHONY: clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Qspi-2f-SpiSlave
