BUILD_DIR=build

include $(N64_INST)/include/n64.mk
include $(T3D_INST)/t3d.mk

N64_CFLAGS += -std=gnu2x
GLTF_FLAGS = '--base-scale=1'

PROJECT_NAME = game

# src := $(shell find -type f -name '*.c')
src =   $(wildcard *.c) \
		$(wildcard src/screen/*.c) \
		$(wildcard src/time/*.c) \
		$(wildcard src/physics/math/*.c) \
		$(wildcard src/physics/collision/*.c) \
		$(wildcard src/physics/actor_collision/*.c) \
		$(wildcard src/physics/collision/shapes/*.c) \
		$(wildcard src/control/*.c) \
		$(wildcard src/camera/*.c) \
		$(wildcard src/actor/*.c) \
		$(wildcard src/game/*.c) \
		$(wildcard src/player/*.c) \
		$(wildcard src/scene/*.c) \
		$(wildcard src/ui/*.c) \
		$(wildcard src/memory/*.c) \

assets_png = $(wildcard assets/*.png)
assets_gltf = $(wildcard assets/*.glb)
assets_ttf = $(wildcard assets/*.ttf)
assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/,$(notdir $(assets_gltf:%.glb=%.t3dm))) \
			  $(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64)))

all: $(PROJECT_NAME).z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"


filesystem/brew_logo.t3dm: GLTF_FLAGS = --base-scale=64

filesystem/%.t3dm: assets/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) $(GLTF_FLAGS) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o filesystem $@


filesystem/%.font64: assets/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -s 9 -o filesystem "$<"

$(BUILD_DIR)/$(PROJECT_NAME).dfs: $(assets_conv)
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(src:%.c=$(BUILD_DIR)/%.o)

$(PROJECT_NAME).z64: N64_ROM_TITLE="engine64demo"
$(PROJECT_NAME).z64: $(BUILD_DIR)/$(PROJECT_NAME).dfs

clean:
	rm -rf $(BUILD_DIR) *.z64
	rm -rf filesystem

build_lib:
	rm -rf $(BUILD_DIR) *.z64
	make -C $(T3D_INST)
	make all

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
