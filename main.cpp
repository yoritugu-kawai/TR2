#include <Novice.h>
#include <cmath>
const char kWindowTitle[] = "カワイヨリツグ_タイトル";
int law(unsigned int red, unsigned int  green, unsigned int blue, int  alpha)
{
	//unsigned char top = 0x;
	int color = (red << 24) | (green << 16) | (blue << 8) | alpha;
	return color;
}
int clamp(int suteji, int min, int max) {
	if (suteji <= min) return min;
	if (suteji >= max) return max;
	return suteji;
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	float Red = 255.0f;
	float Green = 255.0f;
	float Blue = 255.0f;
	int Color = 255;

	int s = 50;
	float distance = 2.0f;
	float changeRate = 0.0f;
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	int k = Novice::LoadTexture("./fog1.png");
	int j = Novice::LoadTexture("./mountain.png");
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		changeRate = 1.0f / log(distance * 2);
		float blueNew = Blue * changeRate;
		float greenNew = Green * changeRate;
		float redNew = Red * changeRate;
		///
		/// ↑更新処理ここまで
		///

		if (keys[DIK_UP]) {

			Color += 1;
		}
		if (keys[DIK_DOWN]) {

			Color -= 1;
		}


		Color = clamp(Color, 0, 255);
		///
		/// ↓描画処理ここから
		///
		Novice::DrawSprite(0, 0, j, 1, 1, 0.0f, 0xffffffff);
		Novice::DrawSprite(0, 0, k, 1, 1, 0.0f, law(redNew, greenNew, blueNew, Color));
		Novice::DrawSprite(100, 0, j, 1, 1, 0.0f, 0xffffffff);
		Novice::DrawSprite(0, 0, k, 1, 1, 0.0f, law(redNew, greenNew, blueNew, Color));
		Novice::DrawSprite(500, 0, j, 1, 1, 0.0f, 0xffffffff);
		Novice::DrawSprite(0, 0, k, 1, 1, 0.0f, law(redNew, greenNew, blueNew, Color));
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
