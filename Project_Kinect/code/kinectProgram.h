#pragma once

//#pragma comment(lib, "ws2_32.lib") // 충돌 방지
//#include <winsock2.h> // windows등 구버전 헤더와 충돌

#include <Kinect.h>
#include <Kinect.face.h>
#include <ppl.h> // parallel_for_each
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <direct.h>
#include <wrl/client.h>
#include <thread> // this_thread
using namespace std;
using namespace Microsoft::WRL;
using namespace cv;

#include "common/defines.hpp"
#include "common/LabelMapper.h"
#include "SPoint.h"
#include "FrameCollection.h"
#include "ImageFrameCollection.h"

enum KINECT_MODE
{
	KINECT_MODE_IDLE,
	KINECT_MODE_OUTPUT,
	KINECT_MODE_PREDICT,
	KINECT_MODE_LEARNING,

	KINECT_MODE_SIZE,
};

static string to_string(KINECT_MODE mode)
{
	switch (mode)
	{
	case	    KINECT_MODE_OUTPUT:
		return "KINECT_MODE_OUTPUT";
	case		KINECT_MODE_LEARNING:
		return "KINECT_MODE_LEARNING";
	case		KINECT_MODE_PREDICT:
		return "KINECT_MODE_PREDICT";
	case		KINECT_MODE_IDLE:
		return "KINECT_MODE_IDLE";
	default:
		return "ERR_NOT_MODE_NUMBER";

	}
}

class Kinect
{
private:
	KINECT_MODE mode;

	// Sensor
	ComPtr<IKinectSensor> kinect;

	// Coordinate Mapper
	ComPtr<ICoordinateMapper> coordinateMapper;

	// Reader
	ComPtr<IColorFrameReader> colorFrameReader;
	ComPtr<IBodyFrameReader> bodyFrameReader;
	ComPtr<IHighDefinitionFaceFrameReader> hdFaceFrameReader;
	ComPtr<IDepthFrameReader> depthFrameReader;

	// Color Buffer
	std::vector<BYTE> colorBuffer; // raw buffer
	int colorWidth, colorHeight;
	cv::Mat colorMat; // showing mat

	// Depth Buffer
	int depthWidth = 512, depthHeight = 424; // kinect v2의 depth 데이터 크기
	cv::Mat depthMat; // CV_U8C4
	BYTE depthBuffer[512 * 424 * 4];
  
	// Body Buffer
	array<IBody*, BODY_COUNT> bodies = { nullptr };
	std::array<cv::Vec3b, BODY_COUNT> colors;

	// HDFace Buffer
	vector<CameraSpacePoint> vertexes;
	ComPtr<IFaceModelBuilder> faceModelBuilder;
	ComPtr<IFaceAlignment> faceAlignment;
	ComPtr<IFaceModel> faceModel;
	std::array<float, FaceShapeDeformations::FaceShapeDeformations_Count> faceShapeUnits = { 0.0f };
	UINT32 vertexCount;
	UINT64 trackingId;
	int trackingCount = 0;
	bool produced = false;
	BOOLEAN tracked = false;

	// sPoint
	float spinePx; // cameraspcae
	float spinePxColorSpaceVersion;
	float spinePxDepthSpaceVersion;
	std::array<SPoint, SPOINT_SIZE> sPoints;
	CameraSpacePoint addtionalPoints[11];
	bool atLeastOneTracked;

	// Status Text
	double fps = 0;
	TIMESPAN lastFrameRelativeTime;
	TIMESPAN pastFrameRelativeTime;
	std::stringstream statusStream;
	cv::Scalar statusFontColor;
	FaceModelBuilderCaptureStatus faceCapture;
	FaceModelBuilderCollectionStatus faceCollection;
	double distance = 0;

	// ML data
	bool leftHandActivated = false;
	bool rightHandActivated = false;
	bool frameStacking = false;
	int recorded = 0;
	FrameCollection frameCollection;
	ImageFrameCollection lhandCollection;
	ImageFrameCollection rhandCollection;

	CameraSpacePoint lHandPos;
	CameraSpacePoint rHandPos;
	TIMESPAN recordStartTime;
	int label;
	string workerName = "None";

	// Hand ROI
	cv::Mat lHandImage;
	cv::Mat rHandImage;

public:
	// Constructor
	Kinect();
	Kinect(KINECT_MODE m);

	// Destructor
	~Kinect();

	// Processing
	void run_one_cycle();

	void setLabel(int l);
	void setMode(KINECT_MODE m);
	void setWorkerName(string name);

private:
	// Initialize
	void initialize();

	void initializeSensor();

	void initializeHDFace();

	void initializeColor();

	void initializeComponents();

	void initializeBody();

	void initializeDepth();

	// Finalize
	void finalize();

	// Update Data
	void update();

	inline void updateColor();

	inline void updateBody();

	void updateSPoint();

	void updateStatus();

	void updateFrame();

	void updateHDFace();

	void updateDepth();

	void updateROI();

	// Draw Data
	void draw();

	inline void drawColor();

	void drawExtractedROI();

	inline void drawBody();

	void drawHDFace();

	void drawSPoint();

	void drawEllipse(cv::Mat & image, const CameraSpacePoint & pos, const int radius, const cv::Vec3b & color, const int thickness = -1);

	void drawVertexes(cv::Mat& image, const std::vector<CameraSpacePoint> vertexes, const int radius, const cv::Vec3b& color, const int thickness = -1);

	void drawStatusText();

	// Show Data
	void show();

	inline void showColor();

	// etc
	void findClosestBody(const std::array<IBody*, BODY_COUNT>& bodies);

	void findLRHandPos();

	string status2string(const FaceModelBuilderCaptureStatus capture);

	string status2string(const FaceModelBuilderCollectionStatus collection);

	void save(bool);

	void isFolderNotExistCreate(string path);

	// for extract hand
	void extractHand();

	bool isHandTracking();

	CameraSpacePoint lerp(CameraSpacePoint src, CameraSpacePoint dst);
};