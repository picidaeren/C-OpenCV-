#include "monitor.hpp"


//Ptr <T>封装了一个指向T实例的指针和与该指针关联的引用计数器。

Ptr<BackgroundSubtractor> pMOG; //MOG Background subtractor
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
int keyboard;

char recordName[128];

void help();

int main(int argc, char* argv[]){
	bool showWindow = false;
	unsigned int method = 0, unnormal = 10, fps = 24;
	//判断参数
	if (argc > 6){
		cerr << "Invalid Parameters, Exiting..." << endl;
		exit(EXIT_FAILURE);
	}
	if (argc >= 2){
		if (strcmp(argv[1], "-vis") == 0)
			showWindow = true;
		if (strcmp(argv[1], "-h") == 0 ||
			strcmp(argv[1], "--help") == 0){
			help();
			exit(EXIT_SUCCESS);
		}
	}
	if (argc >= 3){
		if (strcmp(argv[2], "-mog2") == 0)
			method = 0;
		if (strcmp(argv[2], "-mog1") == 0)
			method = 1;
		if (strcmp(argv[2], "-src") == 0)
			method = 2;
	}
	if (argc >= 4){
		int param = stoi(argv[3], nullptr, 10);
		if (param <= 10)
			fps = 24;
		else
			fps = param;
	}
	if (argc >= 5){
		int param = stoi(argv[4], nullptr, 10);
		if (param <= 0)
			unnormal = 10;
		else
			unnormal = param;
	}
	if (argc >= 6){
		strcpy(recordName, argv[5]);
	}
	else{
		// set record video file name
		time_t t = time(NULL);
		sprintf(recordName, "%d.avi", t);
	}

	cout << "Starts After 2s..." << endl;
	Sleep(2000);
	if (showWindow)
		namedWindow("Monitor");

	pMOG = new BackgroundSubtractorMOG(); //MOG approach
	pMOG2 = new BackgroundSubtractorMOG2(); //MOG2 approach

	processCamera(showWindow, method, unnormal, fps);

	destroyAllWindows();
	return EXIT_SUCCESS;
}


void help(){
	cout
		<< "----------------------------------------------------------------------------\n"
		<< "Usage:                                                                      \n"
		<< " ./MonitorRecorder.exe [VIS] [MODE] [FPS] [THRESHOLD] [OUTPUTFILE]          \n"
		<< "   [VIS]  : use -vis 显示监视器窗口，否则它将运行后台。                       \n"
		<< "   [MODE] : -src   显示原始帧(未做任何出路);                                 \n"
		<< "            -mog1       显示MOG帧;                                          \n"
		<< "            -mog2      显示MOG2帧.                                          \n"
		<< "   [FPS]  : 设置记录文件的fps，默认为24.                                     \n"
		<< "   [THRESHOLD]                                                              \n"
		<< "          : 设置X号，监视器将在X个异常帧通过后开始录制                         \n"
		<< "   [OUTPUTFILE]                                                             \n"
		<< "          :分配输出记录文件。它必须是.avi格式，由force设计                    \n"
		<< "----------------------------------------------------------------------------\n";
}
