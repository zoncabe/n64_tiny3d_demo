BUILD_DIR=build

include $(N64_INST)/include/n64.mk
include $(T3D_INST)/t3d.mk

N64_CFLAGS += -std=gnu2x
GLTF_FLAGS = '--base-scale=1'

PROJECT_NAME = game

src =   $(wildcard *.c) \
		$(wildcard src/game/*.c) \
		$(wildcard src/screen/*.c) \
		$(wildcard src/time/*.c) \
		$(wildcard src/physics/math/*.c) \
		$(wildcard src/physics/body/*.c) \
		$(wildcard src/physics/collision/*.c) \
		$(wildcard src/physics/collision/shapes/*.c) \
		$(wildcard src/viewport/*.c) \
		$(wildcard src/control/*.c) \
		$(wildcard src/actor/*.c) \
		$(wildcard src/scene/*.c) \
		$(wildcard src/player/*.c) \
		$(wildcard src/ui/*.c) \
		$(wildcard src/graphics/*.c) \
		$(wildcard src/memory/*.c) \
		$(wildcard src/render/*.c) \
		$(wildcard src/assets/*.c) \
# $(wildcard src/physics/player_collision/*.c) \

assets_png = $(wildcard assets/textures/*.png)
assets_gltf = $(wildcard assets/models/*.glb)
assets_ttf = $(wildcard assets/fonts/*.ttf)
assets_conv = $(addprefix filesystem/textures/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/models/,$(notdir $(assets_gltf:%.glb=%.t3dm))) \
			  $(addprefix filesystem/fonts/,$(notdir $(assets_ttf:%.ttf=%.font64)))

all: $(PROJECT_NAME).z64

filesystem/textures/%.sprite: assets/textures/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem/textures "$<"


filesystem/models/mannequin.t3dm: GLTF_FLAGS = --base-scale=100

filesystem/models/%.t3dm: assets/models/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) $(GLTF_FLAGS) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o filesystem/models $@


filesystem/fonts/%.font64: assets/fonts/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -s 9 -o filesystem/fonts "$<"

$(BUILD_DIR)/$(PROJECT_NAME).dfs: $(assets_conv)
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(src:%.c=$(BUILD_DIR)/%.o)

$(PROJECT_NAME).z64: N64_ROM_TITLE="demo"
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
