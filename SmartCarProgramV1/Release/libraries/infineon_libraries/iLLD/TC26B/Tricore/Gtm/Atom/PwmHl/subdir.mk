################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.c" 

COMPILED_SRCS += \
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.src" 

C_DEPS += \
"./libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.d" 

OBJS += \
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.o" 


# Each subdirectory must supply rules for building sources it contributes
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.src":"../libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.c" "libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.o":"libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.src" "libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Gtm-2f-Atom-2f-PwmHl

clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Gtm-2f-Atom-2f-PwmHl:
	-$(RM) ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.d ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.o ./libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Atom/PwmHl/IfxGtm_Atom_PwmHl.src

.PHONY: clean-libraries-2f-infineon_libraries-2f-iLLD-2f-TC26B-2f-Tricore-2f-Gtm-2f-Atom-2f-PwmHl
