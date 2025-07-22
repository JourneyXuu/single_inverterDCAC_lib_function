################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
old_source/%.obj: ../old_source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_18.12.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="E:/dianzishejijingsai069/chufaADC/single_inverter" --include_path="E:/dianzishejijingsai069/chufaADC/single_inverter/old_include" --include_path="E:/dianzishejijingsai069/single_phase_inverter/headers/cmd" --include_path="E:/dianzishejijingsai069/single_phase_inverter/common/cmd" --include_path="E:/dianzishejijingsai069/single_phase_inverter/headerfilesinmain" --include_path="E:/dianzishejijingsai069/single_phase_inverter/headers/include" --include_path="E:/dianzishejijingsai069/single_phase_inverter/common/include" --include_path="E:/dianzishejijingsai069/single_phase_inverter/Include" --include_path="E:/dianzishejijingsai069/single_phase_inverter/IQmath" --include_path="E:/dianzishejijingsai069/single_phase_inverter/source" --include_path="D:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_18.12.4.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="old_source/$(basename $(<F)).d_raw" --obj_directory="old_source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


