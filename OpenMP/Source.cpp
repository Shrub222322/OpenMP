#include <iostream>
#include <omp.h>	
#include <raylib.h>
#include <complex>
#include <vector>
#include <chrono>

const double WIDTH = 800;
const double HEIGHT = 600;
const double MAX_ITERATIONS = 1000;

double minReal = -2.0;
double maxReal = 1.0;
double minImag = -1.5;
double maxImag = 1.5;
// these capture the image pretty well
std::vector<int> ThreadCounts;

/*
while(((x*x + y*y) <= 4) && iter <= max_iteration ){
        xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
        iter = iter + 1;
    } https://github.com/bjohnsonfl/Mandelbrot/blob/master/mandelbrot.cpp
*/

void mandlebrot(std::vector<Color>& pixelBuffer)
{
    int numThreads = 0;
    for (int y = 0; y < (int)HEIGHT; y++) {
        for (int x = 0; x < (int)WIDTH; x++) {

          
            double Xval = minReal + (x / WIDTH) * (maxReal - minReal);
            double Yval = minImag + (y / HEIGHT) * (maxImag - minImag);

         
            double xbelow = 0.0;
            double ybelow = 0.0;
            int iterations = 0;

           
            while ((xbelow * xbelow + ybelow * ybelow) <= 4.0 && iterations < MAX_ITERATIONS) {
                double temp = (xbelow * xbelow) - (ybelow * ybelow) + Xval;
                ybelow = 2.0 * xbelow * ybelow + Yval;
                xbelow = temp;
                iterations++;
            }

            
            int index = y * WIDTH + x;
            if (iterations == MAX_ITERATIONS) {
                pixelBuffer[index] = BLUE; 
            }
            else {
                
                unsigned char intensity = (unsigned char)((iterations / MAX_ITERATIONS) * 255);
                pixelBuffer[index] = Color{ intensity, intensity, intensity, 255 };
            }
        }
        numThreads = omp_get_num_threads();

    }
    std::cout << "Number of threads: " << numThreads << " Serial" << std::endl;
	ThreadCounts.push_back(numThreads);
}

void mandlebrotGuided(std::vector<Color>& pixelBuffer)
{
    int numThreads = 0;
#pragma omp parallel for schedule(guided) num_threads(8)
    for (int y = 0; y < (int)HEIGHT; y++) {
        for (int x = 0; x < (int)WIDTH; x++) {

           
            double Xval = minReal + (x / WIDTH) * (maxReal - minReal);
            double Yval = minImag + (y / HEIGHT) * (maxImag - minImag);


            double xbelow = 0.0;
            double ybelow = 0.0;
            int iterations = 0;


            while ((xbelow * xbelow + ybelow * ybelow) <= 4.0 && iterations < MAX_ITERATIONS) {
                double temp = (xbelow * xbelow) - (ybelow * ybelow) + Xval;
                ybelow = 2.0 * xbelow * ybelow + Yval;
                xbelow = temp;
                iterations++;
            }

           
            int index = y * WIDTH + x;
            if (iterations == MAX_ITERATIONS) {
                pixelBuffer[index] = BLUE; 
            }
            else {
                
                unsigned char intensity = (unsigned char)((iterations / MAX_ITERATIONS) * 255);
                pixelBuffer[index] = Color{ intensity, intensity, intensity, 255 };
            }
        }
        numThreads = omp_get_num_threads();

    }
    std::cout << "Number of threads: " << numThreads << " Guided" << std::endl;
    ThreadCounts.push_back(numThreads);
}

void mandlebrotStatic(std::vector<Color>& pixelBuffer)
{
    int numThreads = 0;
#pragma omp parallel for schedule(static) num_threads(8)
    for (int y = 0; y < (int)HEIGHT; y++) {
        for (int x = 0; x < (int)WIDTH; x++) {

            
            double Xval = minReal + (x / WIDTH) * (maxReal - minReal);
            double Yval = minImag + (y / HEIGHT) * (maxImag - minImag);


            double xbelow = 0.0;
            double ybelow = 0.0;
            int iterations = 0;


            while ((xbelow * xbelow + ybelow * ybelow) <= 4.0 && iterations < MAX_ITERATIONS) {
                double temp = (xbelow * xbelow) - (ybelow * ybelow) + Xval;
                ybelow = 2.0 * xbelow * ybelow + Yval;
                xbelow = temp;
                iterations++;
            }

           
            int index = y * WIDTH + x;
            if (iterations == MAX_ITERATIONS) {
                pixelBuffer[index] = BLUE; 
            }
            else {
                
                unsigned char intensity = (unsigned char)((iterations / MAX_ITERATIONS) * 255);
                pixelBuffer[index] = Color{ intensity, intensity, intensity, 255 };
            }
        }
        numThreads = omp_get_num_threads();

    }
    std::cout << "Number of threads: " << numThreads << " Static" << std::endl;
    ThreadCounts.push_back(numThreads);
}

void mandlebrotDynamic(std::vector<Color>& pixelBuffer)
{
    int numThreads = 0;

 #pragma omp parallel for schedule(dynamic) num_threads(8)
    for (int y = 0; y < (int)HEIGHT; y++) {
        for (int x = 0; x < (int)WIDTH; x++) {

           
            double Xval = minReal + (x / WIDTH) * (maxReal - minReal);
            double Yval = minImag + (y / HEIGHT) * (maxImag - minImag);


            double xbelow = 0.0;
            double ybelow = 0.0;
            int iterations = 0;


            while ((xbelow * xbelow + ybelow * ybelow) <= 4.0 && iterations < MAX_ITERATIONS) {
                double temp = (xbelow * xbelow) - (ybelow * ybelow) + Xval;
                ybelow = 2.0 * xbelow * ybelow + Yval;
                xbelow = temp;
                iterations++;
            }

           
            int index = y * WIDTH + x;
            if (iterations == MAX_ITERATIONS) {
                pixelBuffer[index] = BLUE; 
            }
            else {
             
                unsigned char intensity = (unsigned char)((iterations / MAX_ITERATIONS) * 255);
                pixelBuffer[index] = Color{ intensity, intensity, intensity, 255 };
            }
        }
		numThreads = omp_get_num_threads();
        
    }
	std::cout << "Number of threads: " << numThreads << " Dynamic" << std::endl;
    ThreadCounts.push_back(numThreads);

}

void mandlebrotStaticCyclic(std::vector<Color>& pixelBuffer)
{
    int numThreads = 0;
#pragma omp parallel for schedule(static,1) num_threads(8)
    for (int y = 0; y < (int)HEIGHT; y++) {
        for (int x = 0; x < (int)WIDTH; x++) {

            
            double Xval = minReal + (x / WIDTH) * (maxReal - minReal);
            double Yval = minImag + (y / HEIGHT) * (maxImag - minImag);


            double xbelow = 0.0;
            double ybelow = 0.0;
            int iterations = 0;


            while ((xbelow * xbelow + ybelow * ybelow) <= 4.0 && iterations < MAX_ITERATIONS) {
                double temp = (xbelow * xbelow) - (ybelow * ybelow) + Xval;
                ybelow = 2.0 * xbelow * ybelow + Yval;
                xbelow = temp;
                iterations++;
            } 
           
            int index = y * WIDTH + x;

            if (iterations == MAX_ITERATIONS) {
                pixelBuffer[index] = BLUE; 
            }
            else {
                
                unsigned char intensity = (unsigned char)((iterations / MAX_ITERATIONS) * 255);
                pixelBuffer[index] = Color{ intensity, intensity, intensity, 255 };
            }
        }
        numThreads = omp_get_num_threads();

    }
    std::cout << "Number of threads: " << numThreads << " Static Cyclic" << std::endl;
    ThreadCounts.push_back(numThreads);
}

void mandlebrotDynCyclicBlock(std::vector<Color>& pixelBuffer)
{
    int numThreads = 0;
#pragma omp parallel for schedule(dynamic, 2) num_threads(8)  //It will assign 2 rows to each thread at a time and then reassign as threads finish. also close to static cyclic and dynamic sometimes.
    for (int y = 0; y < (int)HEIGHT; y++) {
        for (int x = 0; x < (int)WIDTH; x++) {


            double Xval = minReal + (x / WIDTH) * (maxReal - minReal);
            double Yval = minImag + (y / HEIGHT) * (maxImag - minImag);


            double xbelow = 0.0;
            double ybelow = 0.0;
            int iterations = 0;


            while ((xbelow * xbelow + ybelow * ybelow) <= 4.0 && iterations < MAX_ITERATIONS) {
                double temp = (xbelow * xbelow) - (ybelow * ybelow) + Xval;
                ybelow = 2.0 * xbelow * ybelow + Yval;
                xbelow = temp;
                iterations++;
            }

            int index = y * WIDTH + x;

            if (iterations == MAX_ITERATIONS) {
                pixelBuffer[index] = BLUE;
            }
            else {

                unsigned char intensity = (unsigned char)((iterations / MAX_ITERATIONS) * 255);
                pixelBuffer[index] = Color{ intensity, intensity, intensity, 255 };
            }
        }
        numThreads = omp_get_num_threads();

    }
    std::cout << "Number of threads: " << numThreads << " Dynamic Cyclic Block" << std::endl;
    ThreadCounts.push_back(numThreads);
}

void mandlebrotStaticCyclicBlock(std::vector<Color>& pixelBuffer)
{
    int numThreads = 0;
#pragma omp parallel for schedule(static,4) num_threads(8)// 17 seems to be the best after multiple tries what an odd number on 12 sometimes 2 is great too but it jumps around
    for (int y = 0; y < (int)HEIGHT; y++) {
        for (int x = 0; x < (int)WIDTH; x++) {


            double Xval = minReal + (x / WIDTH) * (maxReal - minReal);
            double Yval = minImag + (y / HEIGHT) * (maxImag - minImag);


            double xbelow = 0.0;
            double ybelow = 0.0;
            int iterations = 0;


            while ((xbelow * xbelow + ybelow * ybelow) <= 4.0 && iterations < MAX_ITERATIONS) {
                double temp = (xbelow * xbelow) - (ybelow * ybelow) + Xval;
                ybelow = 2.0 * xbelow * ybelow + Yval;
                xbelow = temp;
                iterations++;
            }

            int index = y * WIDTH + x;

            if (iterations == MAX_ITERATIONS) {
                pixelBuffer[index] = BLUE;
            }
            else {

                unsigned char intensity = (unsigned char)((iterations / MAX_ITERATIONS) * 255);
                pixelBuffer[index] = Color{ intensity, intensity, intensity, 255 };
            }
        }
        numThreads = omp_get_num_threads();

    }
    std::cout << "Number of threads: " << numThreads << " Static Cyclic Block" << std::endl;
    ThreadCounts.push_back(numThreads);
}

void mandlebrotDynamicCyclic(std::vector<Color>& pixelBuffer)
{
    int numThreads = 0;
#pragma omp parallel for schedule(dynamic,1) num_threads(8) // 2 seems to be the best after multiple tries
    for (int y = 0; y < (int)HEIGHT; y++) {
        for (int x = 0; x < (int)WIDTH; x++) {


            double Xval = minReal + (x / WIDTH) * (maxReal - minReal);
            double Yval = minImag + (y / HEIGHT) * (maxImag - minImag);


            double xbelow = 0.0;
            double ybelow = 0.0;
            int iterations = 0;


            while ((xbelow * xbelow + ybelow * ybelow) <= 4.0 && iterations < MAX_ITERATIONS) {
                double temp = (xbelow * xbelow) - (ybelow * ybelow) + Xval;
                ybelow = 2.0 * xbelow * ybelow + Yval;
                xbelow = temp;
                iterations++;
            }

            int index = y * WIDTH + x;

            if (iterations == MAX_ITERATIONS) {
                pixelBuffer[index] = BLUE;
            }
            else {

                unsigned char intensity = (unsigned char)((iterations / MAX_ITERATIONS) * 255);
                pixelBuffer[index] = Color{ intensity, intensity, intensity, 255 };
            }
        }
        numThreads = omp_get_num_threads();

    }
    std::cout << "Number of threads: " << numThreads << " Dynamic Cyclic" << std::endl;
    ThreadCounts.push_back(numThreads);
}

long long WindowGeneration(void(*mandlebrotFunction)(std::vector<Color>&))
{
    SetTraceLogLevel(LOG_NONE); // keeps logs away
    InitWindow(WIDTH, HEIGHT, "Mandelbrot OPENMP");

    std::vector<Color> pixelBuffer(WIDTH * HEIGHT);

    Image img = { pixelBuffer.data(), WIDTH, HEIGHT, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    Texture2D texture = LoadTextureFromImage(img);



    auto start = std::chrono::high_resolution_clock::now();
    mandlebrotFunction(pixelBuffer);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);



    UpdateTexture(texture, pixelBuffer.data());


    BeginDrawing();
    ClearBackground(BLACK);


    DrawTexture(texture, 0, 0, WHITE);


    EndDrawing();
    UnloadTexture(texture);
    CloseWindow();
    return duration.count();


}


void WindowGenerationShow(void(*mandlebrotFunction)(std::vector<Color>&))
{
    SetTraceLogLevel(LOG_NONE); // keeps logs away
    InitWindow(WIDTH, HEIGHT, "Mandelbrot OPENMP");

    std::vector<Color> pixelBuffer(WIDTH * HEIGHT);

    Image img = { pixelBuffer.data(), WIDTH, HEIGHT, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    Texture2D texture = LoadTextureFromImage(img);



    mandlebrotFunction(pixelBuffer);
    



    UpdateTexture(texture, pixelBuffer.data());

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(texture, 0, 0, WHITE);

        DrawFPS(10, 10);

        EndDrawing();
    }
    UnloadTexture(texture);
    CloseWindow();

}


std::string getSchedulingName(int choice)
{
    switch (choice)
    {
    case 0:
        return "Guided scheduling";
    case 1:
        return "Static scheduling";
    case 2:
        return "Dynamic scheduling";
    case 3:
        return "Cyclic scheduling";
    case 4:
        return "Serial version";
    case 5:
        return "Dynamic Cyclic Block scheduling";
    case 6:
		return "Static Cyclic Block scheduling";
    case 7:
		return "Dynamic Cyclic scheduling";
    default:
        return "Invalid choice";
    }
}


int main() {
  
	std::vector<long long> times;


	times.push_back(WindowGeneration(mandlebrotGuided));//times.push_back(ParallelGuided());
    times.push_back(WindowGeneration(mandlebrotStatic));//times.push_back(ParallelStatic());
    times.push_back(WindowGeneration(mandlebrotDynamic));//times.push_back(ParallelDynamic());
	times.push_back(WindowGeneration(mandlebrotStaticCyclic));//times.push_back(ParallelCyclic());
	times.push_back(WindowGeneration(mandlebrot)); 
	times.push_back(WindowGeneration(mandlebrotDynCyclicBlock)); // times.push_back(ParallelDynCyclic());
    times.push_back(WindowGeneration(mandlebrotStaticCyclicBlock));
	times.push_back(WindowGeneration(mandlebrotDynamicCyclic));


    for (int i = 0; i < times.size(); i++) {
        std::cout << "Time taken for method " << getSchedulingName(i) << ": " << times[i] << " ms" << std::endl;
		std::cout << "Speedup for method " << getSchedulingName(i) << ": " << ((double)times[4]/ (double)times[i]) << "x " << std::endl;  // serial / parallel
		std::cout << "Efficiency for method " << getSchedulingName(i) << ": " << (  ((double)times[4] / (double)times[i])  /  (double)ThreadCounts[i])*100.00 << "% " << std::endl; // (serial / p) / parallel)
        std::cout << "\n\n";
    }
    //dynamic cyclic scheduling x4, dynamic cyclic block scheduling x4, Static Cyclic Block scheduling, Cyclic scheduling
    // in all reality both dynamic cyclic and dynamic cyclic block are very close. 
    //dynamic cyclic scheduling is coming on top a 4 threads
	//dynamic cyclic block scheduling is coming on top at 8 threads.
	//std::cout << "After multiple runs, the best scheduling method seems to be dynamic cyclic block scheduling, with static cyclic block, and dynamic cyclic scheduling being very close." << std::endl;
	//std::cout << "However, after multiple runs, dynamic cyclic seems to hold most consistent with its time etc." << std::endl;
    WindowGenerationShow(mandlebrotDynCyclicBlock);
    return 0;
}
