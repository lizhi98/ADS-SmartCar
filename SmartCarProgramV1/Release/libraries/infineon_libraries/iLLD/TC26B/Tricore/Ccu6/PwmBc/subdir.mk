################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.c" 

COMPILED_SRCS += \
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.src" 

C_DEPS += \
"./libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.d" 

OBJS += \
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.o" 


# Each subdirectory must supply rules for building sources it contributes
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.src":"../libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.c" "libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.o":"libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.src" "libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Ccu6-2f-PwmBc

clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Ccu6-2f-PwmBc:
	-$(RM) ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.d ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.o ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.src

.PHONY: clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Ccu6-2f-PwmBc

