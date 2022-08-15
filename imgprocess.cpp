#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int iAngle = 180;
int iScale = 50;
int iBorderMode = 0;
int iBright =50;
int iContrast = 50;
Mat imgOriginal ;
int iImageCenterY = 0;
int iImageCenterX = 0;
int event_for_save=0;
int iColor;
int iSmooth=0;
int iErosion;
int iLowH = 170;
int iHighH = 179;

int iLowS = 150; 
int iHighS = 255;

int iLowV = 60;
int iHighV = 255;

int idetect;
Mat imgRotated;
Mat imgBrighted;
 
//Ham phan hoi thanh Trackbar
void CallbackForTrackBar(int ,void*)
{
  
 Mat matRotation = getRotationMatrix2D(  Point( iImageCenterX, iImageCenterY ), (iAngle - 180), iScale / 50.0 );
 
 // Rotation, scale, border
  
 warpAffine( imgOriginal, imgRotated, matRotation, imgOriginal.size(), INTER_LINEAR, iBorderMode, Scalar());
 // Bright and Contrast
  imgRotated.convertTo(imgBrighted, -1, (float)iContrast/50, iBright);
  //color change to rgb or gray
     Mat imgColored=imgBrighted.clone() ;
    
    if(iColor==1){
       cvtColor(imgBrighted, imgColored,cv::COLOR_BGR2GRAY);
   }
    //Mat imgColored2 = imgColored.clone();
    if(iColor==2){
       cvtColor(imgBrighted, imgColored,cv::COLOR_BGR2RGB);

    }
    Mat imginvert=imgColored.clone();
 //invert img   
    if(iColor==3){
        bitwise_not(imgColored,imginvert);
    }
 //HSV
    Mat imgHSV=imginvert.clone(); 
    if(iColor==4){
        cvtColor(imginvert,imgHSV,cv::COLOR_BGR2HSV);
    }
  // Gaussian Smooth image
     Mat img_blured_with_kernel=imgHSV.clone();
  
       GaussianBlur(imgHSV, img_blured_with_kernel, Size(2*iSmooth+1, 2*iSmooth+1), 0);
  // Erode img
    Mat img_eroded_with_kernel=img_blured_with_kernel.clone();
      erode(img_blured_with_kernel, img_eroded_with_kernel, getStructuringElement(MORPH_RECT, Size(2*iErosion+1, 2*iErosion+1))); 
   //Color detect
     Mat imgThresholded;
     inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
   //Save 
     if(event_for_save==1)
        {bool isSuccess = imwrite("save_image.jpg", img_eroded_with_kernel);
        if (isSuccess == false)
        {cout << "Failed to save the image" << endl;}

         cout << "Image is succusfully saved to a file" << endl;}
   //imshow( "Destination Img", img_eroded_with_kernel);
   imshow( "Colordetect Img", imgThresholded);
   //face detection
   Mat img_face_detect = img_eroded_with_kernel.clone();
   if(idetect==1){
   //face detect
     CascadeClassifier faceCascade,eyes_cascade;
    faceCascade.load("haarcascade_frontalface_default.xml");
  if(faceCascade.empty()) {cout<<"Fail";}
  vector<Rect> faces;
  faceCascade.detectMultiScale(img_face_detect,faces, 1.1,10);
  for( int i=0; i< faces.size();i++)
  {
     rectangle(img_face_detect, faces[i].tl(), faces[i].br(), Scalar(255,0,255), 3);
   }
   //eyes detect
      eyes_cascade.load("haarcascade_eye.xml");
      vector<Rect> eyes;
      eyes_cascade.detectMultiScale(img_face_detect, eyes, 1.1, 3);//detect eyes in every face//
         for (int j = 0; j < eyes.size(); j++){ //for locating eyes//
            
            rectangle(img_face_detect, eyes[j].tl(), eyes[j].br(), Scalar(0, 255, 0), 3);//drawing rec around both eyes//
         }
  
     
   }
   imshow("Destination Img",img_face_detect  );
   }
   

   

 


 int main( int argc, char** argv )
 {
 // Load the image
 imgOriginal = imread( "cronaldo.png", 1 );

 iImageCenterY = imgOriginal.rows / 2;
 iImageCenterX = imgOriginal.cols / 2;

 //show the original image

 //namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
 //imshow( "Original Image", imgOriginal );


 //create the "Brighted Image" window and 3 trackbars in it
 namedWindow( "Image Processing Software", cv::WINDOW_AUTOSIZE );
  createTrackbar("Angle", "Image Processing Software", &iAngle, 360, CallbackForTrackBar);
  createTrackbar("Scale", "Image Processing Software", &iScale, 100, CallbackForTrackBar);
  createTrackbar("Border Mode", "Image Processing Software", &iBorderMode, 5, CallbackForTrackBar);
  createTrackbar("Bright","Image Processing Software", &iBright,100, CallbackForTrackBar);
  createTrackbar("Bright","Image Processing Software", &iBright,100, CallbackForTrackBar);
  createTrackbar("Contrast","Image Processing Software", &iContrast,100, CallbackForTrackBar);
  createTrackbar("Save (1:Saved, 0: Unsaved)","Image Processing Software", &event_for_save,1,CallbackForTrackBar);   
  createTrackbar("Color","Image Processing Software", &iColor,4, CallbackForTrackBar);   
  createTrackbar("Gaussian smooth","Image Processing Software", &iSmooth,6,CallbackForTrackBar);
  createTrackbar("Erode","Image Processing Software", &iErosion,6,CallbackForTrackBar);  
  createTrackbar("Facedetect + Eyes detect","Image Processing Software", &idetect,1,CallbackForTrackBar); 
  int iDummy = 0;
     CallbackForTrackBar(iDummy,&iDummy);
 //control clr detect
  namedWindow("Control", cv::WINDOW_AUTOSIZE); 
 createTrackbar("LowH", "Control", &iLowH, 179),CallbackForTrackBar; //Hue (0 - 179)
 createTrackbar("HighH", "Control", &iHighH, 179,CallbackForTrackBar);

 createTrackbar("LowS", "Control", &iLowS, 255,CallbackForTrackBar); //Saturation (0 - 255)
 createTrackbar("HighS", "Control", &iHighS, 255,CallbackForTrackBar);

 createTrackbar("LowV", "Control", &iLowV, 255,CallbackForTrackBar);//Value (0 - 255)
 createTrackbar("HighV", "Control", &iHighV, 255,CallbackForTrackBar);
   waitKey(0);
   
   return 0;
}
//g++ try2.cpp -o output `pkg-config --cflags --libs opencv4`

