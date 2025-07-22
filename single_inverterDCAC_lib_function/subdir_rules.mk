################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
USER/%.obj: ../USER/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_18.12.4.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -O3 --include_path="D:/ti/workspacewk/DCAC_069/DCAC_069" --include_path="D:/ti/workspacewk/DCAC_069/DCAC_069/headers/include" --include_path="D:/ti/workspacewk/DCAC_069/DCAC_069/Include" --include_path="D:/ti/workspacewk/DCAC_069/DCAC_069/IQmath/c28/include" --include_path="D:/ti/workspacewk/DCAC_069/DCAC_069/IQmath/c28/lib" --include_path="D:/ti/workspacewk/DCAC_069/DCAC_069/common/include" --include_path="D:/ti/workspacewk/DCAC_069/DCAC_069/common/source" --include_path="D:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_18.12.4.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="USER/$(basename $(<F)).d_raw" --obj_directory="USER" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


