#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
    cv::Mat img;
    cv::Mat dst;
    cv::VideoCapture input(0);
    cv::VideoWriter output(
            "cars_sobel.avi",
            CV_FOURCC('X','V','I','D'),
            30,
            cv::Size(input.get(CV_CAP_PROP_FRAME_WIDTH),
                input.get(CV_CAP_PROP_FRAME_HEIGHT)));

    for(;;)
    {
        if(!input.read(img))
            break;
        cv::Sobel(img, dst, CV_8U,1,1);
        output.write(dst);
        cv::imshow("img",img);

        output.write(dst);
        cv::imshow("img",img);
        char c = cv::waitKey(30);

        if (c == ' ')
            break;
    }
}
