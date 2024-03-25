#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

//READ TXT DATA
std::string temp;
    std::vector<float> ReadTextImage(const std::string& filename, int& width, int& height){
        std::vector<float> pixels;

        width = 0;
        height = 0;

       
    std::ifstream test(filename);
        if(!test.is_open()){
            std::cerr << "Cant open file please check file name " << filename << std::endl;;
            return pixels;
        }


     std::string line; 
       while(std::getline(test,line)){
            std::istringstream iss(line);
            float value;
                while(iss >> value) {
                    pixels.push_back(value);
                    ++width;
                }
                ++height;
    }

        test.close();
        return pixels;
    }


std::vector<float> AverageArrays(const std::vector<std::vector<float>>& frames){
if(frames.empty()){
    std::cerr << "No frames to average cuh \n";
    return {};
}

std::vector<float> averageFrame(frames[0].size(), 0.0f);

    for (const auto& frame : frames){
        for(size_t t = 0; t < frame.size(); ++t){
        averageFrame[t] += frame[t];
    }
}


return averageFrame; 
}


/// Save array to txt file


void SaveArrayToF(const std::vector<float>& data, const std::string& filename, int width, int height){
    
 std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                outFile << data[i * width + j] << " ";
            }
            outFile << "\n";
        }
        outFile.close();
        std::cout << "Data saved to " << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
    }
}



void Txt2Jpg(const std::string& filename, const std::string& outputFileName ){

  std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open input file: " << filename << std::endl;
        return;
    }
    std::string text((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    file.close();



cv::Mat image(300, 600, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::putText(image, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 0), 2);

    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(95); 
    cv::imwrite(outputFileName, image, params);

    std::cout << "Text converted to JPEG and saved as: " << outputFileName << std::endl;



}

int main(){
    
    const int numAvgFrames = 2; 
    const int numFrames = 1;
    const std::string folderPath = "images/";

    std::vector<std::vector<float>> BiasFrame;
    std::vector<std::vector<float>> FlatFrame;
    std::vector<std::vector<float>> DarkFrame;


    std::vector<std::vector<float>> redFrames;
    std::vector<std::vector<float>> GreenFrames;
    std::vector<std::vector<float>> blueFrames;

    //Calculate Darks 
    
    for(int i = 0; i < numFrames; ++i){
        for(int d = 332; d < 334; ++d){
        
        std::string redFileName   = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_1" + ".txt";
        std::string GreenFileName = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_2" + ".txt";
        std::string BlueFileName  = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_3" + ".txt";


        int RedWidth, RedHeight;
        int GreenWidth, GreenHeight;
        int BlueWidth, BlueHeight;
        

        std::vector<float> RedPixel = ReadTextImage(redFileName,RedWidth,RedHeight);
        std::vector<float> GreenPixel = ReadTextImage(GreenFileName,GreenWidth,GreenHeight);
        std::vector<float> BluePixel = ReadTextImage(BlueFileName,BlueWidth,BlueHeight);


        redFrames.push_back(std::move(RedPixel));
        GreenFrames.push_back(std::move(GreenPixel));
        blueFrames.push_back(std::move(BluePixel));

        std::vector<float> averageRedFrame = AverageArrays(redFrames);
        std::vector<float> averageBlueFrame = AverageArrays(blueFrames);
        std::vector<float> averageGreenFrame = AverageArrays(GreenFrames);


        std::vector<float> averagedDarkFrame(averageRedFrame.size(),0.0f);
    
        for(size_t z = 0; z < averageRedFrame.size(); ++z){
            averagedDarkFrame[z] = (averageRedFrame[z] +   averageGreenFrame[z] + averageRedFrame[z]) / 3.0f;
        }


//SaveArrayToF(averagedDarkFrame, std::string(FINAL_IMAGE_FOLDER) + "Average_Dark_frame.txt", redFrames[0].size(), redFrames.size());
    }
    }
    //Calculate whites / flats !
        for(int i = 0; i < numFrames; ++i){
        for(int d = 346; d < 348; ++d){
        
        std::string redFileName   = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_1" + ".txt";
        std::string GreenFileName = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_2" + ".txt";
        std::string BlueFileName  = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_3" + ".txt";


        int RedWidth, RedHeight;
        int GreenWidth, GreenHeight;
        int BlueWidth, BlueHeight;
        

        std::vector<float> RedPixel = ReadTextImage(redFileName,RedWidth,RedHeight);
        std::vector<float> GreenPixel = ReadTextImage(GreenFileName,GreenWidth,GreenHeight);
        std::vector<float> BluePixel = ReadTextImage(BlueFileName,BlueWidth,BlueHeight);


        redFrames.push_back(std::move(RedPixel));
        GreenFrames.push_back(std::move(GreenPixel));
        blueFrames.push_back(std::move(BluePixel));



        std::vector<float> averageRedFrame = AverageArrays(redFrames);
        std::vector<float> averageBlueFrame = AverageArrays(blueFrames);
        std::vector<float> averageGreenFrame = AverageArrays(GreenFrames);


        std::vector<float> averageFlatFrame(averageRedFrame.size(),0.0f);
    
        for(size_t z = 0; z < averageRedFrame.size(); ++z){
            averageFlatFrame[z] = (averageRedFrame[z] +   averageGreenFrame[z] + averageRedFrame[z]) / 3.0f;
        }


//SaveArrayToF(averageFlatFrame, std::string(FINAL_IMAGE_FOLDER) + "Average_Flat_frame.txt", redFrames[0].size(), redFrames.size());
    }
    }

        // calculate bias frames 
        for(int i = 0; i < numFrames; ++i){
        for(int d = 326; d < 328; ++d){
        
        std::string redFileName   = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_1" + ".txt";
        std::string GreenFileName = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_2" + ".txt";
        std::string BlueFileName  = std::string(IMAGES_FOLDER) +  "/IMG_" + std::to_string(d) + "_3" + ".txt";


        int RedWidth, RedHeight;
        int GreenWidth, GreenHeight;
        int BlueWidth, BlueHeight;
        

        std::vector<float> RedPixel = ReadTextImage(redFileName,RedWidth,RedHeight);
        std::vector<float> GreenPixel = ReadTextImage(GreenFileName,GreenWidth,GreenHeight);
        std::vector<float> BluePixel = ReadTextImage(BlueFileName,BlueWidth,BlueHeight);

        redFrames.push_back(std::move(RedPixel));
        GreenFrames.push_back(std::move(GreenPixel));
        blueFrames.push_back(std::move(BluePixel));

        std::vector<float> averageRedFrame = AverageArrays(redFrames);
        std::vector<float> averageBluedFrame = AverageArrays(blueFrames);
        std::vector<float> averageGreenFrame = AverageArrays(GreenFrames);




        std::vector<float> averageBiasFrame(averageRedFrame.size(),0.0f);
    
        for(size_t z = 0; z < averageRedFrame.size(); ++z){
            averageBiasFrame[z] = (averageRedFrame[z] +   averageGreenFrame[z] + averageRedFrame[z]) / 3.0f;
        }

//SaveArrayToF(averageBiasFrame, std::string(FINAL_IMAGE_FOLDER) + "Average_bias_frame.txt", redFrames[0].size(), redFrames.size());
    }


    }



Txt2Jpg( std::string(FINAL_IMAGE_FOLDER) + "/finalimageAverage_bias_frame.txt", "final_bias_frame_jpeg");



    // Text to images

    // Calibrating frame images 



}