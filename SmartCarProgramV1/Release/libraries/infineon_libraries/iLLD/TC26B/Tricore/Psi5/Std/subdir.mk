################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.c" 

COMPILED_SRCS += \
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.src" 

C_DEPS += \
"./libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.d" 

OBJS += \
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.o" 


# Each subdirectory must supply rules for building sources it contributes
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.src":"../libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.c" "libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.o":"libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.src" "libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Psi5-2f-Std

clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Psi5-2f-Std:
	-$(RM) ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.d ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.o ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Std/IfxPsi5.src

.PHONY: clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Psi5-2f-Std

