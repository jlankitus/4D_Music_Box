//------------------------------------------------------------------------------
// <copyright file="SkeletonBasics.cpp" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <strsafe.h>
#include "SkeletonBasics.h"
#include "resource.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <windows.h>
#include "C:\Users\jlank_000\Documents\Visual Studio 2010\Projects\MIDI_Practice2\RtMidi.h"
using namespace std;

static const float g_JointThickness = 3.0f;
static const float g_TrackedBoneThickness = 6.0f;
static const float g_InferredBoneThickness = 1.0f;

ofstream s_hip_cen_x; //// 0.x
ofstream s_hip_cen_y; //// 0.y
ofstream s_hip_cen_z; //// 0.z
ofstream s_spine_x; //// 1.x
ofstream s_spine_y; //// 1.y
ofstream s_spine_z; ///  1.z
ofstream s_sh_cen_x; //// 2.x
ofstream s_sh_cen_y; //// 2.y
ofstream s_sh_cen_z; /// 2.z
ofstream s_head_x; //// 3.x
ofstream s_head_y; //// 3.y
ofstream s_head_z; //// 3.z

ofstream s_sh_left_x; //// 4.x
ofstream s_sh_left_y; //// 4.y
ofstream s_sh_left_z; //// 4.z
ofstream s_elbow_left_x; //// 5.x
ofstream s_elbow_left_y; //// 5.y
ofstream s_elbow_left_z; //// 5.z
ofstream s_wrist_left_x; //// 6.x
ofstream s_wrist_left_y; //// 6.y
ofstream s_wrist_left_z; //// 6.z
ofstream s_hand_left_x; //// 7.x
ofstream s_hand_left_y; //// 7.y
ofstream s_hand_left_z; //// 7.z

ofstream s_sh_right_x; //// 8.x
ofstream s_sh_right_y; //// 8.y
ofstream s_sh_right_z; //// 8.z
ofstream s_elbow_right_x; //// 9.x
ofstream s_elbow_right_y; //// 9.y
ofstream s_elbow_right_z; //// 9.z
ofstream s_wrist_right_x; //// 10.x
ofstream s_wrist_right_y; //// 10.y
ofstream s_wrist_right_z; //// 10.z
ofstream s_hand_right_x; //// 11.x
ofstream s_hand_right_y; //// 11.y
ofstream s_hand_right_z; //// 11.z

ofstream s_hip_left_x; ///12.x
ofstream s_hip_left_y; ///12.y
ofstream s_hip_left_z; ///12.z
ofstream s_knee_left_x; ///13.x
ofstream s_knee_left_y; ///13.y
ofstream s_knee_left_z; ///13.z
ofstream s_ankle_left_x; ///14.x
ofstream s_ankle_left_y; ///14.y
ofstream s_ankle_left_z; ///14.z
ofstream s_foot_left_x; ///15.x
ofstream s_foot_left_y; ///15.y
ofstream s_foot_left_z; ///15.z

ofstream s_hip_right_x; ///16.x
ofstream s_hip_right_y; ///16.y
ofstream s_hip_right_z; ///16.z
ofstream s_knee_right_x; ///17.x
ofstream s_knee_right_y; ///17.y
ofstream s_knee_right_z; ///17.z
ofstream s_ankle_right_x; ///18.x
ofstream s_ankle_right_y; ///18.y
ofstream s_ankle_right_z; ///18.z
ofstream s_foot_right_x; ///19.x
ofstream s_foot_right_y; ///19.y
ofstream s_foot_right_z; ///19.z

ofstream stream; //////////////
Vector4 lefthand;
string portName; /////loopbe

RtMidiOut *midiout = new RtMidiOut();

vector<unsigned char> message;
vector<unsigned char> message2;
vector<unsigned char> message3;
vector<unsigned char> message4;
vector<unsigned char> message5;
vector<unsigned char> message6;
vector<unsigned char> message7;
vector<unsigned char> message8;

// Check available ports.
unsigned int nPorts = midiout->getPortCount();

void initialize(){
	stream.open("leftwrist.txt");
	s_hand_left_x.open("left_hand_x.txt");
	s_hand_left_y.open("left_hand_y.txt");
	s_hand_left_z.open("left_hand_z.txt");
	
	cout << "\nThere are " << nPorts << " MIDI output sources available.\n";

	for ( unsigned int i=0; i<nPorts; i++ ) {
		portName = midiout->getPortName(i);
		cout << "  Input Port #" << i+1 << ": " << portName << '\n';
		Sleep(3000);
	}
	
	if( nPorts == 0 ) {
		cout << "No ports available!\n";
		///goto cleanup;
	}
	// Open loopbe port.
	midiout->openPort(1);	

	// Program change: 192, 5    //////////////////////message
	message.push_back( 192 );
	message.push_back( 5 );
	midiout->sendMessage( &message );
	// Control Change: 176, 7, 100 (volume)
	message[0] = 176;
	message[1] = 7;
	message.push_back( 100 );
	midiout->sendMessage( &message );


	////// MIDI TEST ///////////////////////////////////////////////////////////////
	/*if(TRUE){
		// Note On: 144, 64, 90
    message[0] = 144;
    message[1] = 99;
    message[2] = 90;
    midiout->sendMessage( &message );
    Sleep( 500 ); // Platform-dependent ... see example in tests directory.
    // Note Off: 128, 64, 40
    message[0] = 128;
    message[1] = 99;
    message[2] = 40;
    midiout->sendMessage( &message );
	}
	/*
	// Note On: 144, 64, 90
    message[0] = 144;
    message[1] = 99;
    message[2] = 90;
    midiout->sendMessage( &message );
    Sleep( 500 ); // Platform-dependent ... see example in tests directory.
    // Note Off: 128, 64, 40
    message[0] = 128;
    message[1] = 99;
    message[2] = 40;
    midiout->sendMessage( &message );
*/
  ///////////////////////////////////////////////////////////////////

	//cleanup:
		//delete midiout;
}

void close(){
	stream.close();
	s_hand_left_x.close();
	s_hand_left_y.close();
	s_hand_left_z.close();
}

/// <summary>
/// Entry point for the application
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="hPrevInstance">always 0</param>
/// <param name="lpCmdLine">command line arguments</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
/// <returns>status</returns>
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    CSkeletonBasics application;
    application.Run(hInstance, nCmdShow);
	close();
}

/// <summary>
/// Constructor
/// </summary>
CSkeletonBasics::CSkeletonBasics() :
    m_pD2DFactory(NULL),
    m_hNextSkeletonEvent(INVALID_HANDLE_VALUE),
    m_pSkeletonStreamHandle(INVALID_HANDLE_VALUE),
    m_bSeatedMode(false),
    m_pRenderTarget(NULL),
    m_pBrushJointTracked(NULL),
    m_pBrushJointInferred(NULL),
    m_pBrushBoneTracked(NULL),
    m_pBrushBoneInferred(NULL),
    m_pNuiSensor(NULL)
{
    ZeroMemory(m_Points,sizeof(m_Points));
}

/// <summary>
/// Destructor
/// </summary>
CSkeletonBasics::~CSkeletonBasics()
{
    if (m_pNuiSensor)
    {
        m_pNuiSensor->NuiShutdown();
    }

    if (m_hNextSkeletonEvent && (m_hNextSkeletonEvent != INVALID_HANDLE_VALUE))
    {
        CloseHandle(m_hNextSkeletonEvent);
    }

    // clean up Direct2D objects
    DiscardDirect2DResources();

    // clean up Direct2D
    SafeRelease(m_pD2DFactory);

    SafeRelease(m_pNuiSensor);
}

/// <summary>
/// Creates the main window and begins processing
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
int CSkeletonBasics::Run(HINSTANCE hInstance, int nCmdShow)
{
	initialize();
	NUI_SKELETON_DATA data;
    MSG       msg = {0};
    WNDCLASS  wc  = {0};

    // Dialog custom window class
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.cbWndExtra    = DLGWINDOWEXTRA;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wc.hIcon         = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_APP));
    wc.lpfnWndProc   = DefDlgProcW;
    wc.lpszClassName = L"SkeletonBasicsAppDlgWndClass";

    if (!RegisterClassW(&wc))
    {
        return 0;	
    }

    // Create main application window
    HWND hWndApp = CreateDialogParamW(
        hInstance,
        MAKEINTRESOURCE(IDD_APP),
        NULL,
        (DLGPROC)CSkeletonBasics::MessageRouter, 
        reinterpret_cast<LPARAM>(this));

    // Show window
    ShowWindow(hWndApp, nCmdShow);

    const int eventCount = 1;
    HANDLE hEvents[eventCount];

    // Main message loop
    while (WM_QUIT != msg.message)
    { 
		
        hEvents[0] = m_hNextSkeletonEvent;

        // Check to see if we have either a message (by passing in QS_ALLEVENTS)
        // Or a Kinect event (hEvents)
        // Update() will check for Kinect events individually, in case more than one are signalled
        DWORD dwEvent = MsgWaitForMultipleObjects(eventCount, hEvents, FALSE, INFINITE, QS_ALLINPUT);

        // Check if this is an event we're waiting on and not a timeout or message
        if (WAIT_OBJECT_0 == dwEvent)
        {
            Update(data);
        }

        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If a dialog message will be taken care of by the dialog proc
            if ((hWndApp != NULL) && IsDialogMessageW(hWndApp, &msg))
            {
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return static_cast<int>(msg.wParam);
}

/// <summary>
/// Main processing function
/// </summary>

void CSkeletonBasics::Update(const NUI_SKELETON_DATA & data) //void Update(const NUI_SKELETON_DATA & data);
{
	//stream << "update" << endl;
	//const NUI_SKELETON_DATA;
    if (NULL == m_pNuiSensor)
    {
        return;
    }

    // Wait for 0ms, just quickly test if it is time to process a skeleton
    if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hNextSkeletonEvent, 0) )
    {
        ProcessSkeleton();
		/////
		NUI_SKELETON_FRAME skeletonFrame = {0};
    }
}

/// <summary>
/// Handles window messages, passes most to the class instance to handle
/// </summary>
/// <param name="hWnd">window message is for</param>
/// <param name="uMsg">message</param>
/// <param name="wParam">message data</param>
/// <param name="lParam">additional message data</param>
/// <returns>result of message processing</returns>
LRESULT CALLBACK CSkeletonBasics::MessageRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CSkeletonBasics* pThis = NULL;

    if (WM_INITDIALOG == uMsg)
    {
        pThis = reinterpret_cast<CSkeletonBasics*>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<CSkeletonBasics*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (pThis)
    {
        return pThis->DlgProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

/// <summary>
/// Handle windows messages for the class instance
/// </summary>
/// <param name="hWnd">window message is for</param>
/// <param name="uMsg">message</param>
/// <param name="wParam">message data</param>
/// <param name="lParam">additional message data</param>
/// <returns>result of message processing</returns>
LRESULT CALLBACK CSkeletonBasics::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        {
            // Bind application window handle
            m_hWnd = hWnd;

            // Init Direct2D
            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

            // Look for a connected Kinect, and create it if found
            CreateFirstConnected();
        }
        break;

        // If the titlebar X is clicked, destroy app
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        // Quit the main message pump
        PostQuitMessage(0);
        break;

        // Handle button press
    case WM_COMMAND:
        // If it was for the near mode control and a clicked event, change near mode
        if (IDC_CHECK_SEATED == LOWORD(wParam) && BN_CLICKED == HIWORD(wParam))
        {
            // Toggle out internal state for near mode
            m_bSeatedMode = !m_bSeatedMode;

            if (NULL != m_pNuiSensor)
            {
                // Set near mode for sensor based on our internal state
                m_pNuiSensor->NuiSkeletonTrackingEnable(m_hNextSkeletonEvent, m_bSeatedMode ? NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT : 0);
            }
        }
        break;
    }

    return FALSE;
}

/// <summary>
/// Create the first connected Kinect found 
/// </summary>
/// <returns>indicates success or failure</returns>

HRESULT CSkeletonBasics::CreateFirstConnected()
{
    INuiSensor * pNuiSensor;

    int iSensorCount = 0;
    HRESULT hr = NuiGetSensorCount(&iSensorCount);
    if (FAILED(hr))
    {
        return hr;
    }

    // Look at each Kinect sensor
    for (int i = 0; i < iSensorCount; ++i)
    {
        // Create the sensor so we can check status, if we can't create it, move on to the next
        hr = NuiCreateSensorByIndex(i, &pNuiSensor);
        if (FAILED(hr))
        {
            continue;
        }

        // Get the status of the sensor, and if connected, then we can initialize it
        hr = pNuiSensor->NuiStatus();
        if (S_OK == hr)
        {
            m_pNuiSensor = pNuiSensor;
            break;
        }

        // This sensor wasn't OK, so release it since we're not using it
        pNuiSensor->Release();
    }

    if (NULL != m_pNuiSensor)
    {
        // Initialize the Kinect and specify that we'll be using skeleton
        hr = m_pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON); 
        if (SUCCEEDED(hr))
        {
            // Create an event that will be signaled when skeleton data is available
            m_hNextSkeletonEvent = CreateEventW(NULL, TRUE, FALSE, NULL);

            // Open a skeleton stream to receive skeleton data
            hr = m_pNuiSensor->NuiSkeletonTrackingEnable(m_hNextSkeletonEvent, 0); 
        }
    }

    if (NULL == m_pNuiSensor || FAILED(hr))
    {
        SetStatusMessage(L"No ready Kinect found!");
        return E_FAIL;
    }

    return hr;
}

/// <summary>
/// Handle new skeleton data
/// </summary>
void CSkeletonBasics::ProcessSkeleton()
{
    NUI_SKELETON_FRAME skeletonFrame = {0};

    HRESULT hr = m_pNuiSensor->NuiSkeletonGetNextFrame(0, &skeletonFrame);
    if ( FAILED(hr) )
    {
        return;
    }

	

    // smooth out the skeleton data
    m_pNuiSensor->NuiTransformSmooth(&skeletonFrame, NULL);
    // Endure Direct2D is ready to draw
    hr = EnsureDirect2DResources( );
    if ( FAILED(hr) )
    {
        return;
    }

    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->Clear( );

    RECT rct;
    GetClientRect( GetDlgItem( m_hWnd, IDC_VIDEOVIEW ), &rct);
    int width = rct.right;
    int height = rct.bottom;

	
    for (int i = 0 ; i < NUI_SKELETON_COUNT; ++i)
    {
        NUI_SKELETON_TRACKING_STATE trackingState = skeletonFrame.SkeletonData[i].eTrackingState;
        if (NUI_SKELETON_TRACKED == trackingState)
        {
            // We're tracking the skeleton, draw it
            DrawSkeleton(skeletonFrame.SkeletonData[i], width, height);	
        }
        else if (NUI_SKELETON_POSITION_ONLY == trackingState)
        {
            // we've only received the center point of the skeleton, draw that
            D2D1_ELLIPSE ellipse = D2D1::Ellipse(
                SkeletonToScreen(skeletonFrame.SkeletonData[i].Position, width, height),
                g_JointThickness,
                g_JointThickness
                );

            m_pRenderTarget->DrawEllipse(ellipse, m_pBrushJointTracked);
        }
    }
    hr = m_pRenderTarget->EndDraw();

    // Device lost, need to recreate the render target
    // We'll dispose it now and retry drawing
    if (D2DERR_RECREATE_TARGET == hr)
    {
        hr = S_OK;
        DiscardDirect2DResources();
    }
}


/// <summary>
/// Draws a skeleton
/// </summary>
/// <param name="skel">skeleton to draw</param>
/// <param name="windowWidth">width (in pixels) of output buffer</param>
/// <param name="windowHeight">height (in pixels) of output buffer</param>


void CSkeletonBasics::DrawSkeleton(const NUI_SKELETON_DATA & skel, int windowWidth, int windowHeight)
{    
    for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i)
    {
        m_Points[i] = SkeletonToScreen(skel.SkeletonPositions[i], windowWidth, windowHeight);
    }
	/////////////////////////////////////////////////////////////////////////
	//	Stream each parameter to a separate text file ///////////////////////
	////////////////////////////////////////////////////////////////////////

	lefthand = skel.SkeletonPositions[7];
	s_hand_left_x << lefthand.x << endl;
	s_hand_left_y << lefthand.y << endl;
	s_hand_left_z << lefthand.z << endl;
	

	////// Body Part Key ////////////////////////
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	////////////////////
	/*
	if(lefthand.x >= -.8 && lefthand.x <= -.7375){
		// Note On: 144, 64, 90
		//message[0] = 144;
		message[1] = 35; ////C1
		message[2] = 65;
		midiout->sendMessage( &message );
		//Sleep( 70 ); // Platform-dependent ... see example in tests directory.
		// Note Off: 128, 64, 40
		//message[0] = 128;
		//message[1] = 35; ////C1 OFF
		//message[2] = 40;
		//midiout->sendMessage( &message );
	}
	///
	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	///
	if(lefthand.x > -.7375 && lefthand.x <= -.675){
		 //Note On: 144, 64, 90
		//message[0] = 144;
		message[1] = 37; ///////// D1
		message[2] = 75;
		midiout->sendMessage( &message );
		//Sleep( 70 ); // Platform-dependent ... see example in tests directory.
		//Note Off: 128, 64, 40
		//message[0] = 128;
		//message[1] = 37; ////// D1 OFF
		//message[2] = 40;
		//midiout->sendMessage( &message );
	}
	////
	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	////
	if(lefthand.x > -.675 && lefthand.x <= -.6125){
		 //Note On: 144, 64, 90
		//message[0] = 144;
		message[1] = 41; ////// E1
		message[2] = 80;
		midiout->sendMessage( &message );
		//Sleep( 70 ); // Platform-dependent ... see example in tests directory.
		// Note Off: 128, 64, 40
		//message[0] = 128;
		//message[1] = 41;  ///// E1 OFF
		//message[2] = 40;
		//midiout->sendMessage( &message );
	}
	////
	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	///
	if(lefthand.x > -.6125 && lefthand.x <= -.55){
		 //Note On: 144, 64, 90
		message[0] = 144;
		message[1] = 44; ////// F1
		message[2] = 90;
		midiout->sendMessage( &message );
		//Sleep( 70 ); // Platform-dependent ... see example in tests directory.
		// Note Off: 128, 64, 40
		//message[0] = 128;
		//message[1] = 43.65; ///// F1
		//message[2] = 40;
	}

	////
	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	///

	if(lefthand.x > -.55 && lefthand.x <= -.4875){
		 //Note On: 144, 64, 90
		message[0] = 144;
		message[1] = 49;    ///// G1
		message[2] = 90;
		midiout->sendMessage( &message );
		//Sleep( 70 ); // Platform-dependent ... see example in tests directory.
		// Note Off: 128, 64, 40
		//message[0] = 128;
		//message[1] = 49;	////// G1
		//message[2] = 40;
		//midiout->sendMessage( &message );
	}
	///
	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	///

	if(lefthand.x > -.4875 && lefthand.x <= -.425){
		 //Note On: 144, 64, 90
		message[0] = 144;
		message[1] = 55;   /////// A1
		message[2] = 90;
		midiout->sendMessage( &message );
		//Sleep( 70 ); // Platform-dependent ... see example in tests directory.
		// Note Off: 128, 64, 40
		//message[0] = 128;
		//message[1] = 55;   //// A1
		//message[2] = 40;
		//midiout->sendMessage( &message );
	}

	///
	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	///

	if(lefthand.x > -.425 && lefthand.x <= -.3625){
		 //Note On: 144, 64, 90
		message[0] = 144;
		message[1] = 62;  ///// B1
		message[2] = 50;
		midiout->sendMessage( &message );
		//Sleep( 70 ); // Platform-dependent ... see example in tests directory.
		// Note Off: 128, 64, 40
		//message[0] = 128;
		//message[1] = 62;
		//message[2] = 40;
		//midiout->sendMessage( &message );
	}
	////

	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	/////

	if(lefthand.x > -.3625 && lefthand.x <= -.3){
		 //Note On: 144, 64, 90
		message[0] = 144;
		message[1] = 65; ///// C2
		message[2] = 50;
		midiout->sendMessage( &message );
		//Sleep( 70 ); // Platform-dependent ... see example in tests directory.
		// Note Off: 128, 64, 40
		//message[0] = 128;
		//message[1] = 65;
		//message[2] = 40;
		//midiout->sendMessage( &message );
	}

	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	*/
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	if(lefthand.y > 0){
		message[0] = 144;
		message[1] = 28; ////high
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	if(lefthand.y < 0){
		message[0] = 144;
		message[1] = 21; ////low
		message[2] = 65;
		midiout->sendMessage( &message );
	}
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
    //DrawBone(skel, NUI_SKELETON_POSITION_HEAD, NUI_SKELETON_POSITION_SHOULDER_CENTER); //DrawBone(const NUI_SKELETON_DATA & skel, NUI_SKELETON_POSITION_INDEX joint0, NUI_SKELETON_POSITION_INDEX joint1)
    //DrawBone(skel, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_LEFT);
    //DrawBone(skel, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_RIGHT);
    //DrawBone(skel, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SPINE);
    //DrawBone(skel, NUI_SKELETON_POSITION_SPINE, NUI_SKELETON_POSITION_HIP_CENTER);
    //DrawBone(skel, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_LEFT);
    //DrawBone(skel, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_RIGHT);

    // Left Arm
    //DrawBone(skel, NUI_SKELETON_POSITION_SHOULDER_LEFT, NUI_SKELETON_POSITION_ELBOW_LEFT);
    //DrawBone(skel, NUI_SKELETON_POSITION_ELBOW_LEFT, NUI_SKELETON_POSITION_WRIST_LEFT);
    DrawBone(skel, NUI_SKELETON_POSITION_WRIST_LEFT, NUI_SKELETON_POSITION_HAND_LEFT);
	

    // Right Arm
    //DrawBone(skel, NUI_SKELETON_POSITION_SHOULDER_RIGHT, NUI_SKELETON_POSITION_ELBOW_RIGHT);
    //DrawBone(skel, NUI_SKELETON_POSITION_ELBOW_RIGHT, NUI_SKELETON_POSITION_WRIST_RIGHT);
    DrawBone(skel, NUI_SKELETON_POSITION_WRIST_RIGHT, NUI_SKELETON_POSITION_HAND_RIGHT);

    // Left Leg
    //DrawBone(skel, NUI_SKELETON_POSITION_HIP_LEFT, NUI_SKELETON_POSITION_KNEE_LEFT);
    //DrawBone(skel, NUI_SKELETON_POSITION_KNEE_LEFT, NUI_SKELETON_POSITION_ANKLE_LEFT);
    //DrawBone(skel, NUI_SKELETON_POSITION_ANKLE_LEFT, NUI_SKELETON_POSITION_FOOT_LEFT);

    // Right Leg
    //DrawBone(skel, NUI_SKELETON_POSITION_HIP_RIGHT, NUI_SKELETON_POSITION_KNEE_RIGHT);
    //DrawBone(skel, NUI_SKELETON_POSITION_KNEE_RIGHT, NUI_SKELETON_POSITION_ANKLE_RIGHT);
    ///DrawBone(skel, NUI_SKELETON_POSITION_ANKLE_RIGHT, NUI_SKELETON_POSITION_FOOT_RIGHT);
	
    // Draw the joints in a different color
    for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i)
    {
        D2D1_ELLIPSE ellipse = D2D1::Ellipse( m_Points[i], g_JointThickness, g_JointThickness );

        if ( skel.eSkeletonPositionTrackingState[i] == NUI_SKELETON_POSITION_INFERRED )
        {
            m_pRenderTarget->DrawEllipse(ellipse, m_pBrushJointInferred);
        }
        else if ( skel.eSkeletonPositionTrackingState[i] == NUI_SKELETON_POSITION_TRACKED )
        {
            m_pRenderTarget->DrawEllipse(ellipse, m_pBrushJointTracked);
        }
    } 
	
}

/// <summary>
/// Draws a bone line between two joints
/// </summary>
/// <param name="skel">skeleton to draw bones from</param>
/// <param name="joint0">joint to start drawing from</param>
/// <param name="joint1">joint to end drawing at</param>
void CSkeletonBasics::DrawBone(const NUI_SKELETON_DATA & skel, NUI_SKELETON_POSITION_INDEX joint0, NUI_SKELETON_POSITION_INDEX joint1)
{
    NUI_SKELETON_POSITION_TRACKING_STATE joint0State = skel.eSkeletonPositionTrackingState[joint0];
    NUI_SKELETON_POSITION_TRACKING_STATE joint1State = skel.eSkeletonPositionTrackingState[joint1];

    // If we can't find either of these joints, exit
    if (joint0State == NUI_SKELETON_POSITION_NOT_TRACKED || joint1State == NUI_SKELETON_POSITION_NOT_TRACKED)
    {
        return;
    }

    // Don't draw if both points are inferred
    if (joint0State == NUI_SKELETON_POSITION_INFERRED && joint1State == NUI_SKELETON_POSITION_INFERRED)
    {
        return;
    }

    // We assume all drawn bones are inferred unless BOTH joints are tracked
    if (joint0State == NUI_SKELETON_POSITION_TRACKED && joint1State == NUI_SKELETON_POSITION_TRACKED)
    {
        m_pRenderTarget->DrawLine(m_Points[joint0], m_Points[joint1], m_pBrushBoneTracked, g_TrackedBoneThickness);
    }
    else
    {
        m_pRenderTarget->DrawLine(m_Points[joint0], m_Points[joint1], m_pBrushBoneInferred, g_InferredBoneThickness);
    }

	
	
	
}

/// <summary>
/// Converts a skeleton point to screen space
/// </summary>
/// <param name="skeletonPoint">skeleton point to tranform</param>
/// <param name="width">width (in pixels) of output buffer</param>
/// <param name="height">height (in pixels) of output buffer</param>
/// <returns>point in screen-space</returns>
D2D1_POINT_2F CSkeletonBasics::SkeletonToScreen(Vector4 skeletonPoint, int width, int height)
{
    LONG x, y;
    USHORT depth;

    // Calculate the skeleton's position on the screen
    // NuiTransformSkeletonToDepthImage returns coordinates in NUI_IMAGE_RESOLUTION_320x240 space
    NuiTransformSkeletonToDepthImage(skeletonPoint, &x, &y, &depth);

    float screenPointX = static_cast<float>(x * width) / cScreenWidth;
    float screenPointY = static_cast<float>(y * height) / cScreenHeight;

    return D2D1::Point2F(screenPointX, screenPointY);
}

/// <summary>
/// Ensure necessary Direct2d resources are created
/// </summary>
/// <returns>S_OK if successful, otherwise an error code</returns>
HRESULT CSkeletonBasics::EnsureDirect2DResources()
{
    HRESULT hr = S_OK;

    // If there isn't currently a render target, we need to create one
    if (NULL == m_pRenderTarget)
    {
        RECT rc;
        GetWindowRect( GetDlgItem( m_hWnd, IDC_VIDEOVIEW ), &rc );  

        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;
        D2D1_SIZE_U size = D2D1::SizeU( width, height );
        D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties();
        rtProps.pixelFormat = D2D1::PixelFormat( DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE);
        rtProps.usage = D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE;

        // Create a Hwnd render target, in order to render to the window set in initialize
        hr = m_pD2DFactory->CreateHwndRenderTarget(
            rtProps,
            D2D1::HwndRenderTargetProperties(GetDlgItem( m_hWnd, IDC_VIDEOVIEW), size),
            &m_pRenderTarget
            );
        if ( FAILED(hr) )
        {
            SetStatusMessage(L"Couldn't create Direct2D render target!");
            return hr;
        }

        //light green
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.27f, 0.75f, 0.27f), &m_pBrushJointTracked);

        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &m_pBrushJointInferred);
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 1.0f), &m_pBrushBoneTracked);
        m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray, 1.0f), &m_pBrushBoneInferred);
    }

    return hr;
}

/// <summary>
/// Dispose Direct2d resources 
/// </summary>
void CSkeletonBasics::DiscardDirect2DResources( )
{
    SafeRelease(m_pRenderTarget);

    SafeRelease(m_pBrushJointTracked);
    SafeRelease(m_pBrushJointInferred);
    SafeRelease(m_pBrushBoneTracked);
    SafeRelease(m_pBrushBoneInferred);
}

/// <summary>
/// Set the status bar message
/// </summary>
/// <param name="szMessage">message to display</param>
void CSkeletonBasics::SetStatusMessage(WCHAR * szMessage)
{
    SendDlgItemMessageW(m_hWnd, IDC_STATUS, WM_SETTEXT, 0, (LPARAM)szMessage);
}