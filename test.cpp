#include "DBManagerInterface.cpp"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

int main() {

    //DBManagerInterface dbManager(URI, DATABASE, COLLECTION);

    //dbManager.readOid("oid");
    // Mat m = imread( "img.jpg",1);
    // Mat m2 = imread( "img.jpg",1);

    //Create
    // dbManager.create("oid", 111, "oid", m2, m);
    //Read
    //dbManager.readAll();
    //dbManager.readOne("A01021111");
    //Update
    //dbManager.updateName("Luis Garcia ","Victor Coeto");
    //dbManager.updateMatricula("A01021111", "A01025986");
    //Delete
    //dbManager.deleteOne("Victor Coeto");

    // Mat  m2 = dbManager.readMat("oid");

    // imshow("m2", m2);
    // waitKey();
    //dbManager.matMatch();
    Mat img1 = imread( "jimi.jpg", IMREAD_GRAYSCALE );
    Mat img2 = imread( "jimi2.jpeg", IMREAD_GRAYSCALE );
    if ( img1.empty() || img2.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        return -1;
    }
    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
    int minHessian = 400;
    Ptr<SURF> detector = SURF::create( minHessian );
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    detector->detectAndCompute( img1, noArray(), keypoints1, descriptors1 );
    detector->detectAndCompute( img2, noArray(), keypoints2, descriptors2 );
    //-- Step 2: Matching descriptor vectors with a FLANN based matcher
    // Since SURF is a floating-point descriptor NORM_L2 is used
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<DMatch> > knn_matches;
    matcher->knnMatch( descriptors1, descriptors2, knn_matches, 2 );
    //-- Filter matches using the Lowe's ratio test
    const float ratio_thresh = 0.75f;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }
    //-- Draw matches
    Mat img_matches;
    drawMatches( img1, keypoints1, img2, keypoints2, good_matches, img_matches, Scalar::all(-1),
                 Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    //-- Show detected matches
    imshow("Good Matches", img_matches );
    waitKey();
    return 0;

}