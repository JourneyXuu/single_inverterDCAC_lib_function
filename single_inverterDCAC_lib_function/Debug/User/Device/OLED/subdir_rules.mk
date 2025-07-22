################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
User/Device/OLED/%.obj: ../User/Device/OLED/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="D:/A_Project/DSP_Project/Source/single_inverterDCAC_lib_function/single_inverterDCAC_lib_function/old_include" --include_path="D:/A_Project/DSP_Project/Source/single_inverterDCAC_lib_function/single_inverterDCAC_lib_function" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/A_Project/DSP_Project/Source/single_inverterDCAC_lib_function/single_inverterDCAC_lib_function/User" --include_path="D:/A_Project/DSP_Project/Source/single_inverterDCAC_lib_function/single_inverterDCAC_lib_function/User/App" --include_path="D:/A_Project/DSP_Project/Source/single_inverterDCAC_lib_function/single_inverterDCAC_lib_function/User/bsp" --include_path="D:/A_Project/DSP_Project/Source/single_inverterDCAC_lib_function/single_inverterDCAC_lib_function/User/Device/IIC" --include_path="D:/A_Project/DSP_Project/Source/single_inverterDCAC_lib_function/single_inverterDCAC_lib_function/User/Device/OLED" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="User/Device/OLED/$(basename $(<F)).d_raw" --obj_directory="User/Device/OLED" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


