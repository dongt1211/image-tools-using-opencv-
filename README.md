# Hướng dẫn cài đặt thư viện opencv và chạy code trên ubuntu linux
## Cách cài đặt OpenCV từ Ubuntu Respository
 <p> Step 1: Refresh the packages index and install the OpenCV package by typing: </p>

- <code>$ sudo apt-get update</code>
- <code>$ sudo apt install python3-opencv</code>

 <p> Step 2: To verify the installation, import the cv2 module and print the OpenCV version:</p>

- <code>python3 -c "import cv2; print(cv2.__version__)"   </code>
- Output: 3.2.0

## Cách chạy code trên ubuntu linux:
Step 1: Turn on terminal.

Step 2: To compile a imgprocess.cpp file, using this command:
- <code>g++ imgprocess.cpp -o output `pkg-config --cflags --libs opencv4`</code>

Step 3: To run file, using this command:
- <code>./output</code>  
