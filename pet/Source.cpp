#define ASLIB_INCLUDE_DL
#include <AsLib.hpp>

struct Pet {
	AnimeUI ui;
	int32_t hp = 0;

	Pet() = default;
	const Pet(const AnimeMainData* const add_tmd, const uint8_t add_alpha, const Pos4& add_pos4, const int32_t hp_) :ui(add_tmd, add_alpha, add_pos4), hp(hp_) {}
	const Pet(const AnimeMainData* const add_tmd, const uint8_t add_alpha, const PosA4R& add_pos4, const int32_t hp_) : ui(add_tmd, add_alpha, add_pos4), hp(hp_) {}
};

int32_t asMain()
{
	MainControl as(u8"a", Pos2(540, 960));

	//アニメーションファイル
	const AnimeMainData petA(5, AsLoadTex(u8"Picture/Pet/pet.png", 5));
	//画像ファイル
	const TextureMainData bg(AsLoadTex(u8"Picture/BG/bg.png"));

	//アニメーション管理ファイル
	Pet pet(&petA, 255, PosA4R(100.0f, 100.0f, 50.0f, 50.0f), 10);

	while (asLoop())
	{
		bg.draw();
		pet.ui.fpsUpdate().addSizeF(Pos2R(0.1f, 0.1f)).drawF();
	}

	return 0;
}