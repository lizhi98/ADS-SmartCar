################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/encoder.c" \
"../code/image.c" \
"../code/motor.c" \
"../code/pid.c" \
"../code/screen.c" \
"../code/steer.c" \
"../code/uartWireless.c" 

COMPILED_SRCS += \
"code/encoder.src" \
"code/image.src" \
"code/motor.src" \
"code/pid.src" \
"code/screen.src" \
"code/steer.src" \
"code/uartWireless.src" 

C_DEPS += \
"./code/encoder.d" \
"./code/image.d" \
"./code/motor.d" \
"./code/pid.d" \
"./code/screen.d" \
"./code/steer.d" \
"./code/uartWireless.d" 

OBJS += \
"code/encoder.o" \
"code/image.o" \
"code/motor.o" \
"code/pid.o" \
"code/screen.o" \
"code/steer.o" \
"code/uartWireless.o" 


# Each subdirectory must supply rules for building sources it contributes
"code/encoder.src":"../code/encoder.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/encoder.o":"code/encoder.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/image.src":"../code/image.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/image.o":"code/image.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/motor.src":"../code/motor.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/motor.o":"code/motor.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/pid.src":"../code/pid.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/pid.o":"code/pid.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/screen.src":"../code/screen.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/screen.o":"code/screen.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/steer.src":"../code/steer.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/steer.o":"code/steer.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/uartWireless.src":"../code/uartWireless.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Sync/SmartCar/SmartCarProgram01/Release/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/uartWireless.o":"code/uartWireless.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code

clean-code:
	-$(RM) ./code/encoder.d ./code/encoder.o ./code/encoder.src ./code/image.d ./code/image.o ./code/image.src ./code/motor.d ./code/motor.o ./code/motor.src ./code/pid.d ./code/pid.o ./code/pid.src ./code/screen.d ./code/screen.o ./code/screen.src ./code/steer.d ./code/steer.o ./code/steer.src ./code/uartWireless.d ./code/uartWireless.o ./code/uartWireless.src

.PHONY: clean-code

