################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
GrLib/fonts/fontfixed6x8.obj: ../GrLib/fonts/fontfixed6x8.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/Users/offba/iCloudDrive/___Spring2018 CU Boulder/ECEN3000_DDL_backup/FinalProject/finalproj_ccs/BOOSTXL-EDUMKII_MicrophoneFFT_MSP432P401R" --include_path="C:/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv8/ccs_base/arm/include" --include_path="C:/ti/ccsv8/ccs_base" --include_path="C:/Users/offba/iCloudDrive/___Spring2018 CU Boulder/ECEN3000_DDL_backup/FinalProject/finalproj_ccs/BOOSTXL-EDUMKII_MicrophoneFFT_MSP432P401R/driverlib/MSP432P4xx" --include_path="C:/Users/offba/iCloudDrive/___Spring2018 CU Boulder/ECEN3000_DDL_backup/FinalProject/finalproj_ccs/BOOSTXL-EDUMKII_MicrophoneFFT_MSP432P401R/GrLib/grlib" --include_path="C:/Users/offba/iCloudDrive/___Spring2018 CU Boulder/ECEN3000_DDL_backup/FinalProject/finalproj_ccs/BOOSTXL-EDUMKII_MicrophoneFFT_MSP432P401R/GrLib/fonts" --include_path="C:/Users/offba/iCloudDrive/___Spring2018 CU Boulder/ECEN3000_DDL_backup/FinalProject/finalproj_ccs/BOOSTXL-EDUMKII_MicrophoneFFT_MSP432P401R/LcdDriver" --include_path="C:/Users/offba/iCloudDrive/___Spring2018 CU Boulder/ECEN3000_DDL_backup/FinalProject/finalproj_ccs/BOOSTXL-EDUMKII_MicrophoneFFT_MSP432P401R/CMSIS/Include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=_LINKAGE --define=_CODE_ACCESS="" --define=_DATA_ACCESS="" --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="GrLib/fonts/fontfixed6x8.d_raw" --obj_directory="GrLib/fonts" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


