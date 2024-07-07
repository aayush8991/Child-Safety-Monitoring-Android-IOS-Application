package com.example.Parent_Mobile;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.widget.Toast;
import android.util.Log;
import java.util.ArrayList;
import android.content.res.Configuration;
import androidx.core.app.ActivityCompat;
import androidx.fragment.app.Fragment;
import androidx.core.content.ContextCompat;
import android.view.LayoutInflater;
import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import com.example.Parent_Mobile.databinding.ActivityMainBinding;
import com.google.android.material.tabs.TabLayoutMediator;
import androidx.fragment.app.FragmentManager;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import android.view.MenuItem;
import androidx.navigation.fragment.NavHostFragment;
import androidx.navigation.ui.NavigationUI;
import android.widget.LinearLayout;
import com.google.android.material.bottomnavigation.BottomNavigationView;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import android.view.SurfaceView;
import android.view.View;
import android.widget.ImageButton;
import android.os.CountDownTimer;
import android.os.Build;
import androidx.core.content.res.ResourcesCompat;
import android.widget.TextView;
import java.util.Hashtable;
import android.annotation.TargetApi;
import android.os.Build;
import android.content.Context;
import android.media.AudioManager;

public class Parent_Mobile extends AppCompatActivity implements OnFragmentInteractionListener , CvCameraViewListener2 {
    private InfoFragment infoFragment;
    private AppFragment appFragment;
     FragmentManager fm;
     Fragment current;
    private LogFragment logFragment;
     private Hashtable<Integer,TextView> textViews = new Hashtable<Integer,TextView>();
    private static final int MY_PERMISSIONS_REQUEST_CAMERA = 100;
    private boolean isCameraPermissionGranted = false;
    private boolean isCameraPermissionRequested = false;
    String nativeSampleRate;
    String nativeSampleBufSize;
     private String mErrorInfo[];
     private String mReceiveBlockNames[];


 // properties specific for Camera block
   private CameraView mCameraView;
   private Camera2View mCamera2View;
   private int mDisplayWidth;
   private int mDisplayHeight;
   private Mat mCameraBufInput;
   private Mat mCameraBufOutput;
   private boolean  hasCamera2Support = true;

   private final BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
	    @Override
	    public void onManagerConnected(int status) {
	        switch (status) {
	            case LoaderCallbackInterface.SUCCESS:
	            	flashMessage("OpenCV loaded successfully");
	                if (hasCamera2Support) {
                          if (null != mCamera2View)
                               mCamera2View.enableView();
                          }else {
                          if (null != mCameraView)
                               mCameraView.enableView();
                         }
                   break;
	            default:
	                super.onManagerConnected(status);
                   break;
	        }
	    }
	};

   private boolean isCamera2Supported() {
      if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
          return true;
      } else {
            return false;
      }
   }
    private void registerCamera() {
    if (hasCamera2Support) {
        mCamera2View = (Camera2View) findViewById(R.id.surface2_view);
        mCamera2View.setVisibility(SurfaceView.VISIBLE);
        mCameraView = (CameraView) findViewById(R.id.surface_view);
        mCameraView.setVisibility(SurfaceView.GONE);
        mCamera2View.setCvCameraViewListener(this);
    }else {
        mCameraView = (CameraView) findViewById(R.id.surface_view);
        mCameraView.setVisibility(SurfaceView.VISIBLE);
        mCamera2View = (Camera2View) findViewById(R.id.surface2_view);
        mCamera2View.setVisibility(SurfaceView.GONE);
        mCameraView.setCvCameraViewListener(this);
    }
    }

    private void resumeCamera() {
        if (!OpenCVLoader.initDebug()) {
            Log.d("resumeCamera", "Internal OpenCV library not found. Using OpenCV Manager for initialization");
        OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_0_0, this, mLoaderCallback);
        } else {
            Log.d("resumeCamera", "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
            if (hasCamera2Support) {
                 if (mCamera2View != null) {
                     mCamera2View.setCameraPermissionGranted();
                 }
            } else {
                  if (mCameraView != null) {
                      mCameraView.setCameraPermissionGranted();
                   }
             }
        }
    }

    private void pauseCamera() {
        if (hasCamera2Support) 
              if (mCamera2View != null) 
                  mCamera2View.disableView();
        else {
             if (mCameraView != null)
                  mCameraView.disableView();
        }
	 }

    public void onCameraViewStarted(int width, int height) {
        mCameraBufInput = new Mat(height, width, CvType.CV_8UC4);
        mCameraBufOutput = new Mat(height, width, CvType.CV_8UC4);
	 }

    public void onCameraViewStopped() {
    	mCameraBufInput.release();
    	mCameraBufOutput.release();
    }

    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
    	mCameraBufInput = inputFrame.rgba();
    	return mCameraBufOutput;
	 }

    public int initCamera(double sampleTime, int location, int width, int height) {
        try {
            if (hasCamera2Support)
                mCamera2View.check(location, width, height);
            else
                mCameraView.check(location, width, height);
                 return 1;
        } catch (CameraView.SetupException ex) {
                mCameraView.showAlert(ex.mDescription);
                return 0;
        } catch (Camera2View.SetupException ex) {
                 mCamera2View.showAlert(ex.mDescription);
                 return 0;
        }
    }
    public int initVideoDisplay(int width, int height) {
        mDisplayWidth = width;
        mDisplayHeight = height;
        return 1;
    }

    public long getCameraInputBuffer() {
       return (mCameraBufInput != null ? mCameraBufInput.getNativeObjAddr() : 0);
    }

	 public long getCameraOutputBuffer() {
		return (mCameraBufOutput != null ? mCameraBufOutput.getNativeObjAddr() : 0);
	}

    private boolean checkIfAllPermissionsGranted()
    {
        return true && isCameraPermissionGranted;
    }
    private void requestPermission() {
        String permissionRationale = "";
        // Here, thisClass is the current activity
        //request for camera
        if (ContextCompat.checkSelfPermission(thisClass,
                Manifest.permission.CAMERA)
                != PackageManager.PERMISSION_GRANTED) {

            // Permission is not granted. Should we show an explanation?
            if (ActivityCompat.shouldShowRequestPermissionRationale(thisClass,
                    Manifest.permission.CAMERA)) {
                permissionRationale += "Camera, ";
            } else {
                // No explanation needed; request the permission
                if (!isCameraPermissionRequested) {
                    isCameraPermissionRequested = true;
                    ActivityCompat.requestPermissions(thisClass,
                            new String[]{Manifest.permission.CAMERA},
                            MY_PERMISSIONS_REQUEST_CAMERA);
                    return;
                }
            }
        } else {
            // Permission has already been granted
            isCameraPermissionGranted = true;
        }
        if (!permissionRationale.isEmpty())
            if (infoFragment != null) {
                infoFragment.updateModelInfo(permissionRationale + "permission not granted. Model cannot start.");
            }
    }
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        com.example.Parent_Mobile.databinding.ActivityMainBinding activityMainBinding = ActivityMainBinding.inflate(LayoutInflater.from(this));
        setContentView(activityMainBinding.getRoot());
        fm = getSupportFragmentManager();
        Fragment navHostFragment = fm.findFragmentById(R.id.nav_host_fragment);
        navHostFragment = navHostFragment.getChildFragmentManager().getFragments().get(0);
        current =  navHostFragment;
        appFragment  = (AppFragment) navHostFragment;
        infoFragment  = new InfoFragment();
        logFragment  = new LogFragment();
        fm.beginTransaction().add(R.id.nav_host_fragment, logFragment, "3").hide(logFragment).commit();
        fm.beginTransaction().add(R.id.nav_host_fragment, infoFragment, "2").hide(infoFragment).commit();
        fm.beginTransaction().add(R.id.nav_host_fragment, appFragment, "1").commit();
        BottomNavigationView navView = findViewById(R.id.nav_view);
        NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment);
        NavigationUI.setupWithNavController(navView, navController);
        navView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
        @Override
                public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
                        switch (menuItem.getItemId()) {                case R.id.navigation_app:
                fm.beginTransaction().hide(current).show(appFragment).commit();
                current = appFragment;
        return true;                case R.id.navigation_info:
                fm.beginTransaction().hide(current).show(infoFragment).commit();
                current = infoFragment;
        return true;                case R.id.navigation_log:
                fm.beginTransaction().hide(current).show(logFragment).commit();
                current = logFragment;
        return true;                }
                return false;
                }
        });
        queryNativeAudioParameters();
hasCamera2Support = isCamera2Supported();
        thisClass = this;
mErrorInfo = getResources().getStringArray(R.array.error_information);
mReceiveBlockNames = getResources().getStringArray(R.array.tcpReceiveBlockNames);
     }

    private Parent_Mobile thisClass;
    private final Thread BgThread = new Thread() {
    @Override
    public void run() {
            String argv[] = new String[] {"MainActivity","Parent_Mobile"};
            naMain(argv, thisClass);
        }
    };

    public void flashMessage(final String inMessage) {
        runOnUiThread(new Runnable() {
              public void run() {
                    Toast.makeText(getBaseContext(), inMessage, Toast.LENGTH_SHORT).show();
              }
        });
    }

    public void terminateApp() {
        finish();
    }

    protected void onDestroy() {
         if (BgThread.isAlive())
             naOnAppStateChange(6);
         super.onDestroy();
         System.exit(0); //to kill all our threads.
    }

	@Override
    public void onAttachFragment(Fragment fragment) {
        super.onAttachFragment(fragment);
        if (fragment instanceof InfoFragment) {
            this.infoFragment = (InfoFragment) fragment;
            infoFragment.setFragmentInteractionListener(this);
        }
        if (fragment instanceof AppFragment) {
            ((AppFragment)fragment).setFragmentInteractionListener(this);
        }
        if (fragment instanceof CameraScopeFragment) {
            ((CameraScopeFragment)fragment).setFragmentInteractionListener(this);
        }
        if (fragment instanceof LogFragment) {
            this.logFragment = (LogFragment) fragment;
        }
    }

	@Override
    public void onFragmentCreate(String name) {

    }

    @Override
    public void onFragmentStart(String name) {
        switch (name) {
            case "Info":
               break;
            case "App":
                break;
            default:
                break;
    }
    }

    @Override
    public void onFragmentResume(String name) {
        switch (name) {
            case "App":
                registerDataDisplays();
                break;
           case "dot1":
              if (hasCamera2Support) {
                   if (mCamera2View == null) {
                       registerCamera();
                    }
               }else {
                    if (mCameraView == null) {
                         registerCamera();
                    }
               }
               if (checkIfAllPermissionsGranted()) {
                   resumeCamera();
	                System.loadLibrary("Parent_Mobile");
                   if (!BgThread.isAlive())
                       BgThread.start();
               }
               break;
            default:
                break;
        }
    }

    @Override
    public void onFragmentPause(String name) {
    }
    @Override
    protected void onResume() {
            requestPermission();
         super.onResume();
         if (BgThread.isAlive())
             naOnAppStateChange(3);
    }

    @Override
    protected void onPause() {
        if (BgThread.isAlive())
            naOnAppStateChange(4);
        super.onPause();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        LinearLayout mylayout = thisClass.findViewById(R.id.layoutapp);
        if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
            mylayout.setOrientation(LinearLayout.HORIZONTAL);
        } else if (newConfig.orientation == Configuration.ORIENTATION_PORTRAIT){
            mylayout.setOrientation(LinearLayout.VERTICAL);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String permissions[], int[] grantResults) {
        switch (requestCode) {
            case MY_PERMISSIONS_REQUEST_CAMERA:
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    // permission was granted, yay! Do related task you need to do.
                    isCameraPermissionGranted = true;
                    resumeCamera();
                } else {
                    // permission denied, boo!
                    flashMessage("Camera usage Permission not granted");
                }
                isCameraPermissionRequested = false;
                break;

            // other case lines to check for other
            // permissions this app might request.
        }
        if (!checkIfAllPermissionsGranted() && !isCameraPermissionRequested) {
            requestPermission();
        }
    }

    public void registerDataDisplays() {
    // bind text views for data display block;
    for (int i = 1; i <= 3; i++) {
            TextView textView = (TextView) findViewById(
            getResources().getIdentifier("DataDisplay" + i, "id", getPackageName()));
            textViews.put(i, textView);
        }
    }
    public void displayText(int id, byte[] data, byte[] format) {
        String formatString = new String(format);
        String toDisplay = String.format(formatString, data[0]);
        if (data.length > 1) {
            for (int i = 1; i < data.length; i++)
                toDisplay += "\n" + String.format(formatString, data[i]);
        }
        updateTextViewById(id, toDisplay);
    }

    public void displayText(int id, short[] data, byte[] format) {
        String formatString = new String(format);
        String toDisplay = String.format(formatString, data[0]);
        if (data.length > 1) {
            for (int i = 1; i < data.length; i++)
                toDisplay += "\n" + String.format(formatString, data[i]);
        }
        updateTextViewById(id, toDisplay);
    }

    public void displayText(int id, int[] data, byte[] format) {
        String formatString = new String(format);
        String toDisplay = String.format(formatString, data[0]);
        if (data.length > 1) {
            for (int i = 1; i < data.length; i++)
                toDisplay += "\n" + String.format(formatString, data[i]);
        }
        updateTextViewById(id, toDisplay);
    }

    public void displayText(int id, long[] data, byte[] format) {
        String formatString = new String(format);
        String toDisplay = String.format(formatString, data[0]);
        if (data.length > 1) {
            for (int i = 1; i < data.length; i++)
                toDisplay += "\n" + String.format(formatString, data[i]);
        }
        updateTextViewById(id, toDisplay);
    }

    public void displayText(int id, float[] data, byte[] format) {
        String formatString = new String(format);
        String toDisplay = String.format(formatString, data[0]);
        if (data.length > 1) {
            for (int i = 1; i < data.length; i++)
                toDisplay += "\n" + String.format(formatString, data[i]);
        }
        updateTextViewById(id, toDisplay);
    }

    public void displayText(int id, double[] data, byte[] format) {
        String formatString = new String(format);
        String toDisplay = String.format(formatString, data[0]);
        if (data.length > 1) {
            for (int i = 1; i < data.length; i++)
                toDisplay += "\n" + String.format(formatString, data[i]);
        }
        updateTextViewById(id, toDisplay);
    }

    private void updateTextViewById(final int id, final String finalStringToDisplay) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try {
                    TextView tv = textViews.get(id);
                    if(tv != null) {
                        tv.setText(finalStringToDisplay);
                    }
					
                } catch (Exception ex) {
                    Log.e("Parent_Mobile.updateTextViewById", ex.getLocalizedMessage());
                }
            }
        });
    }
    @TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
    private void queryNativeAudioParameters() {
        Log.d("audioEQ", "queryNativeAudioParameters called");
        AudioManager myAudioMgr = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        nativeSampleRate = myAudioMgr.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
        nativeSampleBufSize = myAudioMgr.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
    }

    public int getNativeSampleRate() {
        Log.d("audioEQ", "JNI getNativeSampleRate called");
        return Integer.parseInt(nativeSampleRate);
    }
    public int getNativeSampleBufSize() {
        Log.d("audioEQ", "JNI getNativeSampleBufSize called");
        return Integer.parseInt(nativeSampleBufSize);
    }
    // Log TCP info
     public void displayTCPLogs(short errorNo, int blockId, short isReceive, String argument) {
       if (mErrorInfo != null && mErrorInfo.length >= errorNo) {
          String errorInfo = mErrorInfo[errorNo];
          if (isReceive == 1 && blockId >0 && mReceiveBlockNames.length >= blockId)
              errorInfo = mReceiveBlockNames[blockId-1] + errorInfo;
            if (!argument.equals(""))
                errorInfo = errorInfo.replace("#argument#",argument);
            logFragment.updateTCPLog(errorInfo);
       }
}

    private native int naMain(String[] argv, Parent_Mobile pThis);
    private native void naOnAppStateChange(int state);
}
