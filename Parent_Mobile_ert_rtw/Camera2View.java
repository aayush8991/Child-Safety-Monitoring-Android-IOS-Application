package com.example.Parent_Mobile;

import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

import org.opencv.android.JavaCamera2View;

import android.content.Context;
import android.hardware.Camera.Size;
import android.util.AttributeSet;

import android.content.DialogInterface;
import android.app.AlertDialog;
import android.app.Activity;

public class Camera2View extends JavaCamera2View {
    private int mCameraWidth = 640;
    private int mCameraHeight = 480;
    private int mCameraLocation = org.opencv.android.CameraBridgeViewBase.CAMERA_ID_BACK;

    public class SetupException extends Exception {
       private static final long serialVersionUID = 3405052571591189497L;
    	public String mDescription;
    	SetupException(String inDescription) {
    		mDescription = inDescription;
    	}
    }

    public Camera2View(Context context, int cameraId) {
        super(context, cameraId);
        setCameraIndex(mCameraLocation);
        setMaxFrameSize(mCameraWidth, mCameraHeight);
    }

    public Camera2View(Context context, AttributeSet attrs) {
        super(context, attrs);
        setCameraIndex(mCameraLocation);
        setMaxFrameSize(mCameraWidth, mCameraHeight);
    }

    public void check(int location, int width, int height) throws SetupException {
    	if ((mCameraWidth != width) || (mCameraHeight != height)) {
    		String message = String.format("Image size in the model doesn't match the view:\nModel: %d x %d\nView: %d x %d", width, height, mCameraWidth, mCameraHeight);
           throw new SetupException(message);
    	}

       String strLocation;
       if (mCameraLocation == org.opencv.android.CameraBridgeViewBase.CAMERA_ID_BACK)
           strLocation = "Back";
       else
           strLocation = "Front";

       if (location > 0) {
           boolean match = false;
           String mdlLocation;
           if (location == 2) {//back
               mdlLocation = "Back";
               match = (mCameraLocation == org.opencv.android.CameraBridgeViewBase.CAMERA_ID_BACK);
           }
           else {
               mdlLocation = "Front";
               match = (mCameraLocation == org.opencv.android.CameraBridgeViewBase.CAMERA_ID_FRONT);
           }
           if (!match) {
               String message = String.format("Location in model doesn't match the view:\nModel: %s\nView: %s", mdlLocation, strLocation);
               throw new SetupException(message);
           }
       }
    }

    protected boolean initializeCamera(int width, int height) {
    	boolean ret = super.initializeCamera();
       return ret;
    }
    public void showAlert(final String inMessage) {
      final Parent_Mobile activity = (Parent_Mobile)getContext();
       activity.runOnUiThread( new Runnable() {
           public void run() {
               AlertDialog.Builder dialog = new AlertDialog.Builder(activity);
               dialog.setCancelable(false);
               dialog.setMessage(inMessage);
               dialog.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                   public void onClick(DialogInterface dialog, int which) {
                       dialog.dismiss();
                       ((Activity)activity).finish();
                   }
               });
               dialog.create();
               dialog.show();
           }
       });
   }

}