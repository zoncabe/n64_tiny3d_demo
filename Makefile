BUILD_DIR=build

include $(N64_INST)/include/n64.mk
include $(T3D_INST)/t3d.mk

N64_CFLAGS += -std=gnu2x

src = main.c

assets_png = $(wildcard assets/*.png)
assets_gltf = $(wildcard assets/*.glb)
assets_ttf = $(wildcard assets/*.ttf)
assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/,$(notdir $(assets_gltf:%.glb=%.t3dm))) \
			  $(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64))) 

all: game.z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"


filesystem/%.t3dm: assets/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) "$<" $@ --base-scale=1
	$(N64_BINDIR)/mkasset -c 2 -o filesystem $@

filesystem/%.font64: assets/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -s 9 -o filesystem "$<"

$(BUILD_DIR)/game.dfs: $(assets_conv)
$(BUILD_DIR)/game.elf: $(src:%.c=$(BUILD_DIR)/%.o)

game.z64: N64_ROM_TITLE="Tiny3D - Model"
game.z64: $(BUILD_DIR)/game.dfs

clean:
	rm -rf $(BUILD_DIR) *.z64
	rm -rf filesystem

build_lib:
	rm -rf $(BUILD_DIR) *.z64
	make -C $(T3D_INST)
	make all

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
