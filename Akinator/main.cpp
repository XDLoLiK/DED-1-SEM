/**
 * @defgroup   MAIN main
 *
 * @brief      This file implements main.
 *
 * @author     Stas
 * @date       2021
 */


#include "Akinator/Akinator.h"


int main()
{
	Logger_Init();
	
	Akinator_t akinator = {};
	Akinator_Ctor(&akinator);

	bool running = true;

	while (running) {

		Akinator_ChooseModeMassage();

		int playMode = -1;

		scanf("%d", &playMode);

		switch (playMode) {

			case -1:
				running = false;
				break;

			case 0:
				Akinator_PlayGame(&akinator);
				break;

			case 1:
				Akinator_Find(&akinator);
				break;

			case 2:
				Akinator_Compare(&akinator);
				break;

			case 3:
				Akinator_DumpTree(&akinator);
				break;

			case 4:
				Akinator_SwitchVoiceover(&akinator);
				break;

			default:
				running = false;
				break;
		}
	}

	Akinator_Dtor(&akinator);

	Logger_Finish();

	return 0;
}